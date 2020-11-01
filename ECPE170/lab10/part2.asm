.text
main:
   #Note: I should be able to change the values of A, B, and C when testing
   #your code, and get correct output each time! (i.e. don't just hardwire your output)
   #int A=10;
   #int B=15;
   #int C=6;
   #int Z=0;


   #if(A > B || C < 5)
   #   Z = 1;
   #else if((A > B) && ((C+1) == 7))
   #   Z = 2;
   #else
   #   Z = 3;

   #switch(Z)
   # {
   #   case 1:
   #      Z = -1;
   #      break;
   #   case 2:
   #      Z -=-2;
   #      break;
   #   default:
   #      Z = 0;
   #     break;
   # }

	#register map
	lw $s0, A #s0=A=10
	lw $s1, B #s1=B=15
	lw $s2, C #s2=C=6
	lw $s3, Z #s3=Z=0

	if: bgt $s0, $s1, ZeqOne #branch to Z=1 if A>B
		addi $t0, $zero, 5 #t0=5
		blt $s2, $t0, ZeqOne #branch to Z=1 if C<5
		j elseif #unconditional jump to elseif
	ZeqOne: addi $s3, $zero, 1 #Z=1
		j outsideelse #uncondtional jump to outsideelse
	elseif: ble $s0, $s1, else #branch to else if A<=B
		addi $t0, $zero, 1 #t0=1; add to C
		add $s2, $s2, $t0 #C++
		addi $t0, $zero, 7 #t0=7; compare if C=
		beq $s2, $t0, ZeqTwo #branch to Z=2 if C=7 & A>B
		j else #unconditional jump to else
	ZeqTwo: addi $s3, $zero, 2 #Z=2
		j outsideelse #unconditional jump to outsideelse
	else: addi $s3, $zero, 3 #Z=3
	outsideelse: 
		caseOne: addi $t0, $zero, 1 #t0=1; compare if Z/=/
			bne $s3, $t0, caseTwo #branch to caseTwo if Z/=/1
			addi $s3, $zero, -1 #Z=-1
			j exit #unconditional jump to outsideswitch
		caseTwo: addi $t0, $zero, 2 #t0=2; compare if Z/=/
			bne $s3, $t0, default #branch to default if Z/=/2
			addi $t0, $zero, -2 #t0=-2
			sub $s3, $s3, $t0 #Z-=-2
			j exit #unconditional jump to outsideswitch
		default: addi $s3, $zero, 0 #Z=0
	exit: 
		li $v0,10
		syscall #exit program

.data
	A: .word 10 #A=10
	B: .word 15 #B=15
	C: .word 6 #C=6
	Z: .word 0 #Z=10

