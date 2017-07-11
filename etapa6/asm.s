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
	.comm _c,4,4
##TAC_PARAM
	.comm _d,4,4
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
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC1, %edi
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
## TAC_SYMBOL
##TAC_PRINT
	movl	_a(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
	.comm _0,4,4
	movl $0, _0(%rip)
## TAC_VEC_READ
	.comm ___TEMPORARY1__,4,4
	movl _0(%rip), %eax 
	movl _v(,%eax,4), %eax 
	movl %eax, ___TEMPORARY1__(%rip) 
##TAC_PRINT
	.comm ___TEMPORARY1__,4,4 ##8
	movl	___TEMPORARY1__(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm _10,4,4
	movl $10, _10(%rip)
## TAC_MOV
	movl _1(%rip), %eax 
	movl %eax, _a(%rip) 
## TAC_LABEL
__LABEL1__:
##TAC_LE
	.comm ___TEMPORARY3__,4,4
	movl _a(%rip), %eax
	cmp %eax, _10(%rip)
	jle HUE0
	movl $0, ___TEMPORARY3__(%rip)
	jmp FIMHUE0
HUE0:
	movl $1, ___TEMPORARY3__(%rip)
FIMHUE0:
 ##TAC_IFZ
	movl ___TEMPORARY3__(%rip), %eax
	jz __LABEL0__
## TAC_SYMBOL
##TAC_PRINT
	movl	_a(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
## TAC_SYMBOL
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
## TAC_ADD
	.comm ___TEMPORARY2__,4,4
	movl _a(%rip), %eax
	addl _1(%rip), %eax
	movl %eax, ___TEMPORARY2__(%rip)
## TAC_MOV
	movl ___TEMPORARY2__(%rip), %eax 
	movl %eax, _a(%rip) 
##TAC_JUMP
	jmp __LABEL1__## TAC_LABEL
__LABEL0__:
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
## TAC_SYMBOL
	.comm _2,4,4
	movl $2, _2(%rip)
##TAC_NE
	.comm ___TEMPORARY4__,4,4
	movl _1(%rip), %eax
	cmp %eax, _2(%rip)
	jne HUE1
	movl $1, ___TEMPORARY4__(%rip)
	jmp FIMHUE1
HUE1:
	movl $0, ___TEMPORARY4__(%rip)
FIMHUE1:
 ##TAC_IF
	movl ___TEMPORARY4__(%rip), %eax
	andl %eax,%eax
	jnz __LABEL2__
## TAC_SYMBOL
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
##TAC_JUMP
	jmp __LABEL3__## TAC_LABEL
__LABEL2__:
## TAC_SYMBOL
##TAC_PRINT
	movl	%eax, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
## TAC_LABEL
__LABEL3__:
## TAC_LABEL
__LABEL5__:
## TAC_SYMBOL
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
##TAC_GT
	.comm ___TEMPORARY5__,4,4
	movl _a(%rip), %eax
	cmp %eax, _1(%rip)
	jg HUE2
	movl $0, ___TEMPORARY5__(%rip)
	jmp FIMHUE2
HUE2:
	movl $1, ___TEMPORARY5__(%rip)
FIMHUE2:
 ##TAC_IF
	movl ___TEMPORARY5__(%rip), %eax
	andl %eax,%eax
	jnz __LABEL4__
## TAC_SYMBOL
## TAC_SYMBOL
	.comm _1,4,4
	movl $1, _1(%rip)
## TAC_SUB
	.comm ___TEMPORARY6__,4,4
	movl _a(%rip), %edx
	movl _1(%rip), %eax
	subl %eax, %edx
	movl %edx, %eax
	movl %eax, ___TEMPORARY6__(%rip)
## TAC_MOV
	movl ___TEMPORARY6__(%rip), %eax 
	movl %eax, _a(%rip) 
## TAC_SYMBOL
##TAC_PRINT
	movl	_a(%rip), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
##TAC_JUMP
	jmp __LABEL5__## TAC_LABEL
__LABEL4__:
## TAC_SYMBOL
## TAC_SYMBOL
## TAC_ADD
	.comm ___TEMPORARY7__,4,4
	movl _a(%rip), %eax
	addl _a(%rip), %eax
	movl %eax, ___TEMPORARY7__(%rip)
## TAC_RETURN
	movl ___TEMPORARY7__(%rip), %eax
	leave
	ret 
##TAC_END_FUN
	leave
	ret 
	.cfi_endproc
.LC0:
	.string "%d"
.LC1:
	.string "\n"
.LC2:
	.string "\n"
.LC3:
	.string "\n"
.LC4:
	.string "!"
.LC5:
	.string "\naaa"
.LC6:
	.string "\nBBB"
