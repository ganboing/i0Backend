	.text
start of i0 asm
	.file	"complex.bc"
	.globl	test
	.type	test,@function
fnuction entry :                        # @test
test:
# BB#0:
	add 	spq, -24, spq
	mov spq, bpq
	storer64 	r4q, ( spq + 16) # 8-byte Folded Spill
	storer64 	bpq, ( spq + 8) # 8-byte Folded Spill
	mov 128, r0q
	loadrs32 	r0q, ( r0q + 0)
	blt 	r0q, 1, <expr to print>

	jmp 	<expr to print>

LBB0_1:                                 # %.lr.ph
	mov 1, r3q
	mov 64, r1q
	storer64 	r1q, ( spq + 0) # 8-byte Folded Spill
	loadr64 	r2q, ( r1q + 0)
LBB0_2:                                 # =>This Inner Loop Header: Depth=1
	add 	r3q, -1, r4q
	mul 	r2q, r4q, r2q
	add 	r3q, 1, r4q
	and 	r3q, 4294967295, bpq
	and 	r0q, 4294967295, r1q
	mov r4q, r3q
	bne 	bpq, r1q, <expr to print>

	jmp 	<expr to print>

LBB0_3:                                 # %._crit_edge
	loadr64 	r0q, ( spq + 0) # 8-byte Folded Reload
	storer64 	r2q, ( r0q + 0)
LBB0_4:
	loadr64 	bpq, ( spq + 8) # 8-byte Folded Reload
	loadr64 	r4q, ( spq + 16) # 8-byte Folded Reload
	mov bpq, spq
	ret
test
 end
Ltmp0:
	.size	test, Ltmp0-test


