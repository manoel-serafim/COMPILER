	.file	"gcd.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	__mulsi3
	.type	__mulsi3, @function
__mulsi3:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	sw	zero,-20(s0)
	lw	a5,-36(s0)
	srai	a4,a5,31
	lw	a5,-36(s0)
	xor	a5,a4,a5
	sub	a5,a5,a4
	sw	a5,-24(s0)
	lw	a5,-40(s0)
	srai	a4,a5,31
	lw	a5,-40(s0)
	xor	a5,a4,a5
	sub	a5,a5,a4
	sw	a5,-28(s0)
	j	.L2
.L4:
	lw	a5,-28(s0)
	andi	a5,a5,1
	beq	a5,zero,.L3
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	add	a5,a4,a5
	sw	a5,-20(s0)
.L3:
	lw	a5,-24(s0)
	slli	a5,a5,1
	sw	a5,-24(s0)
	lw	a5,-28(s0)
	srli	a5,a5,1
	sw	a5,-28(s0)
.L2:
	lw	a5,-28(s0)
	bne	a5,zero,.L4
	lw	a4,-36(s0)
	lw	a5,-40(s0)
	xor	a5,a4,a5
	srli	a5,a5,31
	andi	a5,a5,1
	andi	a5,a5,0xff
	beq	a5,zero,.L5
	lw	a5,-20(s0)
	neg	a5,a5
	sw	a5,-20(s0)
.L5:
	lw	a5,-20(s0)
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	__mulsi3, .-__mulsi3
	.align	2
	.globl	__divsi3
	.type	__divsi3, @function
__divsi3:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	lw	a5,-40(s0)
	bne	a5,zero,.L8
	lw	a5,-36(s0)
	bge	a5,zero,.L9
	li	a5,-2147483648
	j	.L11
.L9:
	li	a5,-2147483648
	xori	a5,a5,-1
	j	.L11
.L8:
	lw	a5,-36(s0)
	srai	a5,a5,31
	lw	a4,-36(s0)
	xor	a4,a5,a4
	sub	a5,a4,a5
	sw	a5,-20(s0)
	lw	a5,-40(s0)
	srai	a5,a5,31
	lw	a4,-40(s0)
	xor	a4,a5,a4
	sub	a5,a4,a5
	sw	a5,-28(s0)
	sw	zero,-24(s0)
	j	.L12
.L13:
	lw	a4,-20(s0)
	lw	a5,-28(s0)
	sub	a5,a4,a5
	sw	a5,-20(s0)
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
.L12:
	lw	a4,-20(s0)
	lw	a5,-28(s0)
	bge	a4,a5,.L13
	lw	a4,-36(s0)
	lw	a5,-40(s0)
	xor	a5,a4,a5
	srli	a5,a5,31
	andi	a5,a5,1
	andi	a5,a5,0xff
	beq	a5,zero,.L14
	lw	a5,-24(s0)
	neg	a5,a5
	sw	a5,-24(s0)
.L14:
	lw	a5,-24(s0)
.L11:
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	__divsi3, .-__divsi3
	.align	2
	.globl	__modsi3
	.type	__modsi3, @function
__modsi3:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	lw	a5,-40(s0)
	bne	a5,zero,.L16
	li	a5,0
	j	.L17
.L16:
	lw	a5,-36(s0)
	srai	a5,a5,31
	lw	a4,-36(s0)
	xor	a4,a5,a4
	sub	a5,a4,a5
	sw	a5,-24(s0)
	lw	a5,-40(s0)
	srai	a5,a5,31
	lw	a4,-40(s0)
	xor	a4,a5,a4
	sub	a5,a4,a5
	sw	a5,-28(s0)
	lw	a5,-24(s0)
	sw	a5,-20(s0)
	j	.L18
.L19:
	lw	a4,-20(s0)
	lw	a5,-28(s0)
	sub	a5,a4,a5
	sw	a5,-20(s0)
.L18:
	lw	a4,-20(s0)
	lw	a5,-28(s0)
	bge	a4,a5,.L19
	lw	a5,-36(s0)
	bge	a5,zero,.L20
	lw	a5,-20(s0)
	neg	a5,a5
	j	.L17
.L20:
	lw	a5,-20(s0)
.L17:
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	__modsi3, .-__modsi3
	.align	2
	.globl	__udivsi3
	.type	__udivsi3, @function
__udivsi3:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	lw	a5,-40(s0)
	bne	a5,zero,.L23
	li	a5,-1
	j	.L24
.L23:
	sw	zero,-20(s0)
	j	.L25
.L26:
	lw	a4,-36(s0)
	lw	a5,-40(s0)
	sub	a5,a4,a5
	sw	a5,-36(s0)
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L25:
	lw	a4,-36(s0)
	lw	a5,-40(s0)
	bgeu	a4,a5,.L26
	lw	a5,-20(s0)
.L24:
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	__udivsi3, .-__udivsi3
	.align	2
	.globl	__umodsi3
	.type	__umodsi3, @function
__umodsi3:
	addi	sp,sp,-48
	sw	s0,44(sp)
	addi	s0,sp,48
	sw	a0,-36(s0)
	sw	a1,-40(s0)
	lw	a5,-40(s0)
	bne	a5,zero,.L28
	li	a5,0
	j	.L29
.L28:
	lw	a5,-36(s0)
	sw	a5,-20(s0)
	j	.L30
.L31:
	lw	a4,-20(s0)
	lw	a5,-40(s0)
	sub	a5,a4,a5
	sw	a5,-20(s0)
.L30:
	lw	a4,-20(s0)
	lw	a5,-40(s0)
	bgeu	a4,a5,.L31
	lw	a5,-20(s0)
.L29:
	mv	a0,a5
	lw	s0,44(sp)
	addi	sp,sp,48
	jr	ra
	.size	__umodsi3, .-__umodsi3
	.globl	__modsi3
	.align	2
	.globl	gcd
	.type	gcd, @function
gcd:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	sw	a1,-24(s0)
	lw	a5,-24(s0)
	bne	a5,zero,.L33
	lw	a5,-20(s0)
	j	.L34
.L33:
	lw	a5,-20(s0)
	lw	a1,-24(s0)
	mv	a0,a5
	call	__modsi3
	mv	a5,a0
	mv	a1,a5
	lw	a0,-24(s0)
	call	gcd
	mv	a5,a0
.L34:
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	gcd, .-gcd
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	li	a5,2
	sw	a5,-20(s0)
	li	a5,3
	sw	a5,-24(s0)
	lw	a1,-24(s0)
	lw	a0,-20(s0)
	call	gcd
	nop
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (12.2.0-14+11+b1) 12.2.0"
