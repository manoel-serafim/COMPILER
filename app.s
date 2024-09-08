.globl main
minloc:
addi x2, x2, -4
sw x1, (x2)
addi x2, x2, -4
sw x8, (x2)
mv x8, x2
addi x2, x2, -28
sw x10, -4(x8)
sw x11, -8(x8)
sw x12, -12(x8)
li x28, 7
sw x28, -16(x8)
lw x28, -8(x8)
sw x28, -20(x8)
lw x28, -28(x8)
lw x27, -8(x8)
add x26, x28, x27
lw x25, 9(s0)
sw x25, -24(x8)
lw x26, -8(x8)
li x25, 1
add x24, x26, x25
sw x24, -16(x8)
.L22:
lw x26, -16(x8)
lw x25, -12(x8)
bge x26, x25, .L47
lw x26, -28(x8)
lw x25, -16(x8)
add x24, x26, x25
lw x22, 9(s0)
lw x24, -24(x8)
bge x22, x24, .L41
lw x24, -28(x8)
lw x22, -16(x8)
add x13, x24, x22
lw x12, 9(s0)
sw x12, -24(x8)
lw x13, -16(x8)
sw x13, -20(x8)
.L41:
lw x13, -16(x8)
li x12, 1
add x11, x13, x12
sw x11, -16(x8)
j .L22
.L47:
lw x13, -20(x8)
mv x2, x8
lw x8, (x2)
addi x2, x2, 4
lw x1, (x2)
addi x2, x2, 4
mv x10, x13
ret
sort:
addi x2, x2, -4
sw x1, (x2)
addi x2, x2, -4
sw x8, (x2)
mv x8, x2
addi x2, x2, -28
sw x10, -4(x8)
sw x11, -8(x8)
sw x12, -12(x8)
.L62:
lw x28, -16(x8)
lw x27, -12(x8)
li x26, 1
sub x25, x27, x26
bge x28, x25, .L95
lw x28, -24(x8)
mv x10, x28
lw x27, -16(x8)
mv x11, x27
lw x26, -12(x8)
mv x12, x26
jal minloc
mv x25, x10
sw x25, -20(x8)
lw x25, -24(x8)
lw x24, -20(x8)
add x22, x25, x24
lw x13, 9(s0)
sw x13, -28(x8)
lw x22, -24(x8)
lw x13, -16(x8)
add x12, x22, x13
lw x11, 9(s0)
sw x11, -24(x8)
lw x12, -28(x8)
sw x12, -24(x8)
lw x12, -16(x8)
li x11, 1
add x10, x12, x11
sw x10, -16(x8)
j .L62
.L95:
mv x2, x8
lw x8, (x2)
addi x2, x2, 4
lw x1, (x2)
addi x2, x2, 4
ret
main:
addi x2, x2, -4
sw x1, (x2)
addi x2, x2, -4
sw x8, (x2)
mv x8, x2
addi x2, x2, -8
li x28, 4
sw x28, -4(x8)
.L107:
lw x28, -4(x8)
li x27, 10
bge x28, x27, .L120
jal input
mv x28, x10
sw x28, -8(x8)
lw x28, -4(x8)
li x27, 1
add x26, x28, x27
sw x26, -4(x8)
j .L107
.L120:
lw x28, -8(x8)
mv x10, x28
mv x11, x0
mv x12, x10
jal sort
mv x27, x10
li x26, 0
sw x26, -4(x8)
.L129:
lw x26, -4(x8)
li x25, 10
bge x26, x25, .L145
lw x26, -8(x8)
lw x25, -4(x8)
add x24, x26, x25
lw x22, 9(s0)
mv x10, x22
jal output
lw x24, -4(x8)
li x13, 1
add x12, x24, x13
sw x12, -4(x8)
j .L129
.L145:
mv x2, x8
lw x8, (x2)
addi x2, x2, 4
lw x1, (x2)
addi x2, x2, 4
ret
