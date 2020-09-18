.data
devided_by_zero_msg: 	 .asciiz 	 "Error division by zero
"
new_line: 	 .asciiz 	 "
"
prcond_false_msg: 	 .asciiz 	 "Precondition hasn't been satisfied for function "
Func_data: 	 .asciiz 	 "Func"
label_30_msg:    .asciiz    "Our greatest glory is not in never falling, but in rising every time we fall. — Confucius\n"
label_58_msg:    .asciiz    "All our dreams can come true, if we have the courage to pursue them. – Walt Disney"
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
Func:
addu $fp, $sp, 0
label_18:
label_19:
lw $8, 0($fp)
beq $8,0, label_47
j label_23
label_23:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
label_30:
la $8, label_30_msg
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
label_45:
addu $sp, $sp, 0
label_47:
lw $8, 4($fp)
beq $8,0, label_51
j label_75
label_51:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
label_58:
la $8, label_58_msg
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
label_73:
addu $sp, $sp, 0
label_75:
addu $sp, $fp, 0
li $v0, 0
jr $ra
main:
addu $fp, $sp, 0
label_81:
label_82:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
j label_93
label_90:
li $8, 0
j label_95
label_93:
li $8, 1
label_95:
j label_97
label_97:
li $9, 0
j label_102
label_100:
li $9, 1
label_102:
subu $sp, $sp, 4
sw $9, ($sp)
subu $sp, $sp, 4
sw $8, 0($sp)
addu $fp, $sp, 0
jal Func
addu $sp, $fp, 0
addu $sp, $sp, 8
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_118:
addu $sp, $fp, 0
li $v0, 0
jr $ra
