main:
	addi $v0, $0, 5 #ajusta o argumento v0 para 5 (leitura)
	syscall #realiza a chamada de sistema para efetuar a leitura
	addi $s0, $v0, 0 #salva o numero do usuario em S0
	addi $t0, $0, 0 # inicializa a variável de iteração, i = 0
	addi $t2, $s0, 1 # argumento para finalização do loop "for", S0 + 1
	
	For:
	addi $t0, $t0, 1 # Incrementa a variável de iteração, i++
	beq $t0, $t2, EndFor #sai do loop se i = S0 + 1
	div $s0, $t0 #Divide S0 por i
	mfhi $t1 # copia resto para T1
	bne $0, $t1, For #Se o resto da divisão for diferente de zero
	addi $v0, $0, 1 #Configura Syscall para exibição (argumento no. 1, exibição de número inteiro)
	add $a0, $0, $t0 #Passa para o SysCall o dado a ser exibido
	syscall # realiza a chamada de sistema para efetuar a exibição
	addi $v0, $0, 11 #configura syscall para exibição (argumento no. 11, exibição de caractere)
	addi $a0, $0, 32 #
	syscall # realiza a chamada de sistema para efetuar a exibição
	j For # desvia para o início do loop
	
EndFor:
	addi $v0, $0, 10 #configura syscall para término de execução (argumento no. 10)
	syscall # realiza a chamada de sistema para efetuar a exibição
