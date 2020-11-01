.globl main
li $s1, 6 # rows = 6
li $s2, 9 # cols = 9
la $s6, board # s6 = base addr of board
 
.text 
main: 
	#register map
	lw $s0, y # s0 = y
	lw $s3, decideTurn # s3 = decideTurn 
	lw $s4, compCol # s4 = compCol
	lw $s5, playerTurn # s5 = playerTurn 

	la $a0, connect5 # load addr of connect5 and save/store to a0
	li $v0, 4 # loads 4 into v0, op code for reading a string
	syscall # print 
	
	la $a0, initrand # load addr of initrand and save/store to a0
	li $v0, 4 # loads 4 into v0, op code for reading a string 
	syscall # print 

	while3:
		la $a0, number1 # load addr of number1 and save/store to a0
		li $v0, 4 # loads 4 into v0, op code for reading a string
		syscall # print
	
		li $v0, 5 # reads 5 in v0 to read an int from user
		syscall # get user input
		move $t0, $v0 # t0 = num1 

		if14: bgt $t0, $zero, while4 # branch to while4 if num1 > 0
			la $a0, notok # load addr of notok and save/store to a0
			li $v0, 4 # loads 4 into v0, op code for reading a string
			syscall # print
		j while3 # unconditional jump to while3
 
	while4: 
		la $a0, number2 # load addr of number2 and save/store to a0
		li $v0, 4 # loads 4 into v0, op code for reading a string
		syscall # print 

		li $v0, 5 # reads 5 in v0 to read an int from user 
		syscall # get user input
		move $t1, $v0 # t1 = num2 

		if15: bgt $t1, $zero, exitwhile4 # branch to exitwhile4 if num2 > 0
			la $a0, number1 # load addr of number1 and save/store to a0
			li $v0, 4 # loads 4 into v0, op code for reading a string
			syscall # print
		j while4 # unconditional jump to while4

	exitwhile4:
	if17: ble $t0, $t1, exitif17 # branch to exitif17 if num1 > num2 
		sw $t2, 0($t1) # temp = num2
		sw $t1, 0($t1) # num2 = num1
		sw $t0, 0($t2) # num1 = temp

	exitif17:
	#call random_in_range()
	sw $a0, 0($t0) # a0 = t0
	sw $a1, 0($t1) # a1 = t1

	jal random_in_range # jump to function random_in_range() 

	move $s3, $v0 # s3 = v0; decideTurn = random_in_range(num1, num2)
	
	la $a0, human # load addr of human and save/store to a0
	li $v0, 4 # loads 4 into v0, op code for reading a string 
	syscall # print 

	la $a0, computer # load addr of computer and save/store to a0
	li $v0, 4 # loads 4 into v0, op code for reading a string
	syscall # print

	la $a0, coin # load addr of coin and save/store to a0
	li $v0, 4 # loads 4 into v0, op code for reading a string
	syscall # print

	if1: li $t0, 2	# t0 = 2
		div $s3, $t0 # s3/t0; decideTurn/2
		mfhi $t0 # decideTurn%2
		bne $t0, $zero, else1 # branch to else1 if decideTurn%2!=0
		la $a0, you # load addr of you and save/store to a0
		li $v0, 4 # loads 4 into v0, op code for reading a string 
		syscall # print 
	else1:
		la $a0, notyou # load addr of notoyu and save/store to a0
		li $v0, 4 # loads 4 into v0, op code for reading a string 
		syscall # print 

	li $a0, 1 # a0 = 1
	#call print_board() 
	jal print_board # jump to function print_board()

	while1: 	
		if2: li $t0, 1 # t0 = 1; t0=true
			bne $s5, $t0, else2 # branch to else2 if playerTurn!=0; playerTurn == false
			
			while5:	
				la $a0, entercol # load addr of entercol and save/store to a0
				li $v0, 4 # loads 4 into v0, op code for reading a string 
				syscall # print

				li $v0, 5 # reads 5 in v0 to read an int from the user
				syscall # get user input 
				move $s0, $v0 # y = user input

				if16: bgt $s0, $zero, exitwhile5 # branch to exitwhile5 if y > 0
					la $a0, notok # load addr of notok and save/store to a0
					li $v0, 4 # loads 4 into v0, op code for reading a string
					syscall # print
				j while5 # unconditional jump to while5

			exitwhile5:
			#call place_on_board
			lb $a0, 72 # 1st arg; a0 = 'H'
			sw $a1, 0($s0) # 2nd arg; a1 = y

			jal place_on_board  # jump to function place_on_board()

			li $s5, 0 # s5 = 0; playerTurn = false
			
			#call win() 
			jal win # jump to function win
			
			move $t0, $v0 # t0 = v0

			if3: li $t1, 1 # t1 = 1
				bne $t0, $t1, else2 # branch to else2 if win() != 1
				
				#call print_board()
				li $a0, 0 # 1st arg; a0 = 0; a0 = false
				jal print_board # jump to function print_board()

				la $a0, winning # load addr of winning and save/store to a0
				li $v0, 4 # loads 4 into v0, op code for reading a string 
				syscall # print 

				j exit # unconditional jump to exit


		else2: 
			#call random_in_range() 
			li $a0, 1 # 1st arg; a0 = 1; low bound
			li $a1, 7 # 2nd arg; a1 = 7; high bound

			jal random_in_range #jump to function random_in_range()

			move $s4, $v0 # s4 = v0; compCol = random_in_range(num1, num2)
			
			la $a0, compselect # load addr of compselect and save/store to a0
			li $v0, 4 # loads 4 into v0, op code for reading a string 
			syscall # print 

			li $v0, 1 # loads 1 into v0, op code for printing an int
			lw $a0, 0($s4)  # a0 = s4; a0 = compCol
			syscall # print 
			
			#call place_on_board() 
			lb $a0, 67 # 1st arg; a0 = 'C'
			sw $a1, 0($s4) # 2nd arg; a1 = compCol

			jal place_on_board # jump to function place_on_board 

			#call print_board() 
			li $a0, 0 # 1st arg; a0 = 0; a0 = false 
			jal print_board # jump to function print_board 

			li $s5, 1 # s5 = 1; playerTurn = true

			#call win() 
			jal win # jump to function win()

			move $t0, $v0 # t0 = v0

			if4: li $t1, 1 # t1 = 1
				bne $t0, $t1, if2 # branch to if2 if win() != 1
				
				la $a0, lose # load addr of lose and save/store to a0
				li $v0, 4 # loads 4 into v0, op code for reading a string 
				syscall # print

				j exit # unconditional jump to exit

		if5: 
			#call win() 
			jal win # jump to function win() 
			move $t0, $v0 # t0 = v0
			
			#call check_tie() 
			move $a0, $t0 # 1st arg; a0 = t0; a0 = win() 
			jal check_tie # jump to function check_tie() 
			move $t0, $v0 # t0 = v0 
			
			li $t1, 1 # t1 = 1
			bne $t0, $t1, while1 # branch to while1 if check_tie(win()) != 1
				
	exit: 
		li $v0, 10 #reads 10 to exit the program
		syscall #exit program 	


