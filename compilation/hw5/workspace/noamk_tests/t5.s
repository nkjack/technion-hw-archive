.data
devided_by_zero_msg: 	 .asciiz 	 "Error division by zero
"
new_line: 	 .asciiz 	 "
"
prcond_false_msg: 	 .asciiz 	 "Precondition hasn't been satisfied for function "
maxTestsBasicAssignmentTest_data: 	 .asciiz 	 "maxTestsBasicAssignmentTest"
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
maxTestsBasicAssignmentTest:
addu $fp, $sp, 0
label_18:
label_19:
sw $0, 0($sp)
subu $sp, $sp, 4
sw $0, 0($sp)
subu $sp, $sp, 4
addu $sp, $fp, 0
li $v0, 0
jr $ra
main:
addu $fp, $sp, 0
label_29:
label_30:
#Prologue: saving regs
#saving $fp and $ra
subu $sp, $sp, 4
sw $fp, 0($sp)
subu $sp, $sp, 4
sw $ra, 0($sp)
addu $fp, $sp, 0
jal maxTestsBasicAssignmentTest
addu $sp, $fp, 0
#restoring $ra and $fp
lw $ra, ($sp)
addu $sp, $sp, 4
lw $fp, ($sp)
addu $sp, $sp, 4
#Epilogue: saving regs
addu $8, $v0, 0
label_47:
addu $sp, $fp, 0
li $v0, 0
jr $ra
