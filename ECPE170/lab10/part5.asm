.text
main: 
  #char string[256];
  #int i=0;
  #char *result = NULL;  // NULL pointer is binary zero
  
  #Obtain string from user, e.g. "Constantinople"
  #scanf("%255s", string); 
  
  #Search string for letter 'e'. Result is pointer to first e (if it exists)
  #or NULL pointer if it does not exist
  #while(string[i] != '\0') {
  #  if(string[i] == 'e') {
  #    result = &string[i]; 
  #    break; // exit from while loop early
  #  }
  #  i++;
  #}

  #if(result != NULL) {
  #  printf("First match at address %d\n", result);
  #  printf("The matching character is %c\n", *result);
  #}
  #else
  #  printf("No match found\n");

	#register map
	la $s0, string #s0 is the base adddr for string 
	lw $s1, i #s1=i=0
	lw $s2, result #s2=result=0
	lw $s3, offset #s3=offset=0

	la $a0, enter #load addr of enter and save/store to a0
	li $v0, 4 #loads 4 into v0, op code for reading a string
	syscall #print; sees 4, knows to read in a string, then print that  

	la $a0, string #points to string to begin writing
	la $a1, string #gets length of a1 to not exceed memory limit
	li $v0, 8 #loads 8 into v0, op code for user input into a string
	syscall #print; sees 8, knows to ask user for input

	move $t9, $v0 #moves v0 to t9

	while: addi $t0, $zero, 1 #t0=1; each element is 1-byte
		mul $s3, $s3, $s1 #offset*=i
		add $t0, $t9, $s3 #t0= base addr of string + offset
		lbu $t1 0($t0) #stores t0 into t1 w/out sign extention		
 		beq $t1, $zero, outsidewhile #branch to outsidewhile if string[i]=\0
	if1: lbu $t2, 0($t9) #stores s0 into t2 w/out sign extention
		li $t3, 'e' #load e into t3
		bne $t2, $t3, outsideif #branch to outsideif if string[i]!='e'
		move $s2, $t1 #moves t2(val of string[i]) to s2(result); result=&string[i]
	outsideif: addi $t4, $zero, 1 #t4=1; add to i
		add $s1, $s1, $t4 #i++
		j while #unconditional loop to while
	outsidewhile: 
	if2: addi $t3, $zero, 0 #t3=0  
		beq $s2, $t3, else2 #branch to else2 if result=NULL(0)
		la $a0, addr #load addr of display message addr and save/store to a0
		li $v0, 4 #reading a string		
		syscall #print

		la $a0, result #hold addr of s2(result) 
		li $v0, 1 #reading an int
		syscall #print  

		la $a0, char #hold addr of display message char
		li $v0, 4 #reading a string
		syscall #print

		la $a0, 0($s2) #hold addr of the value of s2(result)
		li $v0, 12 #reading a char
		syscall #print 	
	else2: la $a0, none #hold addr of display message none
		syscall #print
	exit: 
		li $v0, 10
		syscall #exit program

.data
	string: .space 256 #space for 256 1-byte chars 
	i: .word 0 #i=0 
	result: .word 0 #result=0; use 0 to signify the end of the string
	offset: .word 0 #offset=0
	enter: .asciiz "Enter a string: " #display message
	addr: .asciiz "First match at address: " 
	char: .asciiz "The matching character is: "
	none: .asciiz "No match found\n"