#functions

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


print_board:
	#push s registers and ra
	addi $sp, $sp, -4 #sp moves dow
	sw $s0, 0($sp) #push s0 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s3, 0($sp) #push s3 onto stack 
	addi $sp, $sp, -4 #sp moves down 
	sw $s4, 0($sp) #push s4 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s5, 0($sp) #push s5 onto stack  
	addi $sp, $sp, -4 #sp moves down
	sw $s7, 0($sp) #push s7 onto stack 
	#store/push ra 
	addi $sp, $sp, -4 #sp moves down
	sw $ra, 0($sp) #push ra onto stack 

	#register map 
	#a0 = init 

	#<functiony things happen here> 
	addi $sp, $sp, -4 #sp moves down
	sw $a0, 0($sp) # push/save a0 to stack
	la $a0, header # load addr of header and save/store to a0
	li $v0, 4 # loads 4 into v0; op code for reading a string
	syscall # print 
	lw $a0, 0($sp) # pop a0 from stack
	addi $sp, $sp, 4 # sp moves up

	li $t9, 45 # t9 = 45; ascii value of '-' 

	for1: li $s3, 0 # i = 0
		bge $s3, $s1, exitfor1 # branch to exitfor1 if i >= 6
		for2: li $s4, 0 # j = 0
			bge $s4, $s2, exitfor2 # branch for exitfor1 if j >= 9 

			#calculate array offset
			mul $t0, $s3, 9 #i*9
			add $t0, $t0, $s4 #(i*9+j)
			add $t0, $t0, $s6 #(i*9+j) + board

			if12: bne $a0, $zero, jcheck # branch to jcheck if init = false
				sb $t9, 0($s6) # board[i][j] = '-'
			jcheck: beq $s4, $zero, if13 # branch to if13 if j == 0
				li $t1, 8 # t1 = 8				
				beq $s4, $t1, if13 # branch to if13 if j == 8
				j jcheck2 # unconditional jump to jcheck2 
			if13: li $t1, 2 # t1 = 2
				div $s3, $t1 # i/2 
				mfhi $t1 # t1 = i%2 
				li $t2, 1 # t2 = 1
				bne $t1, $t2, jcheck2 # branch to jcheck2 if i%2 != 1 
				li $t3, 72 # t3 = 'H'
				sb $t0, 0($t3) # sets 'H' to board[i][j]
			jcheck2: beq $s4, $zero, if18 # branch to if15 if j==0 
				li $t1, 8 # t1 = 8
				beq $s4, $t1, if18 # branch to if15 if j == 8
				j exitif15 # unconditional jump to exitif15
			if18: li $t1, 2 # t1 = 2 
				div $s3, $t1 # i/2
				mfhi $t1 # t1 = i%2
				bne $t1, $zero, exitif18 # branch to exitif15 if i%2 != 0 
				li $t2, 67 # t2 = 'C'
				sb $t0, 0($t2) # sets 'c' to board[i][j]
			exitif18: 
				sw $t0, 0($a0) # load addr of board[i][j] and save/store to a0
				li $v0, 1 # loads 1 into v0; op code for printing an int 
				syscall # syscall: print the int

			addi $s4, $s4, 1 # j++
			j for2 # unconditional jump to for2
		exitfor2: 
			addi $s3, $s3, 1 # i++ 
			j for1 # unconditional jump to for1
	exitfor1: 
	addi $sp, $sp, -4 #sp moves down
	sw $a0, 0($sp) # push/save a0 to stack
	la $a0, newline # load addr of newline and save/store to a0
	li $v0, 4 # loads 4 into v0; op code for reading a string
	syscall # print 
	lw $sp, 0($sp) # pop a0 from stack
	addi $sp, $sp, 4 # sp moves up

	lw $ra, 0($sp) #pop ra from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s7, 0($sp) #pop s7 from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s5, 0($sp) #pop s5 from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s4, 0($sp) #pop s4 from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s3, 0($sp) #pop s3 from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s0, 0($sp) #pop s0 from stack 
	
	#place return value in v0 if function returns anything

	jr $ra # jump back to caller: main


