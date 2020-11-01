.globl main
.text 
main:
	#register map
	lw $s0, m_w #s0=m_w=50000
	lw $s1, m_z #s1=m_z=60000
	lw $s2, bint #s2=bint=0
	la $s3, a #s3 is the base addr of a
	lw $s4, i #s4=i=0
	lw $s5, offset #s5=offset=0
	
	addi $t0, $zero, 10 #t0=100
	for: bge $s4, $t0, exitfor #branch to exitfor if i>=100
		li $a0, 1 #low bound
		li $a1, 100000 #high bound

		jal random_in_range #jump to function random_in_range

		move $s2, $v0 #b=random num 
		mul $s5, $s4, 4 #offset=4i
		add $t1, $s3, $s5 #t1= base addr of a[i] + offset
		sw $s2, 0($t1) #saving s2 into t2; a[i]=b	
		addi $s4, $s4, 1 #i++ 
		j for #unconditional jump to for

	exitfor: 
		#a0 is 1st arg, a1 is 2nd arg, a2 is 3rd arg
		add $a0, $zero, $s3 #a0=base addr of a(s3) 
		li $a1, 0 #a1=0
		li $a2, 9 #a2=99

		jal quickSort #jump to quickSort function

		li $v0, 8 #reads 4 in v0 to read a string
		la $a0, sorted #hold addr of message sorted
		syscall #print
		move $t9, $v0 #move v0 into t9 		

	for2: addi $t0, $zero, 100 #t0=100 
		li $s4, 0 #reset i to 0
		bge $s4, $t0, exit #branch to exit if i>= 100
		mul $s5, $s4, 4 #offset=4i
		add $t1, $s3, $s5 #t1= base addr of a[i] + offset

		la $a0, printarray1 #load addr of printarray1 and save/store to a0 
		li $v0, 4 #loads 4 into v0, op code for reading a string 
		syscall #print
		
		la $a0, i #load addr of i(s4) and save/store to a0
		li $v0, 1 #loads 1 into v0; op code for reading an int 
		syscall #print
		
		la $a0, printarray2 #load addr of printarray2 and save/store to a0 
		li $v0, 4 #loads 4 into v0; op code for reading a string
		syscall #print
		
		lw $a0, 0($t2) #load addr of a[i](t2) and save/store to a0
		li $v0, 1 #loads 1 into v0; op code for reading an int	
     	syscall #print
		
		la $a0, printarray3 #load addr of printarray3 and save/store to a0
		li $v0, 4 #loads 4 into v0; op code for reading of string
		syscall #print

		addi $s4, $s4, 1 #i++
		j for2 #unconditional jump to for2		

	exit: 
		li $v0, 10 #reads 10 to exit the program
		syscall #exit program 		
	


		
