	.text
	.file	"branch.ll"
	.globl	test
	.align	16, 0x90
	.type	test,@function
test:                                   # @test
	.cfi_startproc
# BB#0:
                                        # kill: EDI<def> EDI<kill> RDI<def>
	testl	%edi, %edi
	js	.LBB0_1
# BB#2:
	leal	(%rdi,%rdi,2), %edi
	movl	%edi, %eax
	retq
.LBB0_1:
	addl	%edi, %edi
	movl	%edi, %eax
	retq
.Ltmp0:
	.size	test, .Ltmp0-test
	.cfi_endproc


	.ident	"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"
	.section	".note.GNU-stack","",@progbits
