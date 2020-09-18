.data
devided_by_zero_msg: 	 .asciiz 	 "Error division by zero
"
new_line: 	 .asciiz 	 "
"
prcond_false_msg: 	 .asciiz 	 "Precondition hasn't been satisfied for function "
Func_data: 	 .asciiz 	 "Func"
label_30_msg:    .asciiz    "All our dreams can come true, if we have the courage to pursue them. – Walt Disney"
maxTestscallFunctionWithBoolean_data: 	 .asciiz 	 "maxTestscallFunctionWithBoolean"
main_data: 	 .asciiz 	 "main"
label_121_msg:    .asciiz    "\nI hate this course\n"
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
lw $8, 4($fp)
beq $8,0, label_23
j label_47
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
addu $sp, $fp, 0
li $v0, 0
jr $ra
maxTestscallFunctionWithBoolean:
addu $fp, $sp, 0
label_53:
label_54:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
j label_74
j label_63
label_63:
li $8, 0
j label_68
label_66:
li $8, 1
label_68:
subu $sp, $sp, 4
sw $8, ($sp)
label_71:
li $8, 0
j label_76
label_74:
li $8, 1
label_76:
subu $sp, $sp, 4
sw $8, ($sp)
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
label_90:
addu $sp, $fp, 0
li $v0, 0
jr $ra
main:
addu $fp, $sp, 0
label_96:
label_97:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
addu $fp, $sp, 0
jal maxTestscallFunctionWithBoolean
addu $sp, $fp, 0
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_114:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
label_121:
la $8, label_121_msg
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
label_136:
addu $sp, $fp, 0
li $v0, 0
jr $ra
