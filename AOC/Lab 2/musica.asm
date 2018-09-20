.data
	musica: .byte 51,50,48,53,51,50,51,53,55,56,55,53,51,50,48,-1

.text
main:
	la $t0,musica #t0 vetor, t1 indice, t2 pitch, t3 -1
	li $a1,250
	li $a2, 2
	li $a3, 127
	li $t3, -1
	j song
	
song:
	lb $a0,musica($t1)
	beq $a0, $t3, exit
	li $v0,31
	syscall
	li $a0,249
	li $v0,32
	syscall
	addi $t1,$t1,1
	j song
	
exit:
	li $v0,10
	syscall
	