#not donezo 
win:
	#push s registers and ra
	addi $sp, $sp, -4 #sp moves down
	sw $s0, 0($sp) #push s0 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s3, 0($sp) #push s3 onto stack 
	addi $sp, $sp, -4 #sp moves down 
	sw $s4, 0($sp) #push s4 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s5, 0($sp) #push s5 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s7, 0($sp) #push s7 onto stack 
	#store/push ra 
	addi $sp, $sp, -4 #sp moves down
	sw $ra, 0($sp) #push ra onto stack 

	#<functiony things happen here> 
	for5: li $s3, 0 # i = 0
		bge $s3, $s1, exitfor1 # branch to exitfor1 if i >= 6
		for6: li $s4, 0 # j = 0
			bge $s4, $s2, exitfor2 # branch for exitfor1 if j >= 9 

			#calculate array offset
			mul $t0, $s3, 9 #i*9
			add $t0, $t0, $s4 #(i*9+j)
			add $t0, $t0, $s6 #(i*9+j) + board

			if19: li $t1, 45 # t1 = 45; ascii value of '-' 
				beq $t0, $t1, exitfor6 # branch to exitfor6 if board[i][j] == '-'

				checkeroni: addi $t2, $s3, 4 # t2 = i+4
					blt $t2, $s1, if20 # branch to if20 if (i+4) < rows 
				if20: addi $t3, $s4, 4 # t3 = j+4
					blt $t3, $s2, top_down_diagonal # branch to top_down_diagonal if (j+4) < cols
					j checkeroni2 # unconditional jump to checkeroni2 
					top_down_diagonal: addi $t4, $s3, 1 # i+1
						addi $t5, $s4, 1 # j+1 
						add $t6, $t4, $t5 # (i+1) + (j+1)
						add $t6, $t6, $s6 #(i*9+j) + board
						bne $t0, $t6, checkeroni2 # branch to checkeroni2 if board[i][j] != board[i+1][j+1]

						addi $t4, $t4, 1 # i+2
						addi $t5, $t5, 1 # j+2 
						add $t6, $t4, $t5 # (i+2) + (j+2)
						add $t6, $t6, $s6 #(i*9+j) + board
						bne $t0, $t6, checkeroni2 # branch to checkeroni2 if board[i][j] != board[i+2][j+2]

						addi $t4, $t4, 1 # i+3
						addi $t5, $t5, 1 # j+3 
						add $t6, $t4, $t5 # (i+3) + (j+3)
						add $t6, $t6, $s6 #(i*9+j) + board
						bne $t0, $t6, checkeroni2 # branch to checkeroni2 if board[i][j] != board[i+3][j+3]

						addi $t4, $t4, 1 # i+4
						addi $t5, $t5, 1 # j+4 
						add $t6, $t4, $t5 # (i+4) + (j+4)
						add $t6, $t6, $s6 #(i*9+j) + board
						bne $t0, $t6, checkeroni2 # branch to checkeroni2 if board[i][j] != board[i+4][j+4]

						li $t9, 1 # t9 = 1; return 1 if win
						j donezo # unconditional jump to donezo

				checkeroni2: blt $t2, $s1, if21 # branch to if21 if (i+4) < rows
				if21: addi $t3, $s4, -4 # t3 = j-4
					bge $t3, $zero, bottom_up_diagonal # branch to bottom_up diagonal if (j-4) >= 0
					j if22 # unconditional jump to if22 
					bottom_up_diagonal: addi $t4, $s3, 1 # i+1
						addi $t5, $s4, -1 # j-1
						add $t6, $t4, $t5 # (i+1) + (j-1)
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, if22 # branch to if22 if board[i][j] != board[i+1][j-1]

						addi $t4, $t4, 1 # i+2
						addi $t5, $t5, -1 # j-2
						add $t6, $t4, $t5 # (i+2) + (j-2)
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, if22 # branch to if22 if board[i][j] != board[i+2][j-2]

						addi $t4, $t4, 1 # i+3
						addi $t5, $t5, -1 # j-3
						add $t6, $t4, $t5 # (i+3) + (j-3)
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, if22 # branch to if22 if board[i][j] != board[i+3][j-3]

						addi $t4, $t4, 1 # i+4
						addi $t5, $t5, -1 # j-4
						add $t6, $t4, $t5 # (i+4) + (j-4)
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, if22 # branch to if22 if board[i][j] != board[i+4][j-4]

						li $t9, 1 # t9 = 1; return 1 if win
						j donezo # unconditional jump to donezo

				if22: addi $t3, $s4, 4 # t3 = j+4
					blt $t3, $s2, horizontal # branch to horizontal if (j+4) < cols
					j if23 # unconditional jump to if23
					horizontal: addi $t5, $s4, 1 # j+1
						add $t6, $s3, $t5 # i + (j + 1) 
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, if23 # branch to if23 if board[i][j] != board[i][j+1]

						addi $t5, $t5, 1 # j+2
						add $t6, $s3, $t5 # i + (j+2) 
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, if23 # branch to if23 if board[i][j] != board[i][j+2]

						addi $t5, $t5, 1 # j+3
						add $t6, $s3, $t5 # i + (j+3) 
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, if23 # branch to if23 if board[i][j] != board[i][j+3]

						addi $t5, $t5, 1 # j+4
						add $t6, $s3, $t5 # i + (j+4) 
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, if23 # branch to if23 if board[i][j] != board[i][j+4]

						li $t9, 1 # t9 = 1; return 1 if win 
						j donezo # unconditional jump to donezo 

				if23: addi $t2, $s3, 4 # t3 = i+4
					blt $t2, $s1, vertical # branch to vertical if (i+4) < rows 
					j exitfor5 # unconditional jump to exitfor5
					vertical: addi $t4, $s3, 1 # i+1 
						add $t6, $t4, $s4 # (i+1) + j 
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, exitfor5 # branch to exitfor5 if board[i][j] != board[i+1][j]

						addi $t4, $t4, 1 # i+2
						add $t6, $t4, $s4 # (i+2) + j 
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, exitfor5 # branch to exitfor5 if board[i][j] != board[i+2][j]

						addi $t4, $t4, 1 # i+3
						add $t6, $t4, $s4 # (i+3) + j 
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, exitfor5 # branch to exitfor5 if board[i][j] != board[i+3][j]

						addi $t4, $t4, 1 # i+4
						add $t6, $t4, $s4 # (i+4) + j 
						add $t6, $t6, $s6 # (i*9+j) + board 
						bne $t0, $t6, exitfor5 # branch to exitfor5 if board[i][j] != board[i+4][j]

			addi $s4, $s4, 1 # j++
			j for6 # unconditional jump to for6

		exitfor6:
		addi $s3, $s3, 1 # i++
		j for5 # unconditional jump to for5

	exitfor5:
		addi $t9, $t9, 0 # t9 = 0; return 0 if lose/no win

	donezo: 		
		lw $ra, 0($sp) #pop ra from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s7, 0($sp) #pop s7 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s5, 0($sp) #pop s5 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s4, 0($sp) #pop s4 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s3, 0($sp) #pop s3 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s0, 0($sp) #pop s0 from stack 
	
		#place return value in v0 if function returns anything
		move $t9, $v0 # return win
		jr $ra # jump back to caller: main


