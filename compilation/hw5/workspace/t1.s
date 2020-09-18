.data
devided_by_zero_msg: 	 .asciiz 	 "Error division by zero
"
new_line: 	 .asciiz 	 "
"
prcond_false_msg: 	 .asciiz 	 "Precondition hasn't been satisfied for function "
printByValue_data: 	 .asciiz 	 "printByValue"
label_29_msg:    .asciiz    "val is true\n"
label_53_msg:    .asciiz    "val is false\n"
main_data: 	 .asciiz 	 "main"
label_140_msg:    .asciiz    "true\n"
label_170_msg:    .asciiz    "true\n"
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
label_19:
beq $0,0, label_46
j label_22
label_22:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
label_29:
la $8, label_29_msg
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
label_44:
j label_70
label_46:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
label_53:
la $8, label_53_msg
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
label_68:
addu $sp, $sp, 0
label_70:
addu $sp, $fp, 0
li $v0, 0
jr $ra
main:
addu $fp, $sp, 0
label_76:
label_77:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
j label_88
label_85:
li $8, 0
j label_90
label_88:
li $8, 1
label_90:
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
label_104:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
j label_112
label_112:
li $8, 0
j label_117
label_115:
li $8, 1
label_117:
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
label_131:
j label_133
label_133:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
label_140:
la $8, label_140_msg
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
label_155:
addu $sp, $sp, 0
label_157:
j label_159
label_159:
j label_187
label_161:
j label_163
label_163:
#Prologue: saving regs
#saving $fp and $ra
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
subu $sp, $sp, 4
label_170:
la $8, label_170_msg
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
label_185:
addu $sp, $sp, 0
label_187:
addu $sp, $fp, 0
li $v0, 0
jr $ra
