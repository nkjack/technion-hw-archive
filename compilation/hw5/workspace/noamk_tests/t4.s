.data
devided_by_zero_msg: 	 .asciiz 	 "Error division by zero
"
new_line: 	 .asciiz 	 "
"
prcond_false_msg: 	 .asciiz 	 "Precondition hasn't been satisfied for function "
fib_data: 	 .asciiz 	 "fib"
main_data: 	 .asciiz 	 "main"
.text
print:
lw $a0, 0($sp)
li $v0,4
syscall
jr $ra
printi:
lw $a0, 0($sp)
li $v0, 1
syscall
jr $ra
devided_by_zero:
la $a0, devided_by_zero_msg
li $v0, 4
syscall
li $v0, 10
syscall
fib:
addu $fp, $sp, 0
label_18:
label_19:
lw $8, 0($fp)
li $9, 0
beq $8, $9, label_29
j label_24
label_24:
lw $8, 0($fp)
li $9, 1
beq $8, $9, label_29
j label_34
label_29:
li $8, 1
addu $sp, $fp, 0
move $v0, $8
jr $ra
label_34:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
lw $8, 0($fp)
li $9, 1
subu $8, $8, $9
and $8, $8, 255
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal fib
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
#Prologue: saving regs
subu $sp, $sp, 4
sw $8, 0($sp)
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
lw $8, 0($fp)
li $9, 2
subu $8, $8, $9
and $8, $8, 255
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal fib
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
lw $8, 0($sp)
addu $sp, $sp, 4
addu $9, $v0, 0
addu $8, $8, $9
addu $sp, $fp, 0
move $v0, $8
jr $ra
main:
addu $fp, $sp, 0
label_91:
label_92:
li $8, 5
subu $sp, $sp, 4
sw $8, 0($sp)
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
lw $8, -4($fp)
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal fib
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal printi
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_135:
addu $sp, $fp, 0
li $v0, 0
jr $ra
