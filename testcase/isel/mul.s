	.text
	.file	"mul.ll"
	.globl	imul
	.align	16, 0x90
	.type	imul,@function
imul:                                   # @imul
	.cfi_startproc
# BB#0:
	imulq	%rsi, %rdi
	movq	%rdi, %rax
	retq
.Ltmp0:
	.size	imul, .Ltmp0-imul
	.cfi_endproc


	.ident	"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"
	.section	".note.GNU-stack","",@progbits