place_on_board:
	#push s registers and ra
	addi $sp, $sp, -4 #sp moves down
	sw $s0, 0($sp) #push s0 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s3, 0($sp) #push s3 onto stack 
	addi $sp, $sp, -4 #sp moves down 
	sw $s4, 0($sp) #push s4 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s5, 0($sp) #push s5 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s7, 0($sp) #push s7 onto stack 
	#store/push ra 
	addi $sp, $sp, -4 #sp moves down
	sw $ra, 0($sp) #push ra onto stack 

	#register map 
	#a0 = char space 
	#a1 = int col_choice 

	#<functiony things happen here> 
	addi $s3, $s1, -1 # s3 = rows-1 = currow
	li $s4, 0 # y = 0
	li $s5, 45 # s5 = 45; ascii value of '-'
	li $s7, 72 # s6 = 72; ascii value of 'H'
	
	while2: 
		add $s0, $s3, $a1 # s0 = currow + col_choice
		add $s0, $s0, $s6 # (currow + col_choice) + board
		if9: beq $s0, $s5, else9 # branch to else9 if board[currow]col_choice] != '-'
			addi $s3, $s3, -1 # currow--
			j if10 # unconditional jump to if10
		else9: sb $a0, 0($s0)
			j exitwhile2 # unconditional jump to exitwhile2
			
		if10: bge $s3, 0, while2 # branch to while2 if currow >= 0
			ble $a1, 7, while2 # branch to while2 if col_choice <= 7 
			bge $a1, 1, while2 # branch to while2 if col_choice >= 1
			if11: bne $s0, $s7, else11 # branch to else11 if space != 'H'

				addi $sp, $sp, -4 #sp moves down
				sw $a0, 0($sp) # push/save a0 to stack
				la $a0, invalid # load addr of invalid and save/store to a0
				li $v0, 4 # loads 4 into v0; op code for reading a string
				syscall # print 
				lw $sp, 0($sp) # pop a0 from stack
				addi $sp, $sp, 4 # sp moves up
				
				li $v0, 5 # reads 5 in v0 to read an int from user
				syscall # get user input
				move $s4, $v0 # y = user input 

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

				#save/push a
				addi $sp, $sp, -4 #sp moves down
				sw $a1, 0($sp) #push a1 onto stack
				addi $sp, $sp, -4 #sp moves down
				sw $a2, 0($sp) #push a2 onto stack
				addi $sp, $sp, -4 #sp moves down
				sw $a3, 0($sp) #push a3 onto stack

				#a0 remains the same since it is used as a parameter again
				add $a1, $zero, $s4 # a1 = y
				jal place_on_board #jump to place_on_board function 
				#retrieve return value in v0

				#pop a
				lw $a3, 0($sp) #read a3 
				addi $sp, $sp, 4 #sp moves up 
				lw $a2, 0($sp) #read a2 
				addi $sp, $sp, 4 #sp moves up 
				lw $t1, 0($sp) #read a1
				addi $sp, $sp, 4 #sp moves up 
				lw $a0, 0($sp) #read a0 
				addi $sp, $sp, 4 #sp moves up 

				#pop t 
				lw $t9, 0($sp) #read t9 
				addi $sp, $sp, 4 #sp moves up 
				lw $t8, 0($sp) #read t8 
				addi $sp, $sp, 4 #sp moves up 
				lw $t7, 0($sp) #read t7 
				addi $sp, $sp, 4 #sp moves up 
				lw $t6, 0($sp) #read t6 
				addi $sp, $sp, 4 #sp moves up 
				lw $t5, 0($sp) #read t5 
				addi $sp, $sp, 4 #sp moves up 
				lw $t4, 0($sp) #read t4 
				addi $sp, $sp, 4 #sp moves up 
				lw $t3, 0($sp) #read t3 
				addi $sp, $sp, 4 #sp moves up 
				lw $t2, 0($sp) #read t2
				addi $sp, $sp, 4 #sp moves up 
				lw $t1, 0($sp) #read t1 
				addi $sp, $sp, 4 #sp moves up 
				lw $t0, 0($sp) #read t0 
				addi $sp, $sp, 4 #sp moves up 

				j exitwhile2 # unconditional jump to exitwhile2

			else11: 
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

				#save/push a
				addi $sp, $sp, -4 #sp moves down
				sw $a1, 0($sp) #push a1 onto stack
				addi $sp, $sp, -4 #sp moves down
				sw $a2, 0($sp) #push a2 onto stack
				addi $sp, $sp, -4 #sp moves down
				sw $a3, 0($sp) #push a3 onto stack

				#a0 remains the same since it is used as a parameter again 
				div $a1, $s2 # col_choice/cols 
				mfhi $a1 # a1 = col_choice%cols 
				addi $a1, $a1, 1 # (col_choice%9) + 1
				jal place_on_board #jump to place_on_board function 
				#retrieve return value in v0

				#pop a
				lw $a3, 0($sp) #read a3 
				addi $sp, $sp, 4 #sp moves up 
				lw $a2, 0($sp) #read a2 
				addi $sp, $sp, 4 #sp moves up 
				lw $t1, 0($sp) #read a1
				addi $sp, $sp, 4 #sp moves up 
				lw $a0, 0($sp) #read a0 
				addi $sp, $sp, 4 #sp moves up 

				#pop t 
				lw $t9, 0($sp) #read t9 
				addi $sp, $sp, 4 #sp moves up 
				lw $t8, 0($sp) #read t8 
				addi $sp, $sp, 4 #sp moves up 
				lw $t7, 0($sp) #read t7 
				addi $sp, $sp, 4 #sp moves up 
				lw $t6, 0($sp) #read t6 
				addi $sp, $sp, 4 #sp moves up 
				lw $t5, 0($sp) #read t5 
				addi $sp, $sp, 4 #sp moves up 
				lw $t4, 0($sp) #read t4 
				addi $sp, $sp, 4 #sp moves up 
				lw $t3, 0($sp) #read t3 
				addi $sp, $sp, 4 #sp moves up 
				lw $t2, 0($sp) #read t2
				addi $sp, $sp, 4 #sp moves up 
				lw $t1, 0($sp) #read t1 
				addi $sp, $sp, 4 #sp moves up 
				lw $t0, 0($sp) #read t0 
				addi $sp, $sp, 4 #sp moves up 

	exitwhile2: 
		lw $ra, 0($sp) #pop ra from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s7, 0($sp) #pop s7 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s5, 0($sp) #pop s5 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s4, 0($sp) #pop s4 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s3, 0($sp) #pop s3 from stack 
		addi $sp, $sp, 4 #sp moves up
		lw $s0, 0($sp) #pop s0 from stack 
	
		#place return value in v0 if function returns anything

		jr $ra # jump back to caller: main/place_on_board


