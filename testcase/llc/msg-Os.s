	.text
	.i0_asm
	.file	"msg-Os.bc"
	.globl	main
	.type	main,@function
.proc                                   # @main
main
# BB#0:                                 # %entry
	add 	spq, $0, spq
	mov 	spq, bpq
	mov 	$0, r0q
	mov 	$4294967816, r2q
LBB0_1:                                 # %for.body
                                        # =>This Inner Loop Header: Depth=1
	add 	@main.msg, r0q, r1q
	loadrs8 	r1q, (r1q)0
	storer64 	r1q, (r2q)0
	add 	r0q, $1, r0q
	bne 	r0q, $6, @LBB0_1
	jmp 	@LBB0_2
LBB0_2:                                 # %for.end
	mov 	bpq, spq
	ret
.endp 
Ltmp0:
	.size	main, Ltmp0-main

	.globl	test2
	.type	test2,@function
.proc                                   # @test2
test2
# BB#0:                                 # %entry
	add 	spq, $0, spq
	mov 	spq, bpq
	mov 	$0, r0q
	mov 	$4294967816, r2q
LBB1_1:                                 # %for.body
                                        # =>This Inner Loop Header: Depth=1
	add 	@test2.msg, r0q, r1q
	loadrs8 	r1q, (r1q)0
	storer64 	r1q, (r2q)0
	add 	r0q, $1, r0q
	bne 	r0q, $6, @LBB1_1
	jmp 	@LBB1_2
LBB1_2:                                 # %for.end
	mov 	bpq, spq
	ret
.endp 
Ltmp1:
	.size	test2, Ltmp1-test2

	.type	main.msg,@object        # @main.msg
	.section	.rodata.str1.1,"aMS",@progbits,1
main.msg:
	.asciz	"hello"
	.size	main.msg, 6

	.type	test2.msg,@object       # @test2.msg
test2.msg:
	.asciz	"world"
	.size	test2.msg, 6


