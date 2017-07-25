##TAC_VAR_DEC
	.globl 	_x
	.data
_x:
	.long 	6
##TAC_VAR_DEC
	.globl 	_a
	.data
_a:
	.long 	3
##TAC_VAR_DEC
	.globl 	_b
	.data
_b:
	.long 	10
##TAC_BEGIN_FUN
	.globl main
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_SYMBOL
## TAC_SYMBOL
## TAC_SYMBOL
	.comm ___TEMPORARY4__,4,4
## TAC_SUB
	.comm ___TEMPORARY4__,4,4
	movl _a(%rip), %edx
	movl _b(%rip), %eax
	subl %eax, %edx
	movl %edx, %eax
	movl %eax, ___TEMPORARY4__(%rip)
## TAC_SYMBOL
	.comm ___TEMPORARY7__,4,4
## TAC_MOV
	movl ___TEMPORARY4__(%rip), %eax 
	movl %eax, ___TEMPORARY7__(%rip) 
## TAC_SYMBOL
	.comm ___TEMPORARY10__,4,4
## TAC_MOV
	movl ___TEMPORARY4__(%rip), %eax 
	movl %eax, ___TEMPORARY10__(%rip) 
## TAC_SYMBOL
	.comm ___TEMPORARY1__,4,4
## TAC_MUL
	.comm ___TEMPORARY1__,4,4
	movl _a(%rip), %eax
	imull _b(%rip), %eax
	movl %eax, ___TEMPORARY1__(%rip)
## TAC_SYMBOL
## TAC_SYMBOL
	.comm ___TEMPORARY0__,4,4
## TAC_ADD
	.comm ___TEMPORARY0__,4,4
	movl _a(%rip), %eax
	addl _b(%rip), %eax
	movl %eax, ___TEMPORARY0__(%rip)
## TAC_SYMBOL
	.comm ___TEMPORARY3__,4,4
## TAC_MOV
	movl ___TEMPORARY0__(%rip), %eax 
	movl %eax, ___TEMPORARY3__(%rip) 
## TAC_SYMBOL
	.comm ___TEMPORARY6__,4,4
## TAC_MOV
	movl ___TEMPORARY0__(%rip), %eax 
	movl %eax, ___TEMPORARY6__(%rip) 
## TAC_SYMBOL
	.comm ___TEMPORARY9__,4,4
## TAC_MOV
	movl ___TEMPORARY0__(%rip), %eax 
	movl %eax, ___TEMPORARY9__(%rip) 
## TAC_SYMBOL
	.comm ___TEMPORARY5__,4,4
## TAC_ADD
	.comm ___TEMPORARY5__,4,4
	movl ___TEMPORARY3__(%rip), %eax
	addl ___TEMPORARY4__(%rip), %eax
	movl %eax, ___TEMPORARY5__(%rip)
## TAC_SYMBOL
## TAC_MOV
	movl ___TEMPORARY5__(%rip), %eax 
	movl %eax, _b(%rip) 
## TAC_SYMBOL
	.comm ___TEMPORARY8__,4,4
## TAC_MOV
	movl ___TEMPORARY5__(%rip), %eax 
	movl %eax, ___TEMPORARY8__(%rip) 
## TAC_SYMBOL
## TAC_MOV
	movl ___TEMPORARY5__(%rip), %eax 
	movl %eax, _x(%rip) 
## TAC_SYMBOL
	.comm ___TEMPORARY11__,4,4
## TAC_MOV
	movl ___TEMPORARY5__(%rip), %eax 
	movl %eax, ___TEMPORARY11__(%rip) 
## TAC_SYMBOL
## TAC_MOV
	movl ___TEMPORARY5__(%rip), %eax 
	movl %eax, _b(%rip) 
## TAC_SYMBOL
	.comm ___TEMPORARY2__,4,4
## TAC_ADD
	.comm ___TEMPORARY2__,4,4
	movl ___TEMPORARY0__(%rip), %eax
	addl ___TEMPORARY1__(%rip), %eax
	movl %eax, ___TEMPORARY2__(%rip)
## TAC_SYMBOL
## TAC_MOV
	movl ___TEMPORARY2__(%rip), %eax 
	movl %eax, _x(%rip) 
##TAC_PRINT
	movl	_b(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
##TAC_END_FUN
	leave
	ret 
	.cfi_endproc
##TAC_BEGIN_FUN
	.globl foo
foo:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
##TAC_END_FUN
	popq	 %rbp
	leave
	ret 
	.cfi_endproc
.LC0:
	.string "%d"
.LC1:
	.string "\n"
