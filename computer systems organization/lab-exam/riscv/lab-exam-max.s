.text;  
.align 6;
.globl _start;                                                        
_start:

# x7 register has the base address of the array
la x7, tdat1

# Put your code here

addi x19, x0, 19
addi x5, x7, 0
lw x31, 0(x5)
loop:
	addi x19, x19, -1
	beq x19, x0, exit
	
	addi x5, x5, 4
	lw x6, 0(x5)
	bge x31, x6, loop
	
	add x31, x6, x0
	j loop

# end of your code
exit : 

.data


tdat1:  .word 0xdeadc0de
tdat2:  .word 0xdeaddead
tdat3:  .word 0xc0dedead
tdat4:  .word 0xabbaabba
tdat5:  .word 0xfeeddead
tdat6:  .word 0xdeadfeed
tdat7:  .word 0xc0defeed
tdat8:  .word 0xfeedc0de
tdat9:  .word 0xbeadbead
tdat10: .word 0xdeabdeab
tdat11: .word 0x78567856
tdat12: .word 0x00000000
tdat13: .word 0x56785678
tdat14: .word 0xffffffff
tdat15: .word 0x56781234
tdat16: .word 0xbeadbead
tdat17: .word 0x12341234
tdat18: .word 0xeabdeabd
tdat19: .word 0x12345678
tdat20: .word 0xdeabdeab


