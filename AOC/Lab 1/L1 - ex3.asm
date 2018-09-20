#s0: a
#s1: m

main:
	addi $v0, $0, 5 #ajusta o argumento v0 para 5 (leitura)
	syscall #realiza a chamada de sistema para efetuar a leitura (numero 'a')
	addi $s0, $v0, 0 #salva o numero 'a' do usuario em S0
	
	addi $v0, $0, 5 #ajusta o argumento v0 para 5 (leitura)
	syscall #realiza a chamada de sistema para efetuar a leitura (numero 'm')
	addi $s1, $v0, 0 #salva o numero 'm' do usuario em S1
	
	addi $t0, $0, 1 # inicializa a variavel de iteração, i = 1
	addi $t1, $s0, 0  # inicializa a variavel auxiliar
	div $t1, $s1 # divide aux por m
	mfhi $t2 # copia resto para t2
	beq $t2, 1, End	# se resto = 1 então vai para End

Loop:
	addi $t0, $t0, 1 # incrementa valor de i
	mult $t1, $s0 # multiplica 'aux' por 'a'
	mflo $t1 # salva em a o resultado da operação acima
	div $t1, $s1 # divide aux por m
	mfhi $t2 # copia resto para t2
	beq $t2, 1, End # se resto = 1 então vai para End
	j Loop
	
End:
	addi $v0, $0, 1 #Configura Syscall para exibição (argumento no. 1, exibição de numero inteiro)
	add $a0, $0, $t0 #Passa para o SysCall o dado a ser exibido
	syscall # realiza a chamada de sistema para efetuar a exibição 
	addi $v0, $0, 10 #configura syscall para termino de execução (argumento no. 10)
	syscall # realiza a chamada de sistema para efetuar a exibição
	
	
	
