.data

	init: .float 1.0
	
.text 
j main

factorial:
	addi $s0, $zero, 1
	addi $t0, $zero, 1
	loop:
		bgt $t0, $t9, exit
		mul $s0, $s0, $t0
		addi $t0, $t0, 1
		j loop
	exit:
		jr $ra

main:
	addi $t9, $zero, 1
	l.s $f12, init
	l.s $f14, init
	taylor:
		bge $t9, 10, end
		jal factorial
		mtc1 $s0, $f16
  		cvt.s.w $f16, $f16
  		div.s $f16, $f14, $f16
  		add.s $f12, $f12, $f16
  		addi $t9, $t9, 1
		j taylor

end:
	addi $v0, $zero, 2
	syscall