	.text
start of i0 asm
	.file	"b.bc"
	.globl	test
	.type	test,@function
fnuction entry :                        # @test
test:
# BB#0:
	add 	spq, -16, spq
	mov spq, bpq
	mov 4, r0q
	storer32 	r0q, ( spq + 12)
	mov 5, r0q
	storer32 	r0q, ( spq + 8)
	loadra32 	r0q, ( spq + 12)
	mul 	r0q, 5, r0q
	storer32 	r0q, ( spq + 4)
	mov bpq, spq
	ret
test
 end
Ltmp0:
	.size	test, Ltmp0-test


