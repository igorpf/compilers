	.file	"x.c"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	movl	z(%rip), %edx
	movl	%edx, %eax
	subl	y(%rip), %eax
	movl	%eax, x(%rip)
	addl	%edx, %eax
	movl	%eax, y(%rip)
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	z
	.data
	.align 4
	.type	z, @object
	.size	z, 4
z:
	.long	4
	.globl	y
	.align 4
	.type	y, @object
	.size	y, 4
y:
	.long	2
	.globl	x
	.bss
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.zero	4
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
