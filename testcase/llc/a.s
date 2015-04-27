	.text
start of i0 asm
	.file	"a.bc"
	.globl	add
	.type	add,@function
fnuction entry :                        # @add
add:
# BB#0:
	add 	spq, 0, spq
	mov spq, bpq
	mov 1280, r0q
	loadr64 	r0q, ( r0q + 0)
	mov 1024, r1q
	loadr64 	r1q, ( r1q + 0)
	add 	r1q, r0q, r0q
	mov 2048, r1q
	storer64 	r0q, ( r1q + 0)
	mov bpq, spq
	ret
add
 end
Ltmp0:
	.size	add, Ltmp0-add


