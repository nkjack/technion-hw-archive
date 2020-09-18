no precondition 
no precondition 
.data
devided_by_zero_msg: 	 .asciiz 	 "Error division by zero
"
new_line: 	 .asciiz 	 "
"
prcond_false_msg: 	 .asciiz 	 "Precondition hasn't been satisfied for function "
printByValue_data: 	 .asciiz 	 "printByValue"
label_40_msg:    .asciiz    "val is true\n"
label_64_msg:    .asciiz    "val is false\n"
main_data: 	 .asciiz 	 "main"
label_162_msg:    .asciiz    "true\n"
label_192_msg:    .asciiz    "true\n"
.text
print:
lw $a0,0($sp)
li $v0,1
syscall
jr $ra
printi:
lw $a0,0($sp)
li $v0,4
syscall
jr $ra
devided_by_zero:
la $a0, devided_by_zero_msg
li, $v0, 4
syscall
li, $v0, 10
syscall
printByValue:
addu $fp, $sp, 0
label_18:
la $a0, prcond_false_msg
li, $v0, 4
syscall
la $a0, printByValue_data
li, $v0, 4
syscall
la $a0, new_line
li, $v0, 4
syscall
li, $v0, 10
syscall
label_30:
beq $0,0, label_57
j label_33
label_33:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
label_40:
la $8, label_40_msg
sw $8, 0($sp)
subu $sp, $sp, 4
addu $fp, $sp, 0
jal print
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, 4($sp)
addu $sp, $sp, 4
lw $fp, 4($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_55:
j label_81
label_57:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
label_64:
la $8, label_64_msg
sw $8, 0($sp)
subu $sp, $sp, 4
addu $fp, $sp, 0
jal print
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, 4($sp)
addu $sp, $sp, 4
lw $fp, 4($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_79:
addu $sp, $sp, 0
label_81:
addu $sp, $fp, 0
li $v0, 0
jr $ra
main:
addu $fp, $sp, 0
label_87:
la $a0, prcond_false_msg
li, $v0, 4
syscall
la $a0, main_data
li, $v0, 4
syscall
la $a0, new_line
li, $v0, 4
syscall
li, $v0, 10
syscall
label_99:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
j label_110
label_107:
li $8, 0
j label_112
label_110:
li $8, 1
label_112:
sw $8, 0($sp)
subu $sp, $sp, 4
addu $fp, $sp, 0
jal printByValue
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, 4($sp)
addu $sp, $sp, 4
lw $fp, 4($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_126:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
j label_134
label_134:
li $8, 0
j label_139
label_137:
li $8, 1
label_139:
sw $8, 0($sp)
subu $sp, $sp, 4
addu $fp, $sp, 0
jal printByValue
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, 4($sp)
addu $sp, $sp, 4
lw $fp, 4($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_153:
j label_155
label_155:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
label_162:
la $8, label_162_msg
sw $8, 0($sp)
subu $sp, $sp, 4
addu $fp, $sp, 0
jal print
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, 4($sp)
addu $sp, $sp, 4
lw $fp, 4($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_177:
addu $sp, $sp, 0
label_179:
j label_181
label_181:
j label_209
label_183:
j label_185
label_185:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
label_192:
la $8, label_192_msg
sw $8, 0($sp)
subu $sp, $sp, 4
addu $fp, $sp, 0
jal print
addu $sp, $fp, 0
addu $sp, $sp, 4
#restoring $ra and $fp
lw $ra, 4($sp)
addu $sp, $sp, 4
lw $fp, 4($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_207:
addu $sp, $sp, 0
label_209:
addu $sp, $fp, 0
li $v0, 0
jr $ra
