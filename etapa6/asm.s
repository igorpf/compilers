##TAC_VAR_DEC
	.globl 	_a
_a:
	.long 	123
##TAC_VEC_DEC
	.comm _v,8,4
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm  _2,4,4
	movl $2, _2(%rip)
##TAC_VEC_DEC_INIT
	.globl 	_z
_z:
	.long 	1
	.long 	2
##TAC_BEGIN_FUN
	.globl _main
_main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
##TAC_ARG
## TAC_SYMBOL
	.comm  _2,4,4
	movl $2, _2(%rip)
##TAC_ARG
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
##TAC_ARG
## TAC_SYMBOL
	.comm  _2,4,4
	movl $2, _2(%rip)
##TAC_ARG
##TAC_CALL
##TAC_ARG
##TAC_PRINT
## TAC_SYMBOL
	.comm  _123,4,4
	movl $123, _123(%rip)
## TAC_SYMBOL
	.comm  _13,4,4
	movl $13, _13(%rip)
## TAC_ADD
	movl _123(%rip), %eax
	addl _13(%rip), %eax
	movl %eax, ___TEMPORARY1__(%rip)
## TAC_MOV
	movl _a(%rip), %eax 
	movl %eax, ___TEMPORARY1__(%rip) 
## TAC_SYMBOL
	.comm  _2,4,4
	movl $2, _2(%rip)
## TAC_SYMBOL
	.comm  _10,4,4
	movl $10, _10(%rip)
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
TAC_SUB## TAC_VEC_READ
	movl ___TEMPORARY2__(%rip), %eax 
	movl _v(,%eax,4), %eax 
	movl %eax, ___TEMPORARY3__(%rip) 
##TAC_MOV_IND
## TAC_SYMBOL
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm  _10,4,4
	movl $10, _10(%rip)
## TAC_MOV
	movl _a(%rip), %eax 
	movl %eax, _1(%rip) 
## TAC_LABEL
__LABEL1__:
TAC_LE##TAC_IFZ
## TAC_SYMBOL
	.comm  _"i",4,4
	movl $"i", _"i"(%rip)
##TAC_ARG
## TAC_SYMBOL
	.comm  _" ",4,4
	movl $" ", _" "(%rip)
##TAC_ARG
##TAC_PRINT
## TAC_ADD
	movl _a(%rip), %eax
	addl _1(%rip), %eax
	movl %eax, _a(%rip)
##TAC_JUMP
## TAC_LABEL
__LABEL0__:
##TAC_READ
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm  _2,4,4
	movl $2, _2(%rip)
TAC_GT##TAC_IFZ
## TAC_SYMBOL
	.comm  _"aaa",4,4
	movl $"aaa", _"aaa"(%rip)
##TAC_ARG
##TAC_PRINT
##TAC_JUMP
## TAC_LABEL
__LABEL2__:
## TAC_SYMBOL
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
## TAC_ADD
	movl _a(%rip), %eax
	addl _1(%rip), %eax
	movl %eax, ___TEMPORARY6__(%rip)
## TAC_MOV
	movl _a(%rip), %eax 
	movl %eax, ___TEMPORARY6__(%rip) 
## TAC_LABEL
__LABEL3__:
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
##TAC_ARG
## TAC_SYMBOL
	.comm  _2,4,4
	movl $2, _2(%rip)
##TAC_ARG
##TAC_CALL
## TAC_MOV
	movl _a(%rip), %eax 
	movl %eax, ___TEMPORARY7__(%rip) 
## TAC_SYMBOL
## TAC_SYMBOL
## TAC_ADD
	movl _a(%rip), %eax
	addl _a(%rip), %eax
	movl %eax, ___TEMPORARY8__(%rip)
## TAC_RETURN
	movl  ___TEMPORARY8__(%rip), %eax
	leave
	ret 
## TAC_SYMBOL
	.comm  _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm  _2,4,4
	movl $2, _2(%rip)
## TAC_ADD
	movl _1(%rip), %eax
	addl _2(%rip), %eax
	movl %eax, ___TEMPORARY9__(%rip)
##TAC_ARG
## TAC_SYMBOL
	.comm  _12312,4,4
	movl $12312, _12312(%rip)
## TAC_SYMBOL
	.comm  _123,4,4
	movl $123, _123(%rip)
TAC_DIV##TAC_ARG
##TAC_CALL
## TAC_MOV
	movl _a(%rip), %eax 
	movl %eax, ___TEMPORARY11__(%rip) 
	leave
	ret 
	.cfi_endproc
