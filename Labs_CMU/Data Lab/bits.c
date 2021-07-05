/* 
 * CS:APP Data Lab 
 * 
 * <*** cuttingedge191>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
	/* brief description of how your implementation works */
	int var1 = Expr1;
	...
	int varM = ExprM;

	varJ = ExprJ;
	...
	varN = ExprN;
	return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
	  not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
	
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
	 cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
	 is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
	/* exploit ability of shifts to compute powers of 2 */
	return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
	/* exploit ability of shifts to compute powers of 2 */
	int result = (1 << x);
	result += 4;
	return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
	 cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
	 check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
	 or comparison) that you are allowed to use for your implementation
	 of the function.  The max operator count is checked by dlc.
	 Note that assignment ('=') is not counted; you may use as many of
	 these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
	 header comment for each function. If there are any inconsistencies 
	 between the maximum ops in the writeup and in this file, consider
	 this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
//位异或的实现
int bitXor(int x, int y) {
	return ~(~(x & ~y) & ~(~x & y));
	//另一解：
	//return ~(x & y) & ~(~x & ~y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
//返回补数最小值（TMin）
int tmin(void) {
	return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
//判断x是否为TMax
//思路：利用TMax + 1 = TMin, TMin + TMax = 0xFFFFFFFF, !(0xFFFFFFFF) = 0
//注意：需要排除的x = -1的情况
int isTmax(int x) {
	int t = x + 1;
	x = x + t;
	x = ~x;
	t = !t;  //排除-1的情况
	x = x + t;
	return !x;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
//判断一个数是否所有偶数位均为1
//思路：类似掩码
int allOddBits(int x) {
	int t1 = 0xAA << 8;
	int t2 = t1 + 0xAA;
	int t = (t2 << 16) + t2;
	return !((x & t) ^ t);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
//数取负操作
int negate(int x) {
	return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
//Ascii范围判断
int isAsciiDigit(int x) {
	int e1 = !((x >> 4) ^ 0x3);  //检测高28位
	int e2 = x & 0xF;            //取低4位
	int e3 = e2 & 0x8;           //取第4位
	int e4 = !(e2 & 0x6);        //检测是否超出9
	int r = e1 & ((!e3) | e4);
	return r;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
//条件输出
int conditional(int x, int y, int z) {
	int test = !(!x);          //规范化
	int select = ~test + 1;    //0x0 or 0xFFFFFFFF
	return (y & select) | (z & ~select);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
//数小于等于
//思路：同号直接相减看结果，异号则比较符号
int isLessOrEqual(int x, int y) {
	int test = !((y + (~x + 1)) >> 31);  //y-x符号（反）
	int s1 = !(x >> 31);                 //x符号（反）
	int s2 = !(y >> 31);                 //y符号（反）
	int sd = s1 ^ s2;                    //异号时可能存在溢出
	int sx = sd & s1;                    //异号且x为正
	return (sd & !sx) | (test & !sd);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
//实现!操作
//思路：利用0的相反数特殊性质
//注意：TMin也有相反数等于本身的性质
int logicalNeg(int x) {
	int neg = ~x + 1;
	return ((x | neg) >> 31) + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
//补码表示数所需最小位数
int howManyBits(int x) {
	int b_16, b_8, b_4, b_2, b_1, b_0;
	int result;
	int sign = x >> 31;
	x = (x & ~sign) | (~x & sign);  //将负数按位取反，便于寻找最高位，同时避免符号位的1干扰右移过程
	//逐步缩小检测位数
	b_16 = (!!(x >> 16)) << 4;  //判断高16位中是否有1
	x = x >> b_16;              //高16位不为0，将x右移16位再检测
	b_8 = (!!(x >> 8)) << 3;    //同理，检测高8位（24位）
	x = x >> b_8;
	b_4 = (!!(x >> 4)) << 2;    //以下同理
	x = x >> b_4;
	b_2 = (!!(x >> 2)) << 1;
	x = x >> b_2;
	b_1 = !!(x >> 1);
	x = x >> b_1;
	b_0 = x;
	result = b_16 + b_8 + b_4 + b_2 + b_1 + b_0 + 1;  //非负数添加最高符号位0，负数在计算时取反需添加丢失的符号位1
	return result;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
//单精度浮点数二倍计算
unsigned floatScale2(unsigned uf) {
	int sign = uf & (1 << 31);
	int exp = (uf >> 23) & 0xFF;
	int frac = uf & ~(0xff800000);
	if(exp == 0)    //非规范情况直接左移并保留符号位
		return (uf << 1) | sign;
	if(exp == 255)  //指数位全为1时原浮点数为无穷或NaN，直接返回
		return uf;
	++exp;
	if(exp == 255)  //二倍后数溢出，表示为无穷
		frac = 0;
	return sign + (exp << 23) + frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
//单精度浮点数转换为整型(int)
int floatFloat2Int(unsigned uf) {
	int sign = uf >> 31;
	int exp = ((uf >> 23) & 0xFF) - 127;
	int frac = (uf & ~(0xff800000)) | 0x00800000;
	if(exp < 0)  //绝对值肯定小于1的数
		return 0;
	if(exp > 31) //int溢出及NaN
		return 0x80000000;
	if(exp > 23)
		frac = frac << (exp - 23);
	else
		frac = frac >> (23 - exp);
	if(!((frac >> 31) ^ sign))
		return frac;
	if(frac >> 31)
		return 0x80000000;
	return ~frac + 1;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
//单精度表示2的幂
unsigned floatPower2(int x) {
	int inf = 0xff << 23;
	int exp = x + 127;
	if(exp <= 0)
		return 0;
	if(exp >= 255)
		return inf;
	return exp << 23;
}
