.data
	.align 4
	mat1: .space 2048
	.align 4
	mat2: .space 2048
	.align 4
	matR: .space 2048
	nl: .word 10
	sp: .word 32
	
.text
	la $s0, mat1
	la $s1, mat2
	la $s2, matR
	addi $v0, $0, 5
	syscall
	move $s3, $v0 #tam linha
	mult $v0, $v0
	mflo $s4 #n elementos
	
	
	move $t0, $s0
	add $t1, $0, $0
	jal read_for
	move $t0, $s1
	add $t1, $0, $0
	jal read_for
	move $t0, $s0
	move $t1, $s1
	move $t2, $s2
	add $t3, $0, $0 #percorre resposta
	mul $s5, $s3, 4 #pular linha
	jal matrix_mult
	
	j end

	
	read_for:	
		beq $t1, $s4, read_exit
		addi $v0, $0, 5
		syscall
		sw $v0, ($t0)
		addi $t0, $t0, 4
		addi $t1, $t1, 1
		j read_for
		read_exit:
			jr $ra
			
	matrix_mult:
		beq $t3, $s4, matrix_mult_exit
		add $t4, $0, $0 #percorre linha/coluna
		add $t6, $0, $0
		line:
			beq $t4, $s3, line_exit
			lw $t8, ($t0)
			lw $t9, ($t1)
			mul $t5, $t8, $t9
			add $t6, $t6, $t5
			addi $t0, $t0, 4			
			add $t1, $t1, $s5
			addi $t4, $t4, 1
			j line
		
		line_exit:
		sw $t6, ($t2)
		addi $t2, $t2, 4
		
		sub $t0, $t0, $s5
		
		mul $t6, $s3, $s5
		sub $t1, $t1, $t6
		addi $t1, $t1, 4
		
		addi $t3, $t3, 1
		
		div $t3, $s3
		mfhi $t6
		bnez $t6, cont
		
		move $t1, $s1
		add $t0, $t0, $s5
		
		cont:
		j matrix_mult
		
		matrix_mult_exit:
			jr $ra
	end:
		li $t0, 0
		move $t1 $s2
		m_print:
			beq $t0, $s4, terminate
			lw $a0, ($t1)
			li $v0, 1
			syscall
			lw $a0, sp
			li $v0, 11
			syscall
			addi $t1, $t1, 4
			addi $t0, $t0, 1
			div $t0, $s3
			mfhi $t2
			bnez $t2, pula
			lw $a0, nl
			li $v0, 11
			syscall
			pula:
			j m_print
			
	terminate: