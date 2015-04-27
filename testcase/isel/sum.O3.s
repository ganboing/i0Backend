	.text
	.file	"sum.O3.ll"
	.globl	sum
	.align	16, 0x90
	.type	sum,@function
sum:                                    # @sum
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
.Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp2:
	.cfi_def_cfa_register %rbp
	addl	%esi, %edi
	movl	%edi, %eax
	popq	%rbp
	retq
.Ltmp3:
	.size	sum, .Ltmp3-sum
	.cfi_endproc


	.ident	"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"
	.section	".note.GNU-stack","",@progbits
