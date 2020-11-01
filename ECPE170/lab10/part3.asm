.text
main: 
   #int Z=2;
   #int i;

   #i=0;
   #while(1){
   #  if(i>20)
   #    break;
   #Z++;
   #i+=2;
   #}
 
   #do {
   #   Z++;
   #} while (Z<100);
  
   #while(i > 0) {
   #   Z--;
   #   i--;


	#register map
	lw $s0, Z #s0=Z=2 
	lw $s1, i #s1=i=0
	addi $t0, $zero, 20 #t0=20

	whileOne: bge $s1, $t0, outsidewhileOne #branch to outsidewhile if i>=20
		addi $t1, $zero, 1 #t1=1; add to Z
		add $s0, $s0, $t1 #Z++
		addi $t2, $zero, 2 #t2=2; add to i
		add $s1, $s1, $t2 #i+=2
		j whileOne #unconditional jump to whileOne
	outsidewhileOne: 
		addi $t3, $zero, 100 #t3=100
	do: bge $s0, $t3, outsidedowhile #branch to outsidedowhile if Z>=100
		add $s0, $s0, $t1 #Z++
		j do #unconditional jump to do
	outsidedowhile:
		addi $t4, $zero, 0 #t4=0; compare if i<= 
	while: ble $s1, $t4, exit #branch to outsidewhile if i<=0
		sub $s0, $s0, $t1 #Z--
		sub $s1, $s1, $t1 #i--
		j while #unconditional jump to while 
	exit: 
		li $v0,10
		syscall #exit program

.data
	Z: .word 2 #Z=10
	i: .word 0 #i=10

