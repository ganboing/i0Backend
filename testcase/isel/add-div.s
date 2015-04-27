	.text
	.file	"add-div.bc"
	.globl	foo
	.align	16, 0x90
	.type	foo,@function
foo:                                    # @foo
	.cfi_startproc
# BB#0:
	movl	%edx, %ecx
	addl	%esi, %edi
	movl	%edi, %eax
	cltd
	idivl	%ecx
	retq
.Ltmp0:
	.size	foo, .Ltmp0-foo
	.cfi_endproc


	.ident	"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"
	.section	".note.GNU-stack","",@progbits
