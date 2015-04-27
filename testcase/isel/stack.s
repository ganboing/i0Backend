	.text
	.file	"stack.bc"
	.globl	test
	.align	16, 0x90
	.type	test,@function
test:                                   # @test
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
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	addl	-4(%rbp), %esi
	movl	%esi, -12(%rbp)
	movl	%esi, %eax
	popq	%rbp
	retq
.Ltmp3:
	.size	test, .Ltmp3-test
	.cfi_endproc


	.ident	"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"
	.section	".note.GNU-stack","",@progbits