quickSort: 
	#push s registers and ra
	addi $sp, $sp, -4 #sp moves down
	sw $s0, 0($sp) #push s0 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s1, 0($sp) #push s1 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s2, 0($sp) #push s2 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s3, 0($sp) #push s3 onto stack 
	addi $sp, $sp, -4 #sp moves down 
	sw $s4, 0($sp) #push s4 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s5, 0($sp) #push s5 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s6, 0($sp) #push s6 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s7, 0($sp) #push s7 onto stack 
	#store/push ra 
	addi $sp, $sp, -4 #sp moves down
	sw $ra, 0($sp) #push ra onto stack 

	#register map 
	#a0=a[]
	#a1=l
	#a2=r 
	if: bge $a1, $a2, exitif #branch to exitif if l >= r
	
		#backup t registers
		addi $sp, $sp, -4 #sp moves down 
		sw $t0, 0($sp) #save/store t0 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t1, 0($sp) #save/store t1 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t2, 0($sp) #save/store t2 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t3, 0($sp) #save/store t3 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t4, 0($sp) #save/store t4 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t5, 0($sp) #save/store t5 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t6, 0($sp) #save/store t6 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t7, 0($sp) #save/store t7 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t8, 0($sp) #save/store t8 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t9, 0($sp) #save/store t9 to stack

		#don't change arguments since they are the same
		#a0=a[] 
		#a1=l
		#a2=r
		#t0=j
		jal partition #jump to partition function 
		#retrieve return value in v0
		move $t0, $v0 #move v0 into j(t0)		

		#backup t registers
		addi $sp, $sp, -4 #sp moves down 
		sw $t1, 0($sp) #save/store t1 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t2, 0($sp) #save/store t2 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t3, 0($sp) #save/store t3 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t4, 0($sp) #save/store t4 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t5, 0($sp) #save/store t5 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t6, 0($sp) #save/store t6 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t7, 0($sp) #save/store t7 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t8, 0($sp) #save/store t8 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t9, 0($sp) #save/store t9 to stack

		#backup a registers
		addi $sp, $sp, -4 #sp moves down 
		sw $a2, 0($sp) #save/store a2 to stack

		#insert arguments in a registers
		#a0=a[]
		#a1=l
		#a2=j-1
		addi $a2, $t0, -1 #a2=j-1
		jal quickSort #jump to quickSort; recursion
		#retrieve return value in v0

		#backup t registers
		addi $sp, $sp, -4 #sp moves down 
		sw $t0, 0($sp) #save/store t0 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t1, 0($sp) #save/store t1 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t2, 0($sp) #save/store t2 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t3, 0($sp) #save/store t3 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t4, 0($sp) #save/store t4 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t5, 0($sp) #save/store t5 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t6, 0($sp) #save/store t6 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t7, 0($sp) #save/store t7 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t8, 0($sp) #save/store t8 to stack
		addi $sp, $sp, -4 #sp moves down 
		sw $t9, 0($sp) #save/store t9 to stack

		#backup a registers 
		addi $sp, $sp, -4 #sp moves down 
		sw $a1, 0($sp) #save/store a1 to stack

		#insert arguments in a registers
		#a0=a[]
		#a1=j+1
		#a2=r
		addi $a1, $t0, 1 #a1=j+1
		jal quickSort #jump to quickSort; recursion
		#retrieve return value is in v0

	exitif:
		lw $ra, 0($sp) #pop ra from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s7, 0($sp) #pop s7 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s6, 0($sp) #pop s6 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s5, 0($sp) #pop s5 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s4, 0($sp) #pop s4 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s3, 0($sp) #pop s3 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s2, 0($sp) #pop s2 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s1, 0($sp) #pop s1 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s0, 0($sp) #pop s0 from stack 

		#place return value in v0 if this function returns anything 
		jr $ra # jump back to caller: quicksort




partition: 
	#push s registers and ra
	addi $sp, $sp, -4 #sp moves down
	sw $s0, 0($sp) #push s0 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s1, 0($sp) #push s1 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s2, 0($sp) #push s2 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s3, 0($sp) #push s3 onto stack 
	addi $sp, $sp, -4 #sp moves down 
	sw $s4, 0($sp) #push s4 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s5, 0($sp) #push s5 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s6, 0($sp) #push s6 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s7, 0($sp) #push s7 onto stack 
	#store/push ra 
	addi $sp, $sp, -4 #sp moves down
	sw $ra, 0($sp) #push ra onto stack 

	#register map
	#a0=a[] 
	#a1=l
	#a2=r
	li $s0, 0 #pivot=0
	li $s1, 0 #i=0
	li $s2, 0 #j=0
	li $s3, 0 #t=0 
	li $s4, 1 #s4=1 for loop
	li $s5, 1 #s5=1 for loop
	
	add $s6, $a0, $a1 #s6=a[l]
	move $s0, $s6 #move a[l](s6) to pivot(s0) 
	move $s1, $a1 #move l(a1) to i(s1) 
	addi $s6, $a2, 1 #s6=r(a2)+1
	move $s2, $s6 #move r+1(s6) to j(s2) 
	while: bne $s4, $s5, exitwhile #branch to exitwhile if 1(s4) /=/ 1(s5)
		dowhile1: addi $s1, $s1, 1 #i++
			add $s6, $a0, $s1 #s6=a[i]
			ble $s6, $s0, exception2 #branch to exception2 if a[i] <= pivot
			exception2: ble $s1, $a2, dowhile2 #branch to dowhile2 if i <= r
			j dowhile1 #unconditional jump to dowhile1

		dowhile2: addi $s2, $s2, -1 #j--
			add $s6, $a0, $s2 #s6=a[j]
			bgt $s6, $s0, iffy #branch to iffy if a[j] > pivot 
			j dowhile2 #unconditional jump to dowhile2

		iffy: bge $s1, $s2, exitwhile #branch to exitwhile if i >= j
			add $s6, $a0, $s1 #s6=a[i]
			move $s3, $s6 #move a[i] into t(s3); t=a[i]
			add $s6, $a0, $s1 #s6=a[i]
			add $s7, $a0, $s2 #s7=a[j]
			move $s6, $s7 #move a[j](s7) into a[i](s6)
			add $s7, $a0, $a2 #s7=a[j]
			move $s7, $s3 #a[j]=t 

		j while #unconditional jump to while
 
	exitwhile: 
		add $s6, $a0, $a1 #s6=a[l]
		move $s3, $s6 #move a[l](s6) into t(s3)
		add $s6, $a0, $a1 #s6=a[l]
		add $s7, $a0, $s2 #s7=a[j]
		move $s6, $s7 #a[l]=a[j]
		add $s7, $a0, $s2 #s7=a[j]
		move $s7, $s3 #a[j]=t

		lw $ra, 0($sp) #pop ra from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s7, 0($sp) #pop s7 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s6, 0($sp) #pop s6 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s5, 0($sp) #pop s5 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s4, 0($sp) #pop s4 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s3, 0($sp) #pop s3 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s2, 0($sp) #pop s2 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s1, 0($sp) #pop s1 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s0, 0($sp) #pop s0 from stack 
		
		#place return value in v0 if function returns anything
		move $v0, $s2 #return j

		jr $ra # jump back to caller: quicksort




