.data
	zero: .asciiz "ZERO"
	um: .asciiz "UM"
	dois: .asciiz "DOIS"
	tres: .asciiz "TRES"
	quatro: .asciiz "QUATRO"
	cinco: .asciiz "CINCO"
	seis: .asciiz "SEIS"
	sete: .asciiz "SETE"
	oito: .asciiz "OITO"
	nove: .asciiz "NOVE"
	dez: .asciiz "DEZ"

.text
main:
	addi $v0, $0, 5
	syscall
	addi $s0, $v0, 0 #Salva numero do usuario em S0
	
	addi $v0, $0, 4 #Configura Syscall Print
	
	beq $t0, $s0 If0
	li $t0, 1
	beq $t0, $s0 If1
	li $t0, 2
	beq $t0, $s0 If2
	li $t0, 3
	beq $t0, $s0 If3
	li $t0, 4
	beq $t0, $s0 If4
	li $t0, 5
	beq $t0, $s0 If5
	li $t0, 6
	beq $t0, $s0 If6
	li $t0, 7
	beq $t0, $s0 If7
	li $t0, 8
	beq $t0, $s0 If8
	li $t0, 9
	beq $t0, $s0 If9
	li $t0, 10
	beq $t0, $s0 If10

	
	If0:
	la $a0, zero #Argumnto syscall
	j EndIf
	
	If1:
	la $a0, um #Argumnto syscall
	j EndIf
	
	If2:
	la $a0, dois #Argumnto syscall
	j EndIf
	
	If3:
	la $a0, tres #Argumnto syscall
	j EndIf
	
	If4:
	la $a0, quatro #Argumnto syscall
	j EndIf
	
	If5:
	la $a0, cinco #Argumnto syscall
	j EndIf
	
	If6:
	la $a0, seis #Argumnto syscall
	j EndIf
	
	If7:
	la $a0, sete #Argumnto syscall
	j EndIf
	
	If8:
	la $a0, oito #Argumnto syscall
	j EndIf
	
	If9:
	la $a0, nove #Argumnto syscall
	j EndIf

	If10:
	la $a0, dez #Argumnto syscall
	
	
EndIf:
	syscall
	addi $v0, $0, 10
	syscall
