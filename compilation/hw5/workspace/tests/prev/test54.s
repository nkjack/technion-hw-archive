.data
devided_by_zero_msg: 	 .asciiz 	 "Error division by zero
"
new_line: 	 .asciiz 	 "
"
prcond_false_msg: 	 .asciiz 	 "Precondition hasn't been satisfied for function "
Func_data: 	 .asciiz 	 "Func"
maxTestscheckReturnBoolFromFunc_data: 	 .asciiz 	 "maxTestscheckReturnBoolFromFunc"
label_79_msg:    .asciiz    "Hardships often prepare ordinary people for an extraordinary destiny. – C.S. Lewis\n"
label_126_msg:    .asciiz    "Believe in yourself. You are braver than you think, more talented than you know, and capable of more than you imagine. ― Roy T. Bennett"
main_data: 	 .asciiz 	 "main"
label_173_msg:    .asciiz    "\nI hate this course\n"
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
Func:
addu $fp, $sp, 0
label_18:
label_19:
lw $8, 0($fp)
li $9, 3
bgt $8, $9, label_24
j label_35
label_24:
j label_29
label_26:
li $8, 0
j label_31
label_29:
li $8, 1
label_31:
addu $sp, $fp, 0
move $v0, $8
jr $ra
label_35:
j label_37
label_37:
li $8, 0
j label_42
label_40:
li $8, 1
label_42:
addu $sp, $fp, 0
move $v0, $8
jr $ra
maxTestscheckReturnBoolFromFunc:
addu $fp, $sp, 0
label_48:
label_49:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
li $8, 5
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal Func
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
beq $8,0, label_96
j label_72
label_72:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
label_79:
la $8, label_79_msg
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal print
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_94:
addu $sp, $sp, 0
label_96:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
li $8, 1
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal Func
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
beq $8,0, label_119
j label_143
label_119:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
label_126:
la $8, label_126_msg
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal print
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_141:
addu $sp, $sp, 0
label_143:
main:
addu $fp, $sp, 0
label_146:
label_147:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
addu $fp, $sp, 0
jal maxTestscheckReturnBoolFromFunc
addu $sp, $fp, 0
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
beq $8,0, label_166
j label_166
label_166:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
label_173:
la $8, label_173_msg
subu $sp, $sp, 4
sw $8, ($sp)
addu $fp, $sp, 0
jal print
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_188:
addu $sp, $fp, 0
li $v0, 0
jr $ra
