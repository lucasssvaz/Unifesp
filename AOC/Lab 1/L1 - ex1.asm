main:
	addi $v0, $0, 5
	syscall
	addi $s0, $v0, 0 #Salva numero do usuario em S0
	addi $t0, $0, 0 # i=0
	addi $t2, $s0, 1 # argumento do for, S0 + 1
	
	For:
	addi $t0, $t0, 1 # i++
	beq $t0, $t2, EndFor #Sai se i = S0 + 1
	div $s0, $t0 #Divide S0 por i
	mfhi $t1 # copia resto para T1
	bne $0, $t1, For #Se resto dif de zero
	addi $v0, $0, 1 #Configura Syscall
	add $a0, $0, $t0 #Argumnto syscall
	syscall #Print
	addi $v0, $0, 11 #Configura Syscall
	addi $a0, $0, 32 #Argumnto syscall
	syscall #Print
	j For
	
	
EndFor:
	addi $v0, $0, 10
	syscall