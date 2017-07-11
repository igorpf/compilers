	.file	"x.c"
	.globl	x
	.data
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	3
	.comm	y,4,4
	.comm	z,4,4
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	y(%rip), %edx
	movl	x(%rip), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, z(%rip)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
