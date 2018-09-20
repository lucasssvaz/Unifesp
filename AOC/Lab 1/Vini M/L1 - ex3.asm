#s0: a
#s1: m

main:
	addi $v0, $0, 5 #ajusta o argumento v0 para 5 (leitura)
	syscall #realiza a chamada de sistema para efetuar a leitura (número 'a')
	addi $s0, $v0, 0 #salva o numero 'a' do usuario em S0
	
	addi $v0, $0, 5 #ajusta o argumento v0 para 5 (leitura)
	syscall #realiza a chamada de sistema para efetuar a leitura (número 'm')
	addi $s1, $v0, 0 #salva o numero 'm' do usuario em S1
	
	addi $t0, $0, 0 # inicializa a variável de iteração, i = 0
	addi $t1, $s0, 0  # inicializa a variável que será multiplicada, j = 1	

Loop:
	mult $t1, $t1 #multiplica 'a' por ele mesmo
	mflo $t1 # salva em a o resultado da operação acima
	div $t1, $v1 # divide a por m
	mfhi $t2 # copia resto para t2
	beq $t2, 1, End
	addi $t0, $t0, 1
	j Loop
	
End:
	addi $v0, $0, 1 #Configura Syscall para exibição (argumento no. 1, exibição de número inteiro)
	add $a0, $0, $t0 #Passa para o SysCall o dado a ser exibido
	syscall # realiza a chamada de sistema para efetuar a exibição 
	addi $v0, $0, 10 #configura syscall para término de execução (argumento no. 10)
	syscall # realiza a chamada de sistema para efetuar a exibição
	
	
	