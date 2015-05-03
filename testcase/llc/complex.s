	.text
start of i0 asm
	.file	"complex.bc"
	.globl	test
	.type	test,@function
fnuction entry :                        # @test
test:
# BB#0:
	add 	spq, 0, spq
	mov spq, bpq
	mov 128, r0q
	loadr64 	r0q, ( r0q + 0)
	blt 	r0q, 1, LBB0_4
	jmp 	LBB0_1
LBB0_1:                                 # %.lr.ph
	mov 0, r2q
	mov 64, r1q
	loadr64 	r3q, ( r1q + 0)
LBB0_2:                                 # =>This Inner Loop Header: Depth=1
	mul 	r3q, r2q, r3q
	add 	r2q, 1, r2q
	bne 	r0q, r2q, LBB0_2
	jmp 	LBB0_3
LBB0_3:                                 # %._crit_edge
	storer64 	r3q, ( r1q + 0)
LBB0_4:
	mov bpq, spq
	ret
test
 end
Ltmp0:
	.size	test, Ltmp0-test


