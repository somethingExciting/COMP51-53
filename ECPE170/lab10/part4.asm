.text
main: 
   #int A[5]; // Empty memory region for 5 elements
   #int B[5] = {1,2,3,4,5};
   #int C=12;
   #int i;

   #for(i=0; i<5; i++)
   #{
   #   A[i] = B[i] + C;
   #} 

   #i--;
   #while(i >= 0)
   #{
   #   A[i]=A[i]*2;
   #   i--;
   #} 

	#register map
	la $s0, A #s0 is the base addr for array A
	la $s1, B #s1 is the base addr for array B
	lw $s2, C #s2=C=12
	lw $s3, i #s3=i=0
	lw $s4, offset #s4=offset=0
	addi $t0, $zero, 5 #t0=5

	for: bge $s3, $t0, outsidefor #branch to outsidefor if i>=5 
		addi $t1, $zero, 4 #t1=4; each element is 4-bytes
		mul $s4, $s4, $s3 #offset*=i for B[i]
		add $t1, $s1, $s4 #t1= base addr of B[i] + offset
		lw $t2, 0($t1) #$t2 = *(base addr of B[i] + offset)
		add $t3, $t2, $s2 #B[i]+C
		
		addi $s4, $zero, 0 #offset=0
		mul $s4, $s4, $s3 #offset*=i for A[i]
		add $t1, $s0, $s4 #t1=base addr of A[i] + offset
		lw $t2, 0($t1) #t2 = *(base addr of A[i] + offset)
		
		sw $t3, 0($s0) #A[i]=B[i]+C
		addi $t3, $zero, 1 #t3=1
		add $s3, $s3, $t3 #i++
		j for #unconditional jump to for 
	outsidefor: 
		addi $t4, $zero, 1 #t4=1; subtract from i
		sub $s3, $s3, $t4 #i--
		addi $t4, $zero, 0 #t4=0
	while: blt $s3, $t4, exit #branch to outsidewhile if i<0
		addi $s4, $zero, 0 #offset=0
		mul $s4, $s4, $s3 #offset*=i for A[i]
		add $t4, $s0, $s4 #t5= base addr of A[i] + offset
		lw $t6, 0($t4) #t6= *(base addr of A[i] + offset)
 
		addi $t7, $zero, 2 #t7=2
		mul $t8, $t6, $t7 #t8= t6 * 2
		sw $t8, 0($s0) #A[i]=A[i]*2
		sub $s3, $s3, $t3 #i--
	exit:
		li $v0, 10
		syscall #exit program
	
.data
	A: .space 20 #space for 5 4-byte ints 
	B: .word 1, 2, 3, 4, 5 #assigning values to array B
	C: .word 12 #C=12
	i: .word 0 #i=0
	offset: .word 0 #offset=10
	
