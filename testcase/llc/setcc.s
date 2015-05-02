	.text
start of i0 asm
	.file	"setcc.bc"
	.globl	test
	.type	test,@function
fnuction entry :                        # @test
test:
# BB#0:
	add 	spq, 0, spq
	mov spq, bpq
	mov 256, r0q
	loadr64 	r0q, ( r0q + 0)
	mov 128, r1q
	loadr64 	r1q, ( r1q + 0)
	setlt 	r1q, r0q, r0q
	mov 64, r1q
	storer64 	r0q, ( r1q + 0)
	mov bpq, spq
	ret
test
 end
Ltmp0:
	.size	test, Ltmp0-test


