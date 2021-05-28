#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "cachelab.h"

//#define DEBUG_ON 
#define ADDRESS_LENGTH 64

/* Type: Memory address */
typedef unsigned long long int mem_addr_t;

/* Type: Cache line
   LRU is a counter used to implement LRU replacement policy  */
typedef struct cache_line {
    char valid;
    mem_addr_t tag;
    unsigned long long int lru;
} cache_line_t;

typedef cache_line_t* cache_set_t;
typedef cache_set_t* cache_t;

/* Globals set by command line args */
int verbosity = 0; /* print trace if set */
int s = 0; /* set index bits */
int b = 0; /* block offset bits */
int E = 0; /* associativity */
char* trace_file = NULL;

/* Derived from command line args */
int S; /* number of sets */
int B; /* block size (bytes) */

/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int lru_counter = 1;

/* The cache we are simulating */
cache_t cache;  
mem_addr_t set_index_mask; // 用于从内存地址得到缓存组的索引值

/* 
 * initCache - Allocate memory, write 0's for valid and tag and LRU
 * also computes the set_index_mask
 */
void initCache()
{
    cache = (cache_t)malloc(sizeof(cache_set_t) * S);
    if (cache == NULL)
    {
        printf("Failed to malloc!\n");
        return;
    }
    for (int i = 0; i < S; ++i)
    {
        cache[i] = (cache_set_t)malloc(sizeof(cache_line_t) * E);
        if (cache[i] == NULL)
        {
            printf("Failed to malloc!\n");
            return;
        }
        for (int j = 0; j < E; ++j)
        {
            cache[i][j].valid = 0;
            cache[i][j].tag = 0;
            cache[i][j].lru = 0;
        }
    }
    set_index_mask = (1 << s) - 1;
}


/* 
 * freeCache - free allocated memory
 */
void freeCache()
{
    for (int i = 0; i < E; ++i)
        free(cache[i]);
    free(cache);
}


/* 
 * accessData - Access data at memory address addr.
 *   If it is already in cache, increase hit_count
 *   If it is not in cache, bring it in cache, increase miss count.
 *   Also increase eviction_count if a line is evicted.
 */
void accessData(mem_addr_t addr)
{
    /* 
     * 关于LRU实现：
     * 每次访问内存时++lru_counter
     * 将此内存块信息lru值设置为lru_counter
     * 驱逐时选择lru_counter - lru绝对值最大的内存块（避免溢出影响）
     */
    mem_addr_t addr_tag = addr >> (s + b); // 标记位
    mem_addr_t addr_index = (addr >> b) & set_index_mask; // 组索引
    unsigned long long max = 0;
    int max_index;
    ++lru_counter;
    // 在组索引指向的组中查找数据
    for (int i = 0; i < E; ++i)
    {
        if (cache[addr_index][i].tag == addr_tag && cache[addr_index][i].valid) // 命中
        {
            cache[addr_index][i].lru = lru_counter;
            if (verbosity)
                printf(" hit");
            ++hit_count;
            return;
        }
    }
    // 不命中
    ++miss_count;
    if (verbosity)
        printf(" miss");
    // 若未找到，先检测有无空闲块(valid == 0)
    for (int i = 0; i < E; ++i)
    {
        if (!cache[addr_index][i].valid)
        {
            cache[addr_index][i].valid = 1;
            cache[addr_index][i].lru = lru_counter;
            cache[addr_index][i].tag = addr_tag;
            return;
        }
    }
    // 无空闲块，进行LRU
    for (int i = 0; i < E; ++i)
    {
        if (max < abs(lru_counter - cache[addr_index][i].lru))
        {
            max = abs(lru_counter - cache[addr_index][i].lru);
            max_index = i;
        }
    }
    ++eviction_count;
    cache[addr_index][max_index].valid = 1;
    cache[addr_index][max_index].lru = lru_counter;
    cache[addr_index][max_index].tag = addr_tag;
    return;
}


/*
 * replayTrace - replays the given trace file against the cache 
 */
void replayTrace(char* trace_fn)
{
    char buf[1000];
    mem_addr_t addr=0;
    unsigned int len=0;
    FILE* trace_fp = fopen(trace_fn, "r");

    if(!trace_fp){
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while( fgets(buf, 1000, trace_fp) != NULL) {
        if(buf[1]=='S' || buf[1]=='L' || buf[1]=='M') {
            sscanf(buf+3, "%llx,%u", &addr, &len);

            if(verbosity)
                printf("%c %llx,%u ", buf[1], addr, len);

            accessData(addr);

            /* If the instruction is R/W then access again */
            if(buf[1]=='M')
                accessData(addr);
            
            if (verbosity)
                printf("\n");
        }
    }

    fclose(trace_fp);
}

/*
 * printUsage - Print usage info
 */
void printUsage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * main - Main routine 
 */
int main(int argc, char* argv[])
{
    char c;

    while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1) {
        switch(c){
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }

    /* Make sure that all required command line args were specified */
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }

    /* Compute S, E and B from command line args */
    // E已经从命令行参数中得到了
    S = 1 << s;
    E = E;
    B = 1 << b;
 
    /* Initialize cache */
    initCache();

#ifdef DEBUG_ON
    printf("DEBUG: S:%u E:%u B:%u trace:%s\n", S, E, B, trace_file);
    printf("DEBUG: set_index_mask: %llu\n", set_index_mask);
#endif
 
    replayTrace(trace_file);

    /* Free allocated memory */
    freeCache();

    /* Output the hit and miss statistics for the autograder */
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
