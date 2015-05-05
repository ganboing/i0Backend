	.text
start of i0 asm
	.file	"complex-Os.ll"
	.globl	test
	.type	test,@function
fnuction entry :                        # @test
test:
# BB#0:                                 # %entry
	add 	spq, 0, spq
	mov spq, bpq
	mov 128, r0q
	loadr64 	r0q, ( r0q + 0)
	blt 	r0q, 1, LBB0_4
	jmp 	LBB0_1
LBB0_1:                                 # %for.body.lr.ph
	mov 0, r2q
	mov 64, r1q
	loadr64 	r3q, ( r1q + 0)
LBB0_2:                                 # %for.body
                                        # =>This Inner Loop Header: Depth=1
	mul 	r3q, r2q, r3q
	add 	r2q, 1, r2q
	bne 	r0q, r2q, LBB0_2
	jmp 	LBB0_3
LBB0_3:                                 # %for.cond.for.end_crit_edge
	storer64 	r3q, ( r1q + 0)
LBB0_4:                                 # %for.end
	mov bpq, spq
	ret
test
 end
Ltmp0:
	.size	test, Ltmp0-test


