
test:	file format Mach-O 32-bit i386

Disassembly of section __TEXT,__text:
__text:
    1f60:	55 	pushl	%ebp
    1f61:	89 e5 	movl	%esp, %ebp
    1f63:	56 	pushl	%esi
    1f64:	50 	pushl	%eax
    1f65:	e8 00 00 00 00 	calll	0 <_main+0xA>
    1f6a:	58 	popl	%eax
    1f6b:	8d b0 3c 00 00 00 	leal	60(%eax), %esi
    1f71:	66 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	nopw	%cs:(%eax,%eax)
    1f80:	89 34 24 	movl	%esi, (%esp)
    1f83:	e8 02 00 00 00 	calll	2
    1f88:	eb f6 	jmp	-10 <_main+0x20>

_main:
    1f60:	55 	pushl	%ebp
    1f61:	89 e5 	movl	%esp, %ebp
    1f63:	56 	pushl	%esi
    1f64:	50 	pushl	%eax

    1f65:	e8 00 00 00 00 	calll	0 <_main+0xA>
    1f6a:	58 	popl	%eax
    1f6b:	8d b0 3c 00 00 00 	leal	60(%eax), %esi
    1f71:	66 66 66 66 66 66 2e 0f 1f 84 00 00 00 00 00 	nopw	%cs:(%eax,%eax)
    1f80:	89 34 24 	movl	%esi, (%esp)
    1f83:	e8 02 00 00 00 	calll	2
    1f88:	eb f6 	jmp	-10 <_main+0x20>


Disassembly of section __TEXT,__symbol_stub:
__symbol_stub:
    1f8a:	ff 25 08 20 00 00 	jmpl	*8200
Disassembly of section __TEXT,__stub_helper:
__stub_helper:
    1f90:	68 04 20 00 00 	pushl	$8196
    1f95:	ff 25 00 20 00 00 	jmpl	*8192
    1f9b:	90 	nop
    1f9c:	68 00 00 00 00 	pushl	$0
    1fa1:	e9 ea ff ff ff 	jmp	-22 <__stub_helper>
Disassembly of section __TEXT,__cstring:
__cstring:
    1fa6:	68 65 6c 6c 6f 	pushl	$1869376613
    1fab:	00  <unknown>
Disassembly of section __TEXT,__unwind_info:
__unwind_info:
    1fac:	01 00 	addl	%eax, (%eax)
    1fae:	00 00 	addb	%al, (%eax)
    1fb0:	1c 00 	sbbb	$0, %al
    1fb2:	00 00 	addb	%al, (%eax)
    1fb4:	00 00 	addb	%al, (%eax)
    1fb6:	00 00 	addb	%al, (%eax)
    1fb8:	1c 00 	sbbb	$0, %al
    1fba:	00 00 	addb	%al, (%eax)
    1fbc:	00 00 	addb	%al, (%eax)
    1fbe:	00 00 	addb	%al, (%eax)
    1fc0:	1c 00 	sbbb	$0, %al
    1fc2:	00 00 	addb	%al, (%eax)
    1fc4:	02 00 	addb	(%eax), %al
    1fc6:	00 00 	addb	%al, (%eax)
    1fc8:	60 	pushal
    1fc9:	0f 00 00 	sldtw	(%eax)
    1fcc:	34 00 	xorb	$0, %al
    1fce:	00 00 	addb	%al, (%eax)
    1fd0:	34 00 	xorb	$0, %al
    1fd2:	00 00 	addb	%al, (%eax)
    1fd4:	8b 0f 	movl	(%edi), %ecx
    1fd6:	00 00 	addb	%al, (%eax)
    1fd8:	00 00 	addb	%al, (%eax)
    1fda:	00 00 	addb	%al, (%eax)
    1fdc:	34 00 	xorb	$0, %al
    1fde:	00 00 	addb	%al, (%eax)
    1fe0:	03 00 	addl	(%eax), %eax
    1fe2:	00 00 	addb	%al, (%eax)
    1fe4:	0c 00 	orb	$0, %al
    1fe6:	01 00 	addl	%eax, (%eax)
    1fe8:	10 00 	adcb	%al, (%eax)
    1fea:	01 00 	addl	%eax, (%eax)
    1fec:	00 00 	addb	%al, (%eax)
    1fee:	00 00 	addb	%al, (%eax)
    1ff0:	00 00 	addb	%al, (%eax)
    1ff2:	00 00 	addb	%al, (%eax)
Disassembly of section __DATA,__nl_symbol_ptr:
__nl_symbol_ptr:
    2000:	00 00 	addb	%al, (%eax)
    2002:	00 00 	addb	%al, (%eax)
    2004:	00 00 	addb	%al, (%eax)
    2006:	00 00 	addb	%al, (%eax)
Disassembly of section __DATA,__la_symbol_ptr:
__la_symbol_ptr:
    2008:	9c 	pushfl
    2009:	1f 	popl	%ds
    200a:	00 00 	addb	%al, (%eax)
