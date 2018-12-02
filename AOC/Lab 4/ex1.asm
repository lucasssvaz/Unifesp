# s0 - endereço do arquivo
# s1 - byte do buffer sendo comparado
# s2 - byte da palavra sendo comparada
# t0 - contador do buffer
# t1 - endereço da posicao atual do buffer
# t2 - byte atual
# t3 - palavra sendo analisada
# t4 - tamanho da palavra sendo analisada
# t5 - contador temporario do buffer
# t6 - contador posicao palavra


.data
	file: .asciiz "file.c"
	buffer: .space 2048
	while: .ascii "while"
	if: .ascii "if"
	else: .ascii "else"
	for: .ascii "for"
	return: .ascii "return"
	int: .ascii "int"
	float: .ascii "float"
	char: .ascii "char"
	void: .ascii "void"
.text
j main
	strcmp:
		move $t5, $t1
		addi $t6, $0, 0
		cmp_loop:
			lb $s1, 0($t5)
			lb $s2, 0($t3)
			beq $t6, $t4, success
			bne $s1, $s2, done
			add $t6, $t6, 1
			add $t5, $t5, 1
			j cmp_loop
		
		success:
			move $t5, $t1
			addi $t6, $0, 0
			success_loop:
				beq $t6, $t4, done
				lb $s1, 0($t5)
				add $s1, $s1, -32
				sb $s1, 0($t5)
				add $t6, $t6, 1
				add $t5, $t5, 1
				j success_loop
			
			
		done:
			jr $ra

	cmp:	
		lw $t4 2
		la $t3 if
		jal strcmp
		
		lw $t4 3
		la $t3 int
		jal strcmp
		la $t3 for
		jal strcmp
		
		lw $t4 4
		la $t3 char
		jal strcmp
		la $t3 void
		jal strcmp
		la $t3 else
		jal strcmp
		
		lw $t4 5
		la $t3 float
		jal strcmp
		la $t3 while
		jal strcmp
		
		lw $t4 6
		la $t3 return
		jal strcmp
				
		add $t1, $t1, 1
		j loop

	main:
		li $v0, 13
		la $a0, file
		li $a1, 0
		syscall
		move $s0, $v0
	
		li $v0, 14
		move $a0, $s0
		la $a1, buffer
		la $a2, 2048
		syscall
	
		li $v0, 16
		move $a0, $s0
		syscall
	
		li $v0, 13
		la $a0, file
		li $a1, 1
		syscall
		move $s0, $v0
	
		li $t0, 0
		la $t1, buffer
		loop:
			add $t0, $t0, 1
			lbu $t2, 0($t1)
			beqz $t2, end
			j cmp
		
		
		end:
			li $v0, 15
			move $a0, $s0
			la $a1, buffer
			move $a2, $t0
			syscall
			
			li $v0, 16
			move $a0, $s0
			syscall