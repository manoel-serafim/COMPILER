.globl main
gcd:
addi x2, x2, -4
sw x1, 0(x2)
addi x2, x2, -4
sw x8, 0(x2)
mv x8, x2
addi x2, x2, -8
sw x10, -4(x8)
sw x11, -8(x8)
lw x28, -8(x8)
li x27, 0
bne x28, x27, .L19
lw x28, -4(x8)
mv x2, x8
lw x8, 0(x2)
addi x2, x2, 4
lw x1, 0(x2)
addi x2, x2, 4
mv x10, x28
ret
j .L37
.L19:
lw x27, -8(x8)
mv x10, x27
lw x26, -4(x8)
lw x25, -4(x8)
lw x24, -8(x8)
div x22, x25, x24
lw x25, -8(x8)
mul x24, x22, x25
sub x25, x26, x24
mv x11, x25
jal gcd
mv x26, x10
mv x2, x8
lw x8, 0(x2)
addi x2, x2, 4
lw x1, 0(x2)
addi x2, x2, 4
mv x10, x26
ret
.L37:
main:
addi x2, x2, -4
sw x1, 0(x2)
addi x2, x2, -4
sw x8, 0(x2)
mv x8, x2
addi x2, x2, -8
jal input
mv x28, x10
sw x28, -4(x8)
jal input
mv x28, x10
sw x28, -8(x8)
lw x28, -4(x8)
mv x10, x28
lw x27, -8(x8)
mv x11, x27
jal gcd
mv x26, x10
mv x10, x26
jal output
mv x2, x8
lw x8, 0(x2)
addi x2, x2, 4
lw x1, 0(x2)
addi x2, x2, 4
ret
