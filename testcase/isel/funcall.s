	.text
	.file	"funcall.ll"
	.globl	proc
	.align	16, 0x90
	.type	proc,@function
proc:                                   # @proc
	.cfi_startproc
# BB#0:
	testl	%edi, %edi
	js	.LBB0_1
# BB#2:
	jmp	external2               # TAILCALL
.LBB0_1:
	jmp	external1               # TAILCALL
.Ltmp0:
	.size	proc, .Ltmp0-proc
	.cfi_endproc


	.ident	"Ubuntu clang version 3.5-1ubuntu1 (trunk) (based on LLVM 3.5)"
	.section	".note.GNU-stack","",@progbits