random_in_range: 
	addi $sp, $sp, -4 # increment stack pointer
	sw $ra, 0($sp) # store address call
	subu $t0, $a1, $a0 # t0 = range of input
	addiu $t0, $t0, 1 # t0++
	addi $sp, $sp, -4 # increment counter
	sw $t0, 0($sp) # store t0

	jal get_random # calling get_random

	lw $t0, 0($sp) # reload t0 into register
	addi $sp, $sp, 4 # increment counter
	lw $t1, result # load t
	divu $t1, $t0 # unsigned binary division
	mfhi $t0 # move hi register value into t0
	addu $v0, $t0, $a0 # v0 = t0 + a0
	lw $ra, 0($sp) # ra = stack.pop()
	addi $sp, $sp, 4 # increment stack to next value

	jr $ra # jump back to caller: main
	



get_random: 
	lw $t0, m_z # t0 = m_z
	li $t1, 36969 # ti = 36969
	andi $t2, $t0, 65535 # t2 = bitwise and of t0 and 65535
	mul $t2, $t1, $t2 # t2 = t2 * t1
	srl $t1, $t0, 16 # t1 = t0 >> 16
	addu $t0, $t2, $t1 # t0 = t2 + t1
	sw $t0, m_z # m_z = t0
	lw $t1, m_w # t1 = m_w
	li $t2, 18000 # t2 = 18000
	andi $t3, $t1, 65535 # t3 = bitwise and of t1 and 65535
	mul $t3, $t2, $t3 # t3 = t3 * t2
	srl $t2, $t1, 16 # t2 = t0 >> 16
	addu $t1, $t3, $t2 # t1 = t3 + t2
	sw $t1, m_w # m_w = t1
	sll $t0, $t0, 16 # t0 = t0 << 16
	addu $t0, $t0, $t1 # t0 += t1
	sw $t0, result # result = t0

	jr $ra # jump back to caller: random_in_range




.data
	m_w: .word 50000 # m_w = 50000
	m_z: .word 60000 # m_z = 60000
	bint: .word 0 # b = 0 
	a: .space 3200 # space for 100 32-byte uints
	i: .word 0 # i = 0
	result: .word 0 # result = 0
	offset: .word 0 # offset = 0
	sorted: .asciiz "\n Sorted array is:\n" # display message
	printarray1: .asciiz "a[" # first part of print array
	printarray2: .asciiz " ]= " # second part of print array
	printarray3: .asciiz "\n" # third part of print array; newline

