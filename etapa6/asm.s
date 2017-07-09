
.LC0:
	.string	" %d"
##TAC_VAR_DEC
	.globl 	_a
_a:
	.long 	5
##TAC_VEC_DEC
	.comm _v,8,4
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm  _232,4,4
	movl $232, _232(%rip)
##TAC_VEC_DEC_INIT
	.globl 	_z
_z:
	.long 	1
	.long 	232
##TAC_BEGIN_FUN
	.globl main
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_SYMBOL
	.comm  _1,4,4
.comm ___TEMPORARY0__,4,4
.comm ___TEMPORARY1__,4,4
	movl $1, _1(%rip)
## TAC_VEC_READ
	movl _1(%rip), %eax 
	movl _z(,%eax,4), %eax 
	movl %eax, ___TEMPORARY0__(%rip) 
 movl	%eax, %esi
movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
##TAC_MOV
## TAC_SYMBOL
## TAC_SYMBOL
## TAC_ADD
	movl _a(%rip), %eax
	addl _a(%rip), %eax
	movl %eax, ___TEMPORARY1__(%rip)
## TAC_RETURN
	movl  ___TEMPORARY1__(%rip), %eax
	leave
	ret 
	leave
	ret 
	.cfi_endproc
