	.text
	.file	"mem.bc"
	.globl	set
	.align	16, 0x90
	.type	set,@function
set:                                    # @set
	.cfi_startproc
# BB#0:
	movl	%esi, (%rdi)
	movl	%esi, %eax
	retq
.Ltmp0:
	.size	set, .Ltmp0-set
	.cfi_endproc


	.ident	"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"
	.section	".note.GNU-stack","",@progbits
