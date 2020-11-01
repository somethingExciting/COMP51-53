.text
main:
   #int A=15;
   #int B=10;
   #int C=7;
   #int D=2;
   #int E=18;
   #int F=-3;
   #int Z=0;

   #Z = (A+B) + (C-D) + (E+F) - (A-C);

	#register map
	lw $s0, A #s0=A=15
	lw $s1, B #s1=B=10
	lw $s2, C #s2=C=7
	lw $s3, D #s3=D=2
	lw $s4, E #s4=E=18
	lw $s5, F #s5=F=-3
	lw $s6, Z #s6=Z=0

	add $t0, $s0, $s1 #t0=A+B
	sub $t1, $s2, $s3 #t1=C-D
	add $t2, $s4, $s5 #t2=E+F
	sub $t3, $s0, $s2 #t3=A-C
	
	add $t4, $t0, $t1 #t4=(A+B) + (C-D)
	sub $t5, $t2, $t3 #t5=(E+F) - (A-C)

	add $s6, $t4, $t5 #Z = (A+B) + (C-D) + (E+F) - (A-C)

	exit: 
		li $v0,10
		syscall #exit program 

.data
	A: .word 15 #A=15
	B: .word 10 #B=10
	C: .word 7 #C=7
	D: .word 2 #D=2
	E: .word 18 #E=18
	F: .word -3 #F=-3
	Z: .word 0 #Z=0
	
