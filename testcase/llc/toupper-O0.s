	.text
	.i0_asm
	.file	"toupper-O0.bc"
	.globl	main
	.type	main,@function
.proc                                   # @main
main
# BB#0:                                 # %entry
	add 	spq, $-8, spq
	mov 	spq, bpq
LBB0_1:                                 # %while.cond
                                        # =>This Inner Loop Header: Depth=1
	loadr64 	r0q, [4294967808]
	storer64 	r0q, (spq)0
	beq 	r0q, $-1, @LBB0_6
	jmp 	@LBB0_2
LBB0_2:                                 # %while.body
                                        #   in Loop: Header=BB0_1 Depth=1
	loadr64 	r0q, (spq)0
	blt 	r0q, $97, @LBB0_5
	jmp 	@LBB0_3
LBB0_3:                                 # %land.lhs.true
                                        #   in Loop: Header=BB0_1 Depth=1
	loadr64 	r0q, (spq)0
	bgt 	r0q, $122, @LBB0_5
	jmp 	@LBB0_4
LBB0_4:                                 # %if.then
                                        #   in Loop: Header=BB0_1 Depth=1
	loadr64 	r0q, (spq)0
	add 	r0q, $-32, r0q
	storer64 	r0q, (spq)0
LBB0_5:                                 # %if.end
                                        #   in Loop: Header=BB0_1 Depth=1
	loadr64 	r0q, (spq)0
	storer64 	r0q, [4294967816]
	jmp 	@LBB0_1
LBB0_6:                                 # %while.end
	mov 	bpq, spq
	ret
.endp 
Ltmp0:
	.size	main, Ltmp0-main


