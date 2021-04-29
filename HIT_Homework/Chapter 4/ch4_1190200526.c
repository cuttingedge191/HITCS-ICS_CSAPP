/*
* 计算机系统 第四章作业
* 学号：1190200526
* 姓名：沈城有
* 题目：4.45, 4.46, 4.51
*/

/*4.45题：
A.不正确。
当REG为%rsp时，这段代码序列先将栈指针减8再将%rsp的值写入栈，
结果是将%rsp-8压入栈中，而不是压入原栈指针。
B.修改：
  movq REG, -8(%rsp)
  subq $8, %rsp
*/

/*4.46题：
A.不正确。
当REG为%rsp时，这段代码序列先访存将值保存于%rsp再将%rsp的值加8，
结果会使%rsp的值为(%rsp)+8，而不是(%rsp)。
（注：“(%rsp)表示寄存器%rsp指向的内存地址处保存的值）
B.修改：
  addq $8, %rsp
  movq -8(%rsp), REG
*/

/*4.51题：
  iaddq V, rB
  +-----------+------------------------+
  | Fetch     |  icode:ifun <- M1[PC]  |  
  |           |  rA:rB <- M1[PC+1]     | 
  |           |  valC <- M8[PC+2]      |
  |           |  valP <- PC+10         |
  +-----------+------------------------|
  | Decode    |  valB <- R[rB]         |
  +-----------+------------------------+
  | Execute   |  valE <- valB+valC     |
  +-----------+------------------------+
  | Memory    |                        |
  +-----------+------------------------+
  | Write     |  R[rB] <- valE         |
  +-----------+------------------------+
  | PC update |  PC <- valP            |
  +-----------+------------------------+
*/
