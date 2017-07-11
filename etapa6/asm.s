##TAC_VAR_DEC
	.globl 	_a
	.data
_a:
	.long 	123
##TAC_VEC_DEC
	.comm _v,8,4
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm _2,4,4
	movl $2, _2(%rip)
##TAC_VEC_DEC_INIT
	.globl 	_z
	.data
_z:
	.long 	1
	.long 	2
##TAC_PARAM
##TAC_PARAM
##TAC_BEGIN_FUN
	.globl main
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
##TAC_PRINT
	.comm _1,4,4 ##4
	movl $1, _1(%rip)
	movl	_1(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
	.comm _2,4,4
	movl $2, _2(%rip)
##TAC_PRINT
	.comm _2,4,4 ##4
	movl $2, _2(%rip)
	movl	_2(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
	.comm _123,4,4
	movl $123, _123(%rip)
## TAC_SYMBOL
	.comm _13,4,4
	movl $13, _13(%rip)
## TAC_ADD
	.comm ___TEMPORARY0__,4,4
	movl _123(%rip), %eax
	addl _13(%rip), %eax
	movl %eax, ___TEMPORARY0__(%rip)
## TAC_MOV
	movl ___TEMPORARY0__(%rip), %eax 
	movl %eax, _a(%rip) 
## TAC_SYMBOL
	.comm _0,4,4
	movl $0, _0(%rip)
## TAC_SYMBOL
	.comm _60,4,4
	movl $60, _60(%rip)
##TAC_VEC_WRITE
	movl _60(%rip), %eax 
	movl %eax, _v+0(%rip)
##TAC_READ
	movl $_a, %edi
	call gets
	movl $_a, %edi
	call atoi
	movl %eax, _a(%rip)
## TAC_SYMBOL
##TAC_PRINT
	movl	_a(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
## TAC_SYMBOL
## TAC_ADD
	.comm ___TEMPORARY1__,4,4
	movl _a(%rip), %eax
	addl _a(%rip), %eax
	movl %eax, ___TEMPORARY1__(%rip)
## TAC_RETURN
	movl ___TEMPORARY1__(%rip), %eax
	leave
	ret 
##TAC_END_FUN
	leave
	ret 
	.cfi_endproc
.LC0:
	.string "%d\n"