check_tie:
	#push s registers and ra
	addi $sp, $sp, -4 #sp moves down
	sw $s0, 0($sp) #push s0 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s3, 0($sp) #push s3 onto stack 
	addi $sp, $sp, -4 #sp moves down 
	sw $s4, 0($sp) #push s4 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s5, 0($sp) #push s5 onto stack 
	addi $sp, $sp, -4 #sp moves down
	sw $s7, 0($sp) #push s7 onto stack 
	#store/push ra 
	addi $sp, $sp, -4 #sp moves down
	sw $ra, 0($sp) #push ra onto stack 

	#register map 
	#a0 = win 

	#<functiony things happen here>
	li $s0, 0 # s0 = 0; counter = 0
	li $s1, 45 # s1 = '-' (ascii value)
	li $s4, 52 # s4 = 52; for comparison
	
	if6: li $t0, 0 # t0 = 0
		bne $a0, $t0, outsideif6 # branch to outsideif6 if win != 0
		for3: bge $t0, $s1, outsideif6 # branch to outsideif6 if i >= rows(6)
			for4: li $t1, 0 # j = 0
				bge $t1, $s2, outsidefor4 # branch to outsidefor4 if j >= cols(9)
				
				#calculate array offset
				mul $t2, $t0, 9 # t2 = i*9
				add $t2, $t2, $t1 # t2 = (i*9+j)
				add $t2, $t2, $s6 # (i*9+j)+board
				
				if7: bne $s6, $s1, else7 # branch to else7 if board[i][j] != '-'
					j outsideif6 # unconditional jump to outsideif6
				else7: 
					addi $s0, $s0, 1 # counter++
					if8: bne $s0, $s4, for4 # branch to for4 if counter != 52

						addi $sp, $sp, -4 # sp moves down
						sw $a0, 0($sp) # push a0 onto stack 
						la $a0, tie # load addr of tie and save/store to a0
						li $v0, 4 # loads 4 into v0, op code for reading a string 
						syscall # print
						lw $a0, 0($sp) # pop a0 from stack
						addi $sp, $sp, 4 # sp moves up 
						
						li $t9, 1 # t9 = 1
						j donediddly # unconditional jump to donediddly

				addi $t1, $t1, 1 # j++
				j for4 # unconditional jump to for4
			outsidefor4: 
				addi $t0, $t0, 1 # i++
				j for3 # unconditional jump to for3
	outsideif6: 
		li $t9, 0 # t9 = 0

	donediddly:
	lw $ra, 0($sp) #pop ra from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s7, 0($sp) #pop s7 from stack  
	addi $sp, $sp, 4 #sp moves up
	lw $s5, 0($sp) #pop s5 from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s4, 0($sp) #pop s4 from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s3, 0($sp) #pop s3 from stack 
	addi $sp, $sp, 4 #sp moves up
	lw $s0, 0($sp) #pop s0 from stack 
	
	#place return value in v0 if function returns anything
	move $v0, $t9 # move t9 into v0 to return
	jr $ra # jump back to caller: main



