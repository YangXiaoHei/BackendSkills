
test:	file format Mach-O 64-bit x86-64

Disassembly of section __TEXT,__text:
__text:
100000f50:	55 	pushq	%rbp
100000f51:	48 89 e5 	movq	%rsp, %rbp
100000f54:	48 83 ec 10 	subq	$16, %rsp
100000f58:	c7 45 fc 00 00 00 00 	movl	$0, -4(%rbp)
100000f5f:	83 3d b2 00 00 00 00 	cmpl	$0, 178(%rip)
100000f66:	0f 84 16 00 00 00 	je	22 <_main+0x32>
100000f6c:	48 8d 3d 37 00 00 00 	leaq	55(%rip), %rdi
100000f73:	b0 00 	movb	$0, %al
100000f75:	e8 10 00 00 00 	callq	16
100000f7a:	89 45 f8 	movl	%eax, -8(%rbp)
100000f7d:	e9 dd ff ff ff 	jmp	-35 <_main+0xF>
100000f82:	31 c0 	xorl	%eax, %eax
100000f84:	48 83 c4 10 	addq	$16, %rsp
100000f88:	5d 	popq	%rbp
100000f89:	c3 	retq

_main:
100000f50:	55 	pushq	%rbp
100000f51:	48 89 e5 	movq	%rsp, %rbp
100000f54:	48 83 ec 10 	subq	$16, %rsp
100000f58:	c7 45 fc 00 00 00 00 	movl	$0, -4(%rbp)
100000f5f:	83 3d b2 00 00 00 00 	cmpl	$0, 178(%rip)
100000f66:	0f 84 16 00 00 00 	je	22 <_main+0x32>
100000f6c:	48 8d 3d 37 00 00 00 	leaq	55(%rip), %rdi
100000f73:	b0 00 	movb	$0, %al
100000f75:	e8 10 00 00 00 	callq	16
100000f7a:	89 45 f8 	movl	%eax, -8(%rbp)
100000f7d:	e9 dd ff ff ff 	jmp	-35 <_main+0xF>
100000f82:	31 c0 	xorl	%eax, %eax
100000f84:	48 83 c4 10 	addq	$16, %rsp
100000f88:	5d 	popq	%rbp
100000f89:	c3 	retq
Disassembly of section __TEXT,__stubs:
__stubs:
100000f8a:	ff 25 80 00 00 00 	jmpq	*128(%rip)
Disassembly of section __TEXT,__stub_helper:
__stub_helper:
100000f90:	4c 8d 1d 71 00 00 00 	leaq	113(%rip), %r11
100000f97:	41 53 	pushq	%r11
100000f99:	ff 25 61 00 00 00 	jmpq	*97(%rip)
100000f9f:	90 	nop
100000fa0:	68 00 00 00 00 	pushq	$0
100000fa5:	e9 e6 ff ff ff 	jmp	-26 <__stub_helper>
Disassembly of section __TEXT,__cstring:
__cstring:
100000faa:	68 65 6c 6c 6f 	pushq	$1869376613
100000faf:	0a 00 	orb	(%rax), %al
Disassembly of section __TEXT,__unwind_info:
__unwind_info:
100000fb4:	01 00 	addl	%eax, (%rax)
100000fb6:	00 00 	addb	%al, (%rax)
100000fb8:	1c 00 	sbbb	$0, %al
100000fba:	00 00 	addb	%al, (%rax)
100000fbc:	00 00 	addb	%al, (%rax)
100000fbe:	00 00 	addb	%al, (%rax)
100000fc0:	1c 00 	sbbb	$0, %al
100000fc2:	00 00 	addb	%al, (%rax)
100000fc4:	00 00 	addb	%al, (%rax)
100000fc6:	00 00 	addb	%al, (%rax)
100000fc8:	1c 00 	sbbb	$0, %al
100000fca:	00 00 	addb	%al, (%rax)
100000fcc:	02 00 	addb	(%rax), %al
100000fce:	00 00 	addb	%al, (%rax)
100000fd0:	50 	pushq	%rax
100000fd1:	0f 00 00 	sldtw	(%rax)
100000fd4:	34 00 	xorb	$0, %al
100000fd6:	00 00 	addb	%al, (%rax)
100000fd8:	34 00 	xorb	$0, %al
100000fda:	00 00 	addb	%al, (%rax)
100000fdc:	8b 0f 	movl	(%rdi), %ecx
100000fde:	00 00 	addb	%al, (%rax)
100000fe0:	00 00 	addb	%al, (%rax)
100000fe2:	00 00 	addb	%al, (%rax)
100000fe4:	34 00 	xorb	$0, %al
100000fe6:	00 00 	addb	%al, (%rax)
100000fe8:	03 00 	addl	(%rax), %eax
100000fea:	00 00 	addb	%al, (%rax)
100000fec:	0c 00 	orb	$0, %al
100000fee:	01 00 	addl	%eax, (%rax)
100000ff0:	10 00 	adcb	%al, (%rax)
100000ff2:	01 00 	addl	%eax, (%rax)
100000ff4:	00 00 	addb	%al, (%rax)
100000ff6:	00 00 	addb	%al, (%rax)
100000ff8:	00 00 	addb	%al, (%rax)
100000ffa:	00 01 	addb	%al, (%rcx)
Disassembly of section __DATA,__nl_symbol_ptr:
__nl_symbol_ptr:
100001000:	00 00 	addb	%al, (%rax)
100001002:	00 00 	addb	%al, (%rax)
100001004:	00 00 	addb	%al, (%rax)
100001006:	00 00 	addb	%al, (%rax)
100001008:	00 00 	addb	%al, (%rax)
10000100a:	00 00 	addb	%al, (%rax)
10000100c:	00 00 	addb	%al, (%rax)
10000100e:	00 00 	addb	%al, (%rax)
Disassembly of section __DATA,__la_symbol_ptr:
__la_symbol_ptr:
100001010:	a0  <unknown>
100001011:	0f 00 00 	sldtw	(%rax)
100001014:	01 00 	addl	%eax, (%rax)
100001016:	00 00 	addb	%al, (%rax)
Disassembly of section __DATA,__data:
_n:
100001018:	05  <unknown>
100001019:	00 00 	addb	%al, (%rax)
10000101b:	00  <unknown>
