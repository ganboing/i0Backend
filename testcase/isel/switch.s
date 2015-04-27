	.text
	.file	"switch.ll"
	.globl	test
	.align	16, 0x90
	.type	test,@function
test:                                   # @test
	.cfi_startproc
# BB#0:
	movl	$4, %eax
	cmpl	$1, %edi
	je	.LBB0_6
# BB#1:
	cmpl	$10, %edi
	jne	.LBB0_2
# BB#4:
	movl	$2, %eax
	retq
.LBB0_2:
	cmpl	$3, %edi
	jne	.LBB0_5
# BB#3:
	movl	$9, %eax
	retq
.LBB0_5:
	movl	%edi, %eax
.LBB0_6:
	retq
.Ltmp0:
	.size	test, .Ltmp0-test
	.cfi_endproc


	.ident	"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"
	.section	".note.GNU-stack","",@progbits
