main:
	li $v0,5
	syscall
	la $s0,($v0)
	la $s1,($v0)
	j fact
	
fact:
	addi $s0,$s0,-1
	beqz $s0, exit
	mult $s0,$s1
	mflo $s1
	j fact
	
exit:
	la $a0,($s1)
	li $v0,1
	syscall
	li $v0,10
	syscall