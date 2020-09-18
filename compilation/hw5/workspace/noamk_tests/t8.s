.data
devided_by_zero_msg: 	 .asciiz 	 "Error division by zero
"
new_line: 	 .asciiz 	 "
"
prcond_false_msg: 	 .asciiz 	 "Precondition hasn't been satisfied for function "
foo_data: 	 .asciiz 	 "foo"
label_52_msg:    .asciiz    "OK\n"
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
foo:
addu $fp, $sp, 0
label_18:
lw $8, 0($fp)
li $9, 0
bgt $8, $9, label_23
j label_33
label_23:
lw $8, 4($fp)
li $9, 0
bgt $8, $9, label_28
j label_33
label_28:
lw $8, 0($fp)
li $9, 10
blt $8, $9, label_45
j label_33
label_33:
la $a0, prcond_false_msg
li $v0, 4
syscall
la $a0, foo_data
li $v0, 4
syscall
la $a0, new_line
li $v0, 4
syscall
li $v0, 10
syscall
label_45:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
label_52:
la $8, label_52_msg
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
label_67:
addu $sp, $fp, 0
li $v0, 0
jr $ra
main:
addu $fp, $sp, 0
label_73:
label_74:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
li $8, 11
li $9, 7
subu $sp, $sp, 4
sw $9, ($sp)
subu $sp, $sp, 4
sw $8, 0($sp)
addu $fp, $sp, 0
jal foo
addu $sp, $fp, 0
addu $sp, $sp, 8
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_98:
addu $sp, $fp, 0
li $v0, 0
jr $ra
