/*
* 计算机系统 第六章作业
* 学号：1190200526
* 姓名：沈城有
* 题目：6.27, 6.31, 6.35, 6.39, 6.43
* （附加题：6.45, 6.46）
*/

/*6.27题：
A. 0x08A4 0x08A5 0x08A6 0x08A7
   0x0704 0x0705 0x0706 0x0707
B. 0x1238 0x1239 0x123A 0x123B
*/

/*6.31题：
A. 0 0111 0001 1010
B.   参数     值
      CO      0x2
      CI      0x6
      CT      0x38
     Hit?     Y
     Byte     0xEB
*/

/*6.35题：
    dst数组       src数组
  m  h  h  h    m  h  h  h
  m  h  h  h    m  h  h  h
  m  h  h  h    m  h  h  h
  m  h  h  h    m  h  h  h
*/

/*6.39题：
块大小32字节，容量2048字节，直接映射，故共有2048/32 = 64组。
每组1块，可保存2个结构体元素，总共可保存128个结构体。
A. 16*16*4 = 1024
B. 程序按列顺序进行写操作，每四次写的命中情况均为m h h h，
   故不命中的写次数为1024 / 4 = 256
C. 25%
*/

/*6.43题：
每次写入4字节，由于高速缓存的一行也是4字节，每次写入均不会命中。
故有100%的写在高速缓存中不命中。
*/

//【附加】6.45题：
void fast_transpose(int *dst, int *src, int dim)
{
    /* 计算分块大小，要求尽可能大，但要满足2T^2 < C，
    C是L1高速缓存的容量，具体过程略 */
    int T;
    /* limit用于检测是否越界，假如能确保T能整除dim*dim，
    我认为可以去掉此变量，进一步提高性能 */
    long limit = dim * dim;
    /* 使用分块提高时间局部性 */
    for (int i = 0; i < dim; i += T)
    {
        for (int j = 0; j < dim; j += T)
        {
            for (int k = i; k < i + T; ++k)
            {
                for (int l = j; l < j + T; ++l)
                {
                    // 逐个进行读写
                    int a = l * dim + k;
                    int b = k * dim + l;
                    // 检测是否越界
                    if (a < limit && b < limit)
                        dst[a] = src[b];
                }
            }
        }
    }
}

//【附加】6.46题：
/* 思路与6.45题类似，由于无向图邻接矩阵关于对角线对称，
此题可再进行一个优化，即仅计算对角线一侧 */
void fast_col_convert(int *G, int dim)
{
    /* 计算分块大小，要求尽可能大，但要满足2T^2 < C，
    C是L1高速缓存的容量，具体过程略 */
    int T;
    int tmp;
    /* limit用于检测是否越界，假如能确保T能整除dim*dim，
    我认为可以去掉此变量，进一步提高性能 */
    long limit = dim * dim;
    /* 使用分块提高时间局部性 */
    for (int i = 0; i < dim; i += T)
    {   /* 循环变量初始化与上一题略有不同，
        此操作可去掉对角线另一侧的重复计算 */
        for (int j = i; j < dim; j += T)
        {
            for (int k = i; k < i + T; ++k)
            {
                for (int l = j; l < j + T; ++l)
                {
                    // 逐个操作
                    int a = l * dim + k;
                    int b = k * dim + l;
                    // 检测是否越界
                    if (a < limit && b < limit)
                    {
                        //避免重复计算
                        tmp = G[a] || G[b];
                        G[a] = tmp;
                        G[b] = tmp;
                    }
                }
            }
        }
    }
}
