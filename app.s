.globl main
minloc:
addi x2, x2, -4
sw x1, 0(x2)
addi x2, x2, -4
sw x8, 0(x2)
mv x8, x2
addi x2, x2, -24
sw x10, -4(x8)
sw x11, -8(x8)
sw x12, -12(x8)
li x28, 7
sw x28, -16(x8)
lw x28, -8(x8)
sw x28, -20(x8)
lw x28, -4(x8)
lw x27, -8(x8)
add x26, x28, x27
lw x25, -4(x26)
sw x25, -24(x8)
lw x26, -8(x8)
li x12, 1
add x25, x26, x12
sw x25, -16(x8)
.L22:
lw x25, -16(x8)
lw x24, -12(x8)
bge x25, x24, .L47
lw x22, -4(x8)
lw x13, -16(x8)
add x7, x22, x13
lw x6, -4(x7)
lw x7, -24(x8)
bge x6, x7, .L41
lw x5, -4(x8)
lw x4, -16(x8)
add x3, x5, x4
lw x2, -4(x3)
sw x2, -24(x8)
lw x3, -16(x8)
sw x3, -20(x8)
.L41:
lw x3, -16(x8)
li x12, 1
add x2, x3, x12
sw x2, -16(x8)
j .L22
.L47:
lw x2, -20(x8)
mv x2, x8
lw x8, 0(x2)
addi x2, x2, 4
lw x1, 0(x2)
addi x2, x2, 4
mv x10, x2
ret
sort:
addi x2, x2, -4
sw x1, 0(x2)
addi x2, x2, -4
sw x8, 0(x2)
mv x8, x2
addi x2, x2, -24
sw x10, -4(x8)
sw x11, -8(x8)
sw x12, -12(x8)
.L62:
lw x28, -16(x8)
lw x27, -12(x8)
li x12, 1
sub x26, x27, x12
bge x28, x26, .L101
lw x25, -4(x8)
mv x10, x25
lw x24, -16(x8)
mv x11, x24
lw x22, -12(x8)
mv x12, x22
jal minloc
mv x13, x10
sw x13, -20(x8)
lw x13, -4(x8)
lw x7, -20(x8)
add x6, x13, x7
lw x5, -4(x6)
sw x5, -24(x8)
lw x6, -4(x8)
lw x5, -20(x8)
add x4, x6, x5
lw x6, -4(x8)
lw x5, -16(x8)
add x3, x6, x5
lw x2, -4(x3)
sw x2, -4(x4)
lw x4, -4(x8)
lw x3, -16(x8)
add x2, x4, x3
lw x4, -24(x8)
sw x4, -4(x2)
lw x4, -16(x8)
li x12, 1
add x3, x4, x12
sw x3, -16(x8)
j .L62
.L101:
mv x2, x8
lw x8, 0(x2)
addi x2, x2, 4
lw x1, 0(x2)
addi x2, x2, 4
ret
main:
addi x2, x2, -4
sw x1, 0(x2)
addi x2, x2, -4
sw x8, 0(x2)
mv x8, x2
addi x2, x2, -48
addi x28, x8, -40
sw x28, -44(x8)
li x28, 4
sw x28, -48(x8)
.L115:
lw x28, -48(x8)
li x12, 10
bge x28, x12, .L131
lw x27, -44(x8)
lw x26, -48(x8)
add x25, x27, x26
jal input
mv x27, x10
sw x27, -4(x25)
lw x27, -48(x8)
li x12, 1
add x26, x27, x12
sw x26, -48(x8)
j .L115
.L131:
lw x26, -44(x8)
mv x10, x26
mv x11, x0
mv x12, x10
jal sort
mv x25, x10
li x24, 0
sw x24, -48(x8)
.L140:
lw x24, -48(x8)
li x12, 10
bge x24, x12, .L156
lw x22, -44(x8)
lw x13, -48(x8)
add x7, x22, x13
lw x6, -4(x7)
mv x10, x6
jal output
lw x7, -48(x8)
li x12, 1
add x5, x7, x12
sw x5, -48(x8)
j .L140
.L156:
mv x2, x8
lw x8, 0(x2)
addi x2, x2, 4
lw x1, 0(x2)
addi x2, x2, 4
ret
