# 实验 2  Bomb Lab

**主要方法**：64位Linux系统环境下通过命令`linux> objdump -d bomb > bomb.txt`反汇编可执行目标程序得到文本格式保存的汇编代码，结合gdb进行调试（设置断点、查看内存及寄存器的值等）推算拆弹所需的6段字符串。

[<u>gdb指令（CMU官网提供）</u>](http://csapp.cs.cmu.edu/2e/docs/gdbnotes-x86-64.pdf)

---

## Phase 1: 

**相关汇编代码及分析：**

```assembly
0000000000400ee0 <phase_1>:
  400ee0:	48 83 ec 08          	sub    $0x8,%rsp #分配栈空间
  400ee4:	be 00 24 40 00       	mov    $0x402400,%esi #一个类似地址的可疑值
  400ee9:	e8 4a 04 00 00       	callq  401338 <strings_not_equal> #调用函数
  400eee:	85 c0                	test   %eax,%eax #检测函数返回值
  400ef0:	74 05                	je     400ef7 <phase_1+0x17> #第一阶段成功
  400ef2:	e8 43 05 00 00       	callq  40143a <explode_bomb> #引爆
  400ef7:	48 83 c4 08          	add    $0x8,%rsp #释放栈空间
  400efb:	c3                   	retq    #返回
0000000000401338 <strings_not_equal>:
  401338:	41 54                	push   %r12
  40133a:	55                   	push   %rbp
  40133b:	53                   	push   %rbx #被调用者保存
  40133c:	48 89 fb             	mov    %rdi,%rbx
  40133f:	48 89 f5             	mov    %rsi,%rbp #转移地址
  401342:	e8 d4 ff ff ff       	callq  40131b <string_length> #测输入字符串长度
  401347:	41 89 c4             	mov    %eax,%r12d
  40134a:	48 89 ef             	mov    %rbp,%rdi
  40134d:	e8 c9 ff ff ff       	callq  40131b <string_length> #测答案字符串长度
  401352:	ba 01 00 00 00       	mov    $0x1,%edx
  401357:	41 39 c4             	cmp    %eax,%r12d #比较两次结果
  40135a:	75 3f                	jne    40139b <strings_not_equal+0x63> #不相等
  40135c:	0f b6 03             	movzbl (%rbx),%eax #开始检查字符串中字符是否相同
  40135f:	84 c0                	test   %al,%al
  401361:	74 25                	je     401388 <strings_not_equal+0x50>
  401363:	3a 45 00             	cmp    0x0(%rbp),%al
  401366:	74 0a                	je     401372 <strings_not_equal+0x3a>
  401368:	eb 25                	jmp    40138f <strings_not_equal+0x57>
  40136a:	3a 45 00             	cmp    0x0(%rbp),%al
  40136d:	0f 1f 00             	nopl   (%rax)
  401370:	75 24                	jne    401396 <strings_not_equal+0x5e>
  401372:	48 83 c3 01          	add    $0x1,%rbx
  401376:	48 83 c5 01          	add    $0x1,%rbp
  40137a:	0f b6 03             	movzbl (%rbx),%eax
  40137d:	84 c0                	test   %al,%al
  40137f:	75 e9                	jne    40136a <strings_not_equal+0x32>
  401381:	ba 00 00 00 00       	mov    $0x0,%edx
  401386:	eb 13                	jmp    40139b <strings_not_equal+0x63>
  401388:	ba 00 00 00 00       	mov    $0x0,%edx
  40138d:	eb 0c                	jmp    40139b <strings_not_equal+0x63>
  40138f:	ba 01 00 00 00       	mov    $0x1,%edx
  401394:	eb 05                	jmp    40139b <strings_not_equal+0x63>
  401396:	ba 01 00 00 00       	mov    $0x1,%edx
  40139b:	89 d0                	mov    %edx,%eax #返回值，默认为1
  40139d:	5b                   	pop    %rbx
  40139e:	5d                   	pop    %rbp
  40139f:	41 5c                	pop    %r12
  4013a1:	c3                   	retq   
000000000040131b <string_length>:
  40131b:	80 3f 00             	cmpb   $0x0,(%rdi)
  40131e:	74 12                	je     401332 <string_length+0x17>
  401320:	48 89 fa             	mov    %rdi,%rdx
  401323:	48 83 c2 01          	add    $0x1,%rdx
  401327:	89 d0                	mov    %edx,%eax
  401329:	29 f8                	sub    %edi,%eax
  40132b:	80 3a 00             	cmpb   $0x0,(%rdx)
  40132e:	75 f3                	jne    401323 <string_length+0x8>
  401330:	f3 c3                	repz retq 
  401332:	b8 00 00 00 00       	mov    $0x0,%eax
  401337:	c3                   	retq   
```

**过程：**

```
***:~/Bomb Lab$ gdb bomb
(gdb) break strings_not_equal
Breakpoint 1 at 0x401338
(gdb) break string_length
Breakpoint 2 at 0x40131b
(gdb) break explode_bomb
Breakpoint 3 at 0x40143a
(gdb) run
Starting program: ~/bomb 
Welcome to my fiendish little bomb. You have 6 phases with
which to blow yourself up. Have a nice day!
Test input.

Breakpoint 1, 0x0000000000401338 in strings_not_equal ()
(gdb) x/s 0x402400
0x402400:	"Border relations with Canada have never been better." #答案字符串
(gdb) c
Continuing.

Breakpoint 2, 0x000000000040131b in string_length ()
(gdb) x/s $rdi
0x603780 <input_strings>:	"Test input." #输入字符串
(gdb) c
Continuing.

Breakpoint 2, 0x000000000040131b in string_length ()
(gdb) print /d $r12d
$1 = 11 #输入串长
```

**答案： `Border relations with Canada have never been better.`**

---

## Phase 2：

**相关汇编代码及分析：**

```assembly
0000000000400efc <phase_2>:
  400efc:	55                   	push   %rbp
  400efd:	53                   	push   %rbx #被调用者保存
  400efe:	48 83 ec 28          	sub    $0x28,%rsp #划分栈空间
  400f02:	48 89 e6             	mov    %rsp,%rsi #保存栈指针
  400f05:	e8 52 05 00 00       	callq  40145c <read_six_numbers> #调用函数
  400f0a:	83 3c 24 01          	cmpl   $0x1,(%rsp) #第一个数必须是1
  400f0e:	74 20                	je     400f30 <phase_2+0x34>
  400f10:	e8 25 05 00 00       	callq  40143a <explode_bomb>
  400f15:	eb 19                	jmp    400f30 <phase_2+0x34>
  400f17:	8b 43 fc             	mov    -0x4(%rbx),%eax
  400f1a:	01 c0                	add    %eax,%eax #前一个数乘2
  400f1c:	39 03                	cmp    %eax,(%rbx) #比较下一个数与前一个的2倍
  400f1e:	74 05                	je     400f25 <phase_2+0x29>
  400f20:	e8 15 05 00 00       	callq  40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    $0x4,%rbx #下一个数地址
  400f29:	48 39 eb             	cmp    %rbp,%rbx #循环条件，数没有检测结束
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
  400f2e:	eb 0c                	jmp    400f3c <phase_2+0x40>
  400f30:	48 8d 5c 24 04       	lea    0x4(%rsp),%rbx #第二个数地址
  400f35:	48 8d 6c 24 18       	lea    0x18(%rsp),%rbp
  400f3a:	eb db                	jmp    400f17 <phase_2+0x1b>
  400f3c:	48 83 c4 28          	add    $0x28,%rsp
  400f40:	5b                   	pop    %rbx
  400f41:	5d                   	pop    %rbp
  400f42:	c3                   	retq   
000000000040145c <read_six_numbers>:
  40145c:	48 83 ec 18          	sub    $0x18,%rsp
  401460:	48 89 f2             	mov    %rsi,%rdx
  401463:	48 8d 4e 04          	lea    0x4(%rsi),%rcx
  401467:	48 8d 46 14          	lea    0x14(%rsi),%rax
  40146b:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  401470:	48 8d 46 10          	lea    0x10(%rsi),%rax
  401474:	48 89 04 24          	mov    %rax,(%rsp)
  401478:	4c 8d 4e 0c          	lea    0xc(%rsi),%r9
  40147c:	4c 8d 46 08          	lea    0x8(%rsi),%r8 #划分空间，部分存栈，部分存寄存器
  401480:	be c3 25 40 00       	mov    $0x4025c3,%esi #保存了输入格式字符串
  401485:	b8 00 00 00 00       	mov    $0x0,%eax
  40148a:	e8 61 f7 ff ff       	callq  400bf0 <__isoc99_sscanf@plt> #返回输入了几个数字
  40148f:	83 f8 05             	cmp    $0x5,%eax
  401492:	7f 05                	jg     401499 <read_six_numbers+0x3d> #检测输入>5
  401494:	e8 a1 ff ff ff       	callq  40143a <explode_bomb> #输入个数不足引爆
  401499:	48 83 c4 18          	add    $0x18,%rsp
  40149d:	c3                   	retq   
```

**过程：** 略

**答案：`1 2 4 8 16 32`**

---

## Phase 3：

**相关汇编代码及分析：**

```assembly
0000000000400f43 <phase_3>:
  400f43:	48 83 ec 18          	sub    $0x18,%rsp
  400f47:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx #栈指针 + 12
  400f4c:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx #栈指针 + 8
  400f51:	be cf 25 40 00       	mov    $0x4025cf,%esi #和第2题类似，格式字符串
  400f56:	b8 00 00 00 00       	mov    $0x0,%eax #返回值预置
  400f5b:	e8 90 fc ff ff       	callq  400bf0 <__isoc99_sscanf@plt>
  400f60:	83 f8 01             	cmp    $0x1,%eax
  400f63:	7f 05                	jg     400f6a <phase_3+0x27> #输入个数大于1
  400f65:	e8 d0 04 00 00       	callq  40143a <explode_bomb> #否则引爆
  400f6a:	83 7c 24 08 07       	cmpl   $0x7,0x8(%rsp) #要求输入1小于等于7
  400f6f:	77 3c                	ja     400fad <phase_3+0x6a> #可看出输入1为正数
  400f71:	8b 44 24 08          	mov    0x8(%rsp),%eax
  400f75:	ff 24 c5 70 24 40 00 	jmpq   *0x402470(,%rax,8) #跳转地址数组
  400f7c:	b8 cf 00 00 00       	mov    $0xcf,%eax  #input1 = 0
  400f81:	eb 3b                	jmp    400fbe <phase_3+0x7b>
  400f83:	b8 c3 02 00 00       	mov    $0x2c3,%eax #input1 = 2
  400f88:	eb 34                	jmp    400fbe <phase_3+0x7b>
  400f8a:	b8 00 01 00 00       	mov    $0x100,%eax #input1 = 3
  400f8f:	eb 2d                	jmp    400fbe <phase_3+0x7b>
  400f91:	b8 85 01 00 00       	mov    $0x185,%eax #input1 = 4
  400f96:	eb 26                	jmp    400fbe <phase_3+0x7b>
  400f98:	b8 ce 00 00 00       	mov    $0xce,%eax  #input1 = 5
  400f9d:	eb 1f                	jmp    400fbe <phase_3+0x7b>
  400f9f:	b8 aa 02 00 00       	mov    $0x2aa,%eax #input1 = 6
  400fa4:	eb 18                	jmp    400fbe <phase_3+0x7b>
  400fa6:	b8 47 01 00 00       	mov    $0x147,%eax #input1 = 7
  400fab:	eb 11                	jmp    400fbe <phase_3+0x7b>
  400fad:	e8 88 04 00 00       	callq  40143a <explode_bomb>
  400fb2:	b8 00 00 00 00       	mov    $0x0,%eax
  400fb7:	eb 05                	jmp    400fbe <phase_3+0x7b>
  400fb9:	b8 37 01 00 00       	mov    $0x137,%eax #input1 = 1
  400fbe:	3b 44 24 0c          	cmp    0xc(%rsp),%eax #比较输入2与数组对应结果
  400fc2:	74 05                	je     400fc9 <phase_3+0x86>
  400fc4:	e8 71 04 00 00       	callq  40143a <explode_bomb>
  400fc9:	48 83 c4 18          	add    $0x18,%rsp
  400fcd:	c3                   	retq   
```

**过程：**

```
(gdb) x/s 0x4025cf
0x4025cf:	"%d %d"
（跳转地址数组）
(gdb) print /x *0x402470
$0 = 0x400f7c
(gdb) print /x *(0x402470 + 0x8)
$1 = 0x400fb9
(gdb) print /x *(0x402470 + 0x10)
$2 = 0x400f83
(gdb) print /x *(0x402470 + 0x18)
$3 = 0x400f8a
(gdb) print /x *(0x402470 + 0x20)
$4 = 0x400f91
(gdb) print /x *(0x402470 + 0x28)
$5 = 0x400f98
(gdb) print /x *(0x402470 + 0x30)
$6 = 0x400f9f
(gdb) print /x *(0x402470 + 0x38)
$7 = 0x400fa6
```

**答案：输入分析中任意一个组合均可，如`3 256`。应该是十进制。**

---

## Phase 4：

**相关汇编代码及分析：**

```assembly
000000000040100c <phase_4>:
  40100c:	48 83 ec 18          	sub    $0x18,%rsp
  401010:	48 8d 4c 24 0c       	lea    0xc(%rsp),%rcx
  401015:	48 8d 54 24 08       	lea    0x8(%rsp),%rdx
  40101a:	be cf 25 40 00       	mov    $0x4025cf,%esi
  40101f:	b8 00 00 00 00       	mov    $0x0,%eax
  401024:	e8 c7 fb ff ff       	callq  400bf0 <__isoc99_sscanf@plt>
  401029:	83 f8 02             	cmp    $0x2,%eax
  40102c:	75 07                	jne    401035 <phase_4+0x29> #说明输入两个数
  40102e:	83 7c 24 08 0e       	cmpl   $0xe,0x8(%rsp)
  401033:	76 05                	jbe    40103a <phase_4+0x2e> #input1 <= 15
  401035:	e8 00 04 00 00       	callq  40143a <explode_bomb> #否则引爆
  40103a:	ba 0e 00 00 00       	mov    $0xe,%edx #14
  40103f:	be 00 00 00 00       	mov    $0x0,%esi #0
  401044:	8b 7c 24 08          	mov    0x8(%rsp),%edi
  401048:	e8 81 ff ff ff       	callq  400fce <func4>
  40104d:	85 c0                	test   %eax,%eax
  40104f:	75 07                	jne    401058 <phase_4+0x4c>
  401051:	83 7c 24 0c 00       	cmpl   $0x0,0xc(%rsp) #input2 = 0
  401056:	74 05                	je     40105d <phase_4+0x51>
  401058:	e8 dd 03 00 00       	callq  40143a <explode_bomb>
  40105d:	48 83 c4 18          	add    $0x18,%rsp
  401061:	c3                   	retq   
0000000000400fce <func4>:
  400fce:	48 83 ec 08          	sub    $0x8,%rsp
  400fd2:	89 d0                	mov    %edx,%eax
  400fd4:	29 f0                	sub    %esi,%eax
  400fd6:	89 c1                	mov    %eax,%ecx
  400fd8:	c1 e9 1f             	shr    $0x1f,%ecx
  400fdb:	01 c8                	add    %ecx,%eax
  400fdd:	d1 f8                	sar    %eax
  400fdf:	8d 0c 30             	lea    (%rax,%rsi,1),%ecx
  400fe2:	39 f9                	cmp    %edi,%ecx #第一次7 : input1
  400fe4:	7e 0c                	jle    400ff2 <func4+0x24> #input1 >= 7
  400fe6:	8d 51 ff             	lea    -0x1(%rcx),%edx
  400fe9:	e8 e0 ff ff ff       	callq  400fce <func4> #调用自身，同理可得3、1、0也可行
  400fee:	01 c0                	add    %eax,%eax
  400ff0:	eb 15                	jmp    401007 <func4+0x39>
  400ff2:	b8 00 00 00 00       	mov    $0x0,%eax
  400ff7:	39 f9                	cmp    %edi,%ecx #第一次7 : input1
  400ff9:	7d 0c                	jge    401007 <func4+0x39> #input1 <= 7
  400ffb:	8d 71 01             	lea    0x1(%rcx),%esi
  400ffe:	e8 cb ff ff ff       	callq  400fce <func4>
  401003:	8d 44 00 01          	lea    0x1(%rax,%rax,1),%eax
  401007:	48 83 c4 08          	add    $0x8,%rsp #input1 = 7可行
  40100b:	c3                   	retq   
```

**过程：** 略

**答案：`7 0` 或 `3 0` 或 `1 0` 或 `0 0`**

---

## Phase 5:

**相关汇编代码及分析：**

```assembly
0000000000401062 <phase_5>:
  401062:	53                   	push   %rbx
  401063:	48 83 ec 20          	sub    $0x20,%rsp
  401067:	48 89 fb             	mov    %rdi,%rbx
  40106a:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  401071:	00 00 
  401073:	48 89 44 24 18       	mov    %rax,0x18(%rsp) #金丝雀值
  401078:	31 c0                	xor    %eax,%eax #置0
  40107a:	e8 9c 02 00 00       	callq  40131b <string_length>
  40107f:	83 f8 06             	cmp    $0x6,%eax
  401082:	74 4e                	je     4010d2 <phase_5+0x70> #字符串长度为6
  401084:	e8 b1 03 00 00       	callq  40143a <explode_bomb>
  401089:	eb 47                	jmp    4010d2 <phase_5+0x70>
  40108b:	0f b6 0c 03          	movzbl (%rbx,%rax,1),%ecx
  40108f:	88 0c 24             	mov    %cl,(%rsp)
  401092:	48 8b 14 24          	mov    (%rsp),%rdx #转移输入的每一个字符
  401096:	83 e2 0f             	and    $0xf,%edx #字符与0xf作&运算，相当于取低四位
  401099:	0f b6 92 b0 24 40 00 	movzbl 0x4024b0(%rdx),%edx #映射为地址
  4010a0:	88 54 04 10          	mov    %dl,0x10(%rsp,%rax,1) #获取对应字符
  4010a4:	48 83 c0 01          	add    $0x1,%rax
  4010a8:	48 83 f8 06          	cmp    $0x6,%rax #循环控制，直至六个字符均处理完
  4010ac:	75 dd                	jne    40108b <phase_5+0x29>
  4010ae:	c6 44 24 16 00       	movb   $0x0,0x16(%rsp)
  4010b3:	be 5e 24 40 00       	mov    $0x40245e,%esi #答案字符串地址
  4010b8:	48 8d 7c 24 10       	lea    0x10(%rsp),%rdi #处理后的输入字符串
  4010bd:	e8 76 02 00 00       	callq  401338 <strings_not_equal> #比较
  4010c2:	85 c0                	test   %eax,%eax
  4010c4:	74 13                	je     4010d9 <phase_5+0x77>
  4010c6:	e8 6f 03 00 00       	callq  40143a <explode_bomb>
  4010cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
  4010d0:	eb 07                	jmp    4010d9 <phase_5+0x77>
  4010d2:	b8 00 00 00 00       	mov    $0x0,%eax
  4010d7:	eb b2                	jmp    40108b <phase_5+0x29>
  4010d9:	48 8b 44 24 18       	mov    0x18(%rsp),%rax
  4010de:	64 48 33 04 25 28 00 	xor    %fs:0x28,%rax
  4010e5:	00 00 
  4010e7:	74 05                	je     4010ee <phase_5+0x8c>
  4010e9:	e8 42 fa ff ff       	callq  400b30 <__stack_chk_fail@plt>
  4010ee:	48 83 c4 20          	add    $0x20,%rsp
  4010f2:	5b                   	pop    %rbx
  4010f3:	c3                   	retq   
  #调用的两个函数在Phase1中分析过，此处略
```

**过程：**

```
So you got that one.  Try this one.
test12

Breakpoint 1, 0x000000000040143a in explode_bomb ()
(gdb) x/s 0x4024b0
0x4024b0 <array.3449>:	"maduiersnfotvbylSo you think you can stop the bomb with ctrl-c, do you?"
(gdb) x/s 0x40245e
0x40245e:	"flyers"

对应各字符与0xf与运算的结果#地址偏移量）:9 15 14 5 6 7
转换为对应字符表示：9 ? > 5 6 7
```

**答案：`9?>567`**

---

## Phase 6:

**相关汇编代码及分析：**

```assembly
00000000004010f4 <phase_6>:
  4010f4:	41 56                	push   %r14
  4010f6:	41 55                	push   %r13
  4010f8:	41 54                	push   %r12
  4010fa:	55                   	push   %rbp
  4010fb:	53                   	push   %rbx
  4010fc:	48 83 ec 50          	sub    $0x50,%rsp
  401100:	49 89 e5             	mov    %rsp,%r13 #保存
  401103:	48 89 e6             	mov    %rsp,%rsi
  401106:	e8 51 03 00 00       	callq  40145c <read_six_numbers>
  40110b:	49 89 e6             	mov    %rsp,%r14 #读入6个数后的栈指针保存
  40110e:	41 bc 00 00 00 00    	mov    $0x0,%r12d
  #外层循环开始
  401114:	4c 89 ed             	mov    %r13,%rbp #栈指针
  401117:	41 8b 45 00          	mov    0x0(%r13),%eax #取数
  40111b:	83 e8 01             	sub    $0x1,%eax
  40111e:	83 f8 05             	cmp    $0x5,%eax
  401121:	76 05                	jbe    401128 <phase_6+0x34> #每一个数范围1~6 
  401123:	e8 12 03 00 00       	callq  40143a <explode_bomb>
  401128:	41 83 c4 01          	add    $0x1,%r12d #外层循环控制变量
  40112c:	41 83 fc 06          	cmp    $0x6,%r12d
  401130:	74 21                	je     401153 <phase_6+0x5f>
  	#内层循环开始
  401132:	44 89 e3             	mov    %r12d,%ebx
  401135:	48 63 c3             	movslq %ebx,%rax
  401138:	8b 04 84             	mov    (%rsp,%rax,4),%eax #依次读数
  40113b:	39 45 00             	cmp    %eax,0x0(%rbp) #数比较
  40113e:	75 05                	jne    401145 <phase_6+0x51> #数要求互不相等
  401140:	e8 f5 02 00 00       	callq  40143a <explode_bomb>
  401145:	83 c3 01             	add    $0x1,%ebx #内层循环控制变量
  401148:	83 fb 05             	cmp    $0x5,%ebx
  40114b:	7e e8                	jle    401135 <phase_6+0x41>
  	#内层循环结束
  40114d:	49 83 c5 04          	add    $0x4,%r13
  401151:	eb c1                	jmp    401114 <phase_6+0x20>
  #外层循环结束
  #以上的循环体保证6个数互不相等且取值范围为1~6
  401153:	48 8d 74 24 18       	lea    0x18(%rsp),%rsi #第一个数
  401158:	4c 89 f0             	mov    %r14,%rax
  40115b:	b9 07 00 00 00       	mov    $0x7,%ecx
  401160:	89 ca                	mov    %ecx,%edx
  #循环体1开始
  401162:	2b 10                	sub    (%rax),%edx #7-每一个数
  401164:	89 10                	mov    %edx,(%rax) #写回栈
  401166:	48 83 c0 04          	add    $0x4,%rax #指向下一个数
  40116a:	48 39 f0             	cmp    %rsi,%rax
  40116d:	75 f1                	jne    401160 <phase_6+0x6c> #循环直至最后一个数
  #循环体1结束
  #数对应地址存栈操作开始
  40116f:	be 00 00 00 00       	mov    $0x0,%esi
  401174:	eb 21                	jmp    401197 <phase_6+0xa3>
  401176:	48 8b 52 08          	mov    0x8(%rdx),%rdx
  40117a:	83 c0 01             	add    $0x1,%eax
  40117d:	39 c8                	cmp    %ecx,%eax
  40117f:	75 f5                	jne    401176 <phase_6+0x82>
  401181:	eb 05                	jmp    401188 <phase_6+0x94>
  401183:	ba d0 32 60 00       	mov    $0x6032d0,%edx
  401188:	48 89 54 74 20       	mov    %rdx,0x20(%rsp,%rsi,2) #栈存数
  #数    存栈值                              数    存栈值
  #1    0x6032d0                            2    *(0x6032d0 + 0x8) = 0x6032e0
  #3    *(0x6032e0 + 0x8) = 0x6032f0        4    *(0x6032f0 + 0x8) = 0x603300
  #5    *(0x6033f0 + 0x8) = 0x603310        6    *(0x603310 + 0x8) = 0x603320
  #按照顺序放在栈的%rsp+0x20到%rsp+0x48处
  40118d:	48 83 c6 04          	add    $0x4,%rsi
  401191:	48 83 fe 18          	cmp    $0x18,%rsi #与24比较，循环控制
  401195:	74 14                	je     4011ab <phase_6+0xb7>
  401197:	8b 0c 34             	mov    (%rsp,%rsi,1),%ecx #取每一个数
  40119a:	83 f9 01             	cmp    $0x1,%ecx
  40119d:	7e e4                	jle    401183 <phase_6+0x8f> #判断数==1
  40119f:	b8 01 00 00 00       	mov    $0x1,%eax
  4011a4:	ba d0 32 60 00       	mov    $0x6032d0,%edx
  4011a9:	eb cb                	jmp    401176 <phase_6+0x82>
  #数对应地址存栈操作结束
  4011ab:	48 8b 5c 24 20       	mov    0x20(%rsp),%rbx #*(%rsp + 32)
  4011b0:	48 8d 44 24 28       	lea    0x28(%rsp),%rax #%rsp + 40
  4011b5:	48 8d 74 24 50       	lea    0x50(%rsp),%rsi #%rsp + 80
  4011ba:	48 89 d9             	mov    %rbx,%rcx
  4011bd:	48 8b 10             	mov    (%rax),%rdx
  4011c0:	48 89 51 08          	mov    %rdx,0x8(%rcx)
  4011c4:	48 83 c0 08          	add    $0x8,%rax
  4011c8:	48 39 f0             	cmp    %rsi,%rax
  4011cb:	74 05                	je     4011d2 <phase_6+0xde>
  4011cd:	48 89 d1             	mov    %rdx,%rcx
  4011d0:	eb eb                	jmp    4011bd <phase_6+0xc9>
  4011d2:	48 c7 42 08 00 00 00 	movq   $0x0,0x8(%rdx)
  4011d9:	00 
  4011da:	bd 05 00 00 00       	mov    $0x5,%ebp
  4011df:	48 8b 43 08          	mov    0x8(%rbx),%rax
  4011e3:	8b 00                	mov    (%rax),%eax
  4011e5:	39 03                	cmp    %eax,(%rbx)
  4011e7:	7d 05                	jge    4011ee <phase_6+0xfa> #链表数据降序
  4011e9:	e8 4c 02 00 00       	callq  40143a <explode_bomb>
  4011ee:	48 8b 5b 08          	mov    0x8(%rbx),%rbx
  4011f2:	83 ed 01             	sub    $0x1,%ebp
  4011f5:	75 e8                	jne    4011df <phase_6+0xeb>
  4011f7:	48 83 c4 50          	add    $0x50,%rsp
  4011fb:	5b                   	pop    %rbx
  4011fc:	5d                   	pop    %rbp
  4011fd:	41 5c                	pop    %r12
  4011ff:	41 5d                	pop    %r13
  401201:	41 5e                	pop    %r14
  401203:	c3                   	retq   
```

**过程：** 略

**答案： `4 3 2 1 6 5`**

---

## Secret Phase彩蛋及更详细的过程

**参考知乎专栏文章：**[Introduction to CSAPP（十九）：这可能是你能找到的分析最全的Bomblab了](https://zhuanlan.zhihu.com/p/104130161)

