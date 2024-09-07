j .L35
.L1:
addi x2, x2, -4
sw x1, x2
addi x2, x2, -4
sw x8, x2
mv x8, x2
sw x10, 0(s0)
sw x11, 0(s0)
lw a28, 9(s0)
li x27, 0
bne x28, x27, .L17
lw a28, 9(s0)
mv x2, x8
lw x1, x2
addi x2, x2, 4
mv x10, x28
ret
j .L34
.L17:
lw a27, 9(s0)
mv x10, x27
lw a26, 9(s0)
lw a25, 9(s0)
lw a24, 9(s0)
mv a0, 25
mv a1, 24
jal __divsi3
mv x22, a0
lw a25, 9(s0)
mv a0, x22
mv a1, x25
jal __mulsi3
mv x24, a0
sub x25, x26, x24
mv x11, x25
jal .L1
mv x26, x10
mv x2, x8
lw x1, x2
addi x2, x2, 4
mv x10, x26
ret
.L34:
.L35:
addi x2, x2, -4
sw x1, x2
addi x2, x2, -4
sw x8, x2
mv x8, x2
li x28, 2
sw x28, 0(s0)
li x28, 3
sw x28, 0(s0)
lw a28, 9(s0)
mv x10, x28
lw a27, 9(s0)
mv x11, x27
jal .L1
mv x26, x10
