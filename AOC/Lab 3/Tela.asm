.data
	#Alguns exemplos de cores
	yellow:   .word 0xF5F62E
	white:	  .word 0xFFFFFF
	blue: 	  .word 0x2E8CF6
	orange:   .word 0xF67F2E
	black:	  .word 0x00000
	w:	  .word 0x00000077
	a:	  .word 0x00000061
	s:	  .word 0x00000073
	d:	  .word 0x00000064
	keyboard: .word 0xFFFF0004
	ready:	  .word	0xFFFF0000
.text
	j main

	mover:
		lw $t5, ($t7)
		
		lw $s6, w
		beq $t5, $s6, mw
		lw $s6, a
		beq $t5, $s6, ma
		lw $s6, s
		beq $t5, $s6, ms
		lw $s6, d
		beq $t5, $s6, md
		j while
		
		mw:	
			jal clear
			addi $t1, $t1, -512
			jal desenha
			j while
		ma:
			jal clear
			addi $t1, $t1, -4
			jal desenha
			j while
		ms:
			jal clear
			addi $t1, $t1, 512
			jal desenha
			j while
		md:
			jal clear
			addi $t1, $t1, 4
			jal desenha
			j while
	
	
	clear:
		addi $t2, $zero, 0
		lui $t3, 0x1004
		for:
			sw $s3, ($t3)
			addi $t3, $t3, 4
			addi $t2, $t2, 1		
			ble $t2, 65536, for
		jr $ra
	
	set_tela: #Inicia todos os valores para a tela
		addi $t0, $zero, 65536 #65536 = (512*512)/4 pixels
		add $t1, $t0, $zero #Adicionar a distribuição de pixels ao endereco
		lui $t1, 0x1004 #Endereco base da tela no heap, pode mudar se quiser
		jr $ra

	set_cores: #Salvar as cores em registradores
		lw $s3, black
		lw $s4, white
		lw $s5, yellow
		jr $ra

	desenha:
		add $t0, $zero, $t1
		addi $t2, $zero, 0
		loop_1: #Loop de linha branca no canto superior esquerdo
			sw $s4, ($t0) #Pinto o pixel na posicao $t0 com a cor de $s4
			addi $t0, $t0, 4 #Pulo +4 no pixel
			addi $t2, $t2, 1 #Contador +1
			beq $t2, 10, exit_1
			j loop_1
		exit_1:
			addi $t2, $zero, 0
			loop_2: #Loop de linha amarela para baixo ao final da branca
				sw $s5, ($t0)
				addi $t0, $t0, 512 #Ando de linha em linha, ou seja, 512
				addi $t2, $t2, 1
				beq $t2, 10, exit_2
				j loop_2
			exit_2:
				jr $ra

	main: 
		jal set_tela
		jal set_cores
		jal desenha
		lw $t7, keyboard
		lw $t6, ready
		
		while:	
			lw $t5, ($t6)
			bnez $t5, mover
			j while
			