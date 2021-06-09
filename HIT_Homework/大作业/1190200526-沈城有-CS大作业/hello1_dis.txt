
hello：     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000401000 <_init>:
  401000:	f3 0f 1e fa          	endbr64 
  401004:	48 83 ec 08          	sub    $0x8,%rsp
  401008:	48 8b 05 e9 2f 00 00 	mov    0x2fe9(%rip),%rax        # 403ff8 <__gmon_start__>
  40100f:	48 85 c0             	test   %rax,%rax
  401012:	74 02                	je     401016 <_init+0x16>
  401014:	ff d0                	callq  *%rax
  401016:	48 83 c4 08          	add    $0x8,%rsp
  40101a:	c3                   	retq   

Disassembly of section .plt:

0000000000401020 <.plt>:
  401020:	ff 35 e2 2f 00 00    	pushq  0x2fe2(%rip)        # 404008 <_GLOBAL_OFFSET_TABLE_+0x8>
  401026:	f2 ff 25 e3 2f 00 00 	bnd jmpq *0x2fe3(%rip)        # 404010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40102d:	0f 1f 00             	nopl   (%rax)
  401030:	f3 0f 1e fa          	endbr64 
  401034:	68 00 00 00 00       	pushq  $0x0
  401039:	f2 e9 e1 ff ff ff    	bnd jmpq 401020 <.plt>
  40103f:	90                   	nop
  401040:	f3 0f 1e fa          	endbr64 
  401044:	68 01 00 00 00       	pushq  $0x1
  401049:	f2 e9 d1 ff ff ff    	bnd jmpq 401020 <.plt>
  40104f:	90                   	nop
  401050:	f3 0f 1e fa          	endbr64 
  401054:	68 02 00 00 00       	pushq  $0x2
  401059:	f2 e9 c1 ff ff ff    	bnd jmpq 401020 <.plt>
  40105f:	90                   	nop
  401060:	f3 0f 1e fa          	endbr64 
  401064:	68 03 00 00 00       	pushq  $0x3
  401069:	f2 e9 b1 ff ff ff    	bnd jmpq 401020 <.plt>
  40106f:	90                   	nop
  401070:	f3 0f 1e fa          	endbr64 
  401074:	68 04 00 00 00       	pushq  $0x4
  401079:	f2 e9 a1 ff ff ff    	bnd jmpq 401020 <.plt>
  40107f:	90                   	nop

Disassembly of section .plt.sec:

0000000000401080 <puts@plt>:
  401080:	f3 0f 1e fa          	endbr64 
  401084:	f2 ff 25 8d 2f 00 00 	bnd jmpq *0x2f8d(%rip)        # 404018 <puts@GLIBC_2.2.5>
  40108b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000401090 <printf@plt>:
  401090:	f3 0f 1e fa          	endbr64 
  401094:	f2 ff 25 85 2f 00 00 	bnd jmpq *0x2f85(%rip)        # 404020 <printf@GLIBC_2.2.5>
  40109b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000004010a0 <getchar@plt>:
  4010a0:	f3 0f 1e fa          	endbr64 
  4010a4:	f2 ff 25 7d 2f 00 00 	bnd jmpq *0x2f7d(%rip)        # 404028 <getchar@GLIBC_2.2.5>
  4010ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000004010b0 <exit@plt>:
  4010b0:	f3 0f 1e fa          	endbr64 
  4010b4:	f2 ff 25 75 2f 00 00 	bnd jmpq *0x2f75(%rip)        # 404030 <exit@GLIBC_2.2.5>
  4010bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000004010c0 <sleep@plt>:
  4010c0:	f3 0f 1e fa          	endbr64 
  4010c4:	f2 ff 25 6d 2f 00 00 	bnd jmpq *0x2f6d(%rip)        # 404038 <sleep@GLIBC_2.2.5>
  4010cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000004010d0 <_start>:
  4010d0:	f3 0f 1e fa          	endbr64 
  4010d4:	31 ed                	xor    %ebp,%ebp
  4010d6:	49 89 d1             	mov    %rdx,%r9
  4010d9:	5e                   	pop    %rsi
  4010da:	48 89 e2             	mov    %rsp,%rdx
  4010dd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4010e1:	50                   	push   %rax
  4010e2:	54                   	push   %rsp
  4010e3:	49 c7 c0 00 12 40 00 	mov    $0x401200,%r8
  4010ea:	48 c7 c1 90 11 40 00 	mov    $0x401190,%rcx
  4010f1:	48 c7 c7 05 11 40 00 	mov    $0x401105,%rdi
  4010f8:	ff 15 f2 2e 00 00    	callq  *0x2ef2(%rip)        # 403ff0 <__libc_start_main@GLIBC_2.2.5>
  4010fe:	f4                   	hlt    
  4010ff:	90                   	nop

0000000000401100 <_dl_relocate_static_pie>:
  401100:	f3 0f 1e fa          	endbr64 
  401104:	c3                   	retq   

0000000000401105 <main>:
  401105:	f3 0f 1e fa          	endbr64 
  401109:	55                   	push   %rbp
  40110a:	48 89 e5             	mov    %rsp,%rbp
  40110d:	48 83 ec 20          	sub    $0x20,%rsp
  401111:	89 7d ec             	mov    %edi,-0x14(%rbp)
  401114:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
  401118:	83 7d ec 03          	cmpl   $0x3,-0x14(%rbp)
  40111c:	74 16                	je     401134 <main+0x2f>
  40111e:	48 8d 3d df 0e 00 00 	lea    0xedf(%rip),%rdi        # 402004 <_IO_stdin_used+0x4>
  401125:	e8 56 ff ff ff       	callq  401080 <puts@plt>
  40112a:	bf 01 00 00 00       	mov    $0x1,%edi
  40112f:	e8 7c ff ff ff       	callq  4010b0 <exit@plt>
  401134:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
  40113b:	eb 3b                	jmp    401178 <main+0x73>
  40113d:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  401141:	48 83 c0 10          	add    $0x10,%rax
  401145:	48 8b 10             	mov    (%rax),%rdx
  401148:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
  40114c:	48 83 c0 08          	add    $0x8,%rax
  401150:	48 8b 00             	mov    (%rax),%rax
  401153:	48 89 c6             	mov    %rax,%rsi
  401156:	48 8d 3d c5 0e 00 00 	lea    0xec5(%rip),%rdi        # 402022 <_IO_stdin_used+0x22>
  40115d:	b8 00 00 00 00       	mov    $0x0,%eax
  401162:	e8 29 ff ff ff       	callq  401090 <printf@plt>
  401167:	8b 05 d7 2e 00 00    	mov    0x2ed7(%rip),%eax        # 404044 <sleepsecs>
  40116d:	89 c7                	mov    %eax,%edi
  40116f:	e8 4c ff ff ff       	callq  4010c0 <sleep@plt>
  401174:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
  401178:	83 7d fc 09          	cmpl   $0x9,-0x4(%rbp)
  40117c:	7e bf                	jle    40113d <main+0x38>
  40117e:	e8 1d ff ff ff       	callq  4010a0 <getchar@plt>
  401183:	b8 00 00 00 00       	mov    $0x0,%eax
  401188:	c9                   	leaveq 
  401189:	c3                   	retq   
  40118a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000401190 <__libc_csu_init>:
  401190:	f3 0f 1e fa          	endbr64 
  401194:	41 57                	push   %r15
  401196:	4c 8d 3d b3 2c 00 00 	lea    0x2cb3(%rip),%r15        # 403e50 <_DYNAMIC>
  40119d:	41 56                	push   %r14
  40119f:	49 89 d6             	mov    %rdx,%r14
  4011a2:	41 55                	push   %r13
  4011a4:	49 89 f5             	mov    %rsi,%r13
  4011a7:	41 54                	push   %r12
  4011a9:	41 89 fc             	mov    %edi,%r12d
  4011ac:	55                   	push   %rbp
  4011ad:	48 8d 2d 9c 2c 00 00 	lea    0x2c9c(%rip),%rbp        # 403e50 <_DYNAMIC>
  4011b4:	53                   	push   %rbx
  4011b5:	4c 29 fd             	sub    %r15,%rbp
  4011b8:	48 83 ec 08          	sub    $0x8,%rsp
  4011bc:	e8 3f fe ff ff       	callq  401000 <_init>
  4011c1:	48 c1 fd 03          	sar    $0x3,%rbp
  4011c5:	74 1f                	je     4011e6 <__libc_csu_init+0x56>
  4011c7:	31 db                	xor    %ebx,%ebx
  4011c9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  4011d0:	4c 89 f2             	mov    %r14,%rdx
  4011d3:	4c 89 ee             	mov    %r13,%rsi
  4011d6:	44 89 e7             	mov    %r12d,%edi
  4011d9:	41 ff 14 df          	callq  *(%r15,%rbx,8)
  4011dd:	48 83 c3 01          	add    $0x1,%rbx
  4011e1:	48 39 dd             	cmp    %rbx,%rbp
  4011e4:	75 ea                	jne    4011d0 <__libc_csu_init+0x40>
  4011e6:	48 83 c4 08          	add    $0x8,%rsp
  4011ea:	5b                   	pop    %rbx
  4011eb:	5d                   	pop    %rbp
  4011ec:	41 5c                	pop    %r12
  4011ee:	41 5d                	pop    %r13
  4011f0:	41 5e                	pop    %r14
  4011f2:	41 5f                	pop    %r15
  4011f4:	c3                   	retq   
  4011f5:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
  4011fc:	00 00 00 00 

0000000000401200 <__libc_csu_fini>:
  401200:	f3 0f 1e fa          	endbr64 
  401204:	c3                   	retq   

Disassembly of section .fini:

0000000000401208 <_fini>:
  401208:	f3 0f 1e fa          	endbr64 
  40120c:	48 83 ec 08          	sub    $0x8,%rsp
  401210:	48 83 c4 08          	add    $0x8,%rsp
  401214:	c3                   	retq   
