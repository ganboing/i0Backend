	.text
start of i0 asm
	.file	"mul.bc"
	.globl	test
	.type	test,@function
fnuction entry :                        # @test
test:
# BB#0:
	add 	spq, -16, spq
	mov spq, bpq
	mov 128, r0q
	loadr64 	r0q, ( r0q + 0)
	storer64 	r0q, ( spq + 8)
	mov 96, r0q
	loadr64 	r0q, ( r0q + 0)
	storer64 	r0q, ( spq + 0)
	loadr64 	r1q, ( spq + 8)
	mul 	r1q, r0q, r0q
	mov 256, r1q
	storer64 	r0q, ( r1q + 0)
	mov bpq, spq
	ret
test
 end
Ltmp0:
	.size	test, Ltmp0-test