.data
	m_w: .word 50000 # m_w = 50000
	m_z: .word 60000 # m_z = 60000
	result: .word 0 # result = 0
	y: .word 0 # y = 0
	rows: .word 6 # rows = 6
	cols: .word 9 # cols = 9
	num1: .word 0 # num1 = 0
	num2: .word 0 # num2 = 0
	decideTurn: .word 0 # decideTurn = 0
	compCol: .word 0 # compCol = 0
	playerTurn: .word 0 # playerTurn = 0
	board: .space 54 # space for 54 1-byte chars; board[6][9] needs 54 spaces 

	#display messages
	connect5: .asciiz "Welcome to Connect-5!\n"
	initrand: .asciiz "Enter 2 positive numbers to initialize the random number generator.\n"
	number1: .asciiz "Number 1: "
	number2: .asciiz "Number 2: "
	notok: .asciiz "Invalid value, try again.\n" 
	human: .asciiz "Human player = H\n" 
	computer: .asciiz "Computer player = C\n" 
	coin: .asciiz "Coin toss..."
	you: .asciiz "You go first!"
	notyou: .asciiz "Computer goes first" 
	header: .asciiz "\n   1 2 3 4 5 6 7 \n"
	entercol: .asciiz "Enter a column number(1-7): "
	invalid: .asciiz "Invalid move, select another column: "
	compselect: .asciiz "Computer selected column " 
	winning: .asciiz "You win!\n" 
	lose: .asciiz "You lose...\n" 
	tie: .asciiz "Tie\n"
	newline: .asciiz "\n" 

