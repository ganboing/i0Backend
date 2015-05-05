	.text
	.section .mdebug.abi32
	.previous
	.file	"complex32.bc"
	.globl	test
	.align	2
	.type	test,@function
	.ent	test                    # @test
test:
	.frame	$sp,0,$lr
	.mask 	0x00000000,0
	.set	noreorder
	.set	nomacro
# BB#0:
	addiu	$2, $zero, 128
	ld	$2, 0($2)
	addiu	$3, $zero, 1
	slt	$3, $2, $3
	bne	$3, $zero, LBB0_4
	nop
# BB#1:                                 # %.lr.ph
	addiu	$3, $zero, 0
	addiu	$4, $zero, 64
	ld	$5, 0($4)
LBB0_2:                                 # =>This Inner Loop Header: Depth=1
	mul	$5, $5, $3
	addiu	$3, $3, 1
	bne	$2, $3, LBB0_2
	nop
# BB#3:                                 # %._crit_edge
	st	$5, 0($4)
LBB0_4:
	ret	$lr
	nop
	.set	macro
	.set	reorder
	.end	test
$tmp0:
	.size	test, ($tmp0)-test


