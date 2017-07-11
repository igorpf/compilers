##TAC_VAR_DEC
	.globl 	_a
	.data
_a:
	.long 	7
##TAC_VAR_DEC
	.globl 	_b
	.data
_b:
	.long 	0
##TAC_VEC_DEC
	.comm _v,8,4
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm _232,4,4
	movl $232, _232(%rip)
##TAC_VEC_DEC_INIT
	.globl 	_z
	.data
_z:
	.long 	1
	.long 	232
##TAC_PARAM
##TAC_PARAM
##TAC_BEGIN_FUN
	.globl main
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_SYMBOL
	.comm _4,4,4
	movl $4, _4(%rip)
## TAC_SYMBOL
## TAC_ADD
	.comm ___TEMPORARY0__,4,4
	movl _4(%rip), %eax
	addl _a(%rip), %eax
	movl %eax, ___TEMPORARY0__(%rip)
## TAC_MOV
	movl ___TEMPORARY0__(%rip), %eax 
	movl %eax, _a(%rip) 
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm _3,4,4
	movl $3, _3(%rip)
## TAC_SYMBOL
## TAC_SUB
	.comm ___TEMPORARY1__,4,4
	movl _3(%rip), %edx
	movl _b(%rip), %eax
	subl %eax, %edx
	movl %edx, %eax
	movl %eax, ___TEMPORARY1__(%rip)
##TAC_VEC_WRITE
	movl ___TEMPORARY1__(%rip), %eax 
	movl %eax, _v+4(%rip)
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
## TAC_VEC_READ
	.comm ___TEMPORARY2__,4,4
	movl _1(%rip), %eax 
	movl _v(,%eax,4), %eax 
	movl %eax, ___TEMPORARY2__(%rip) 
## TAC_SYMBOL
	.comm _4,4,4
	movl $4, _4(%rip)
## TAC_MUL
	.comm ___TEMPORARY3__,4,4
	movl ___TEMPORARY2__(%rip), %eax
	imull _4(%rip), %eax
	movl %eax, ___TEMPORARY3__(%rip)
## TAC_MOV
	movl ___TEMPORARY3__(%rip), %eax 
	movl %eax, _a(%rip) 
## TAC_SYMBOL
## TAC_SYMBOL
	.comm _3,4,4
	movl $3, _3(%rip)
## TAC_DIV
	.comm ___TEMPORARY4__,4,4
	movl _a(%rip), %eax
	cltd
	idivl _3(%rip)
	movl %eax, ___TEMPORARY4__(%rip)
## TAC_MOV
	movl ___TEMPORARY4__(%rip), %eax 
	movl %eax, _a(%rip) 
## TAC_SYMBOL
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
## TAC_SYMBOL
	.comm _3,4,4
	movl $3, _3(%rip)
## TAC_DIV
	.comm ___TEMPORARY5__,4,4
	movl _a(%rip), %eax
	cltd
	idivl _3(%rip)
	movl %eax, ___TEMPORARY5__(%rip)
##TAC_PRINT
	.comm ___TEMPORARY5__,4,4
	movl	___TEMPORARY5__(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
## TAC_VEC_READ
	.comm ___TEMPORARY6__,4,4
	movl _1(%rip), %eax 
	movl _z(,%eax,4), %eax 
	movl %eax, ___TEMPORARY6__(%rip) 
##TAC_PRINT
	.comm ___TEMPORARY6__,4,4
	movl	___TEMPORARY6__(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
## TAC_SYMBOL
	.comm _0,4,4
	movl $0, _0(%rip)
## TAC_VEC_READ
	.comm ___TEMPORARY7__,4,4
	movl _0(%rip), %eax 
	movl _z(,%eax,4), %eax 
	movl %eax, ___TEMPORARY7__(%rip) 
## TAC_ADD
	.comm ___TEMPORARY8__,4,4
	movl _b(%rip), %eax
	addl ___TEMPORARY7__(%rip), %eax
	movl %eax, ___TEMPORARY8__(%rip)
## TAC_SYMBOL
## TAC_SYMBOL
	.comm _3,4,4
	movl $3, _3(%rip)
## TAC_DIV
	.comm ___TEMPORARY9__,4,4
	movl _a(%rip), %eax
	cltd
	idivl _3(%rip)
	movl %eax, ___TEMPORARY9__(%rip)
## TAC_ADD
	.comm ___TEMPORARY10__,4,4
	movl ___TEMPORARY8__(%rip), %eax
	addl ___TEMPORARY9__(%rip), %eax
	movl %eax, ___TEMPORARY10__(%rip)
##TAC_PRINT
	.comm ___TEMPORARY10__,4,4
	movl	___TEMPORARY10__(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
## TAC_SYMBOL
## TAC_ADD
	.comm ___TEMPORARY11__,4,4
	movl _a(%rip), %eax
	addl _a(%rip), %eax
	movl %eax, ___TEMPORARY11__(%rip)
## TAC_RETURN
	movl ___TEMPORARY11__(%rip), %eax
	leave
	ret 
##TAC_END_FUN
	leave
	ret 
	.cfi_endproc
##TAC_PARAM
##TAC_PARAM
##TAC_BEGIN_FUN
	.globl f
f:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_SYMBOL
	.comm _0,4,4
	movl $0, _0(%rip)
## TAC_RETURN
	movl _0(%rip), %eax
	popq	 %rbp
	leave
	ret 
##TAC_END_FUN
	popq	 %rbp
	leave
	ret 
	.cfi_endproc
.LC0:
	.string "%d\n"
.LC1:
	.string "v[1]\n"
.LC2:
	.string "ola\n"
