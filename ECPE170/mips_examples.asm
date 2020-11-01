NOTES:
#Branching Instructions
-beq - branch on equal to 
-bne - branch on not equal to
-bgt - branch on greater than
-bge - branch on greater than or equal to
-blt - branch on less than
-ble - branch on less than or equal to 
#j - unconditional jump (if the conditions are false,then jump to another label)


#MIPS
 -load - from registers to cpu
 -store - from cpu to registers
 -lw <destination register>, memory_var
 -lb <destination register>, memory_var
 -sb <source register>, memory_var
-acessing arrays
# base offset (add n number of bytes to the base in order to retrieve data from an array 
#  element)
# pointer arithmetic
# example 
#	Write a C for loop to print the values of a 1-D array of size N using:
#	 1. indexed addressing
#	 2. pointer arithmetic

#	int array[n]
#	for(int i=0;i<n;i++)
#	{
#	  //method 1: printf("\n%d", array[i])
#	  //method 2: printf("\n%d", *(array+i))
#	  //method 3: printf("\n%d", *array)
#	    array++;
#	}


#C vs MIPS base/offset
# base[offset] //C
# offset(<register storing base addr>) //MIPS
# example 1:
	array[12] = h + array[8]
	lw  $t1, 32($s3) #load array[8] into $t1, offset=32
	add $t1, $t1, $s2 #$t1=h+array[8]
	sw $t1, 48($s3) #array[12]=h+array[8]
# example 2:
	g = h + array[i];
	#calculate the correct offset=4i
	add $s4, $s4, $s4 #2i
	add $s4, $s4, $s4 #4i
	add $t1, $s3, $s4 #t1= base addr + offset
	lw $t2, 0($t1) #$t2 = *(base addr + offset)
	add $s1, $t2, $s2 #h+array[i]
#load addr. - la <destination register to store the addr>, arrayname
 +      array[0]   [1]   [2]
  value    5        6     4
  add     30       34    38
la $s0, array #$s0 = 30  -> correct
lw $s0, array #$s0 = 5


#Converting MIPS to C
#MIPS
 addi $t0, $zero, 0 #t0=0
 addi $t1, $zero, 2 #t1=2
 bge $t0, $t1, <label to addr 24>
 addi $t0, $t0, 1
 j <label to addr 12>
 li $v0, 10
 syscall 

-C
 i=0;
 j=2;
 for(i=0; i<2; i++) {
  
 }

#use 'a' registers to store function arguments
#use jal <function label> to save the return addr of the function into $ra
#saves return values in 'v' registers 
#use jr <register name> #usually $ra; to return to the next step after the jal call
#when calling a function, backup all registers





EXAMPLES:
1. Convert the C snippet to assembly.
g = 15;
h = 20;
i = 5;
j= 18;
f = (g + h) – (i+j);
Assume Map:
$s0 = g
$s1 = h
$s2 = i
$s3 = j
$s4 = f

addi $s0, $zero, 15 #g=15
addi $s1, $zero, 20 #h=20
addi $s2, $zero, 5 #i=5
addi $s3, $zero, 18 #j=18
add $t0, $s0, $s1 #t0=g+h
add $t1, $s3, $s4 #t1=i+j
sub $s4, $t0, $t1 #f=(g+h)-(i+j)



2. Convert the C snippet to assembly.
if( (A>=B)|| A>6)
  C=A;
else
  C=B-A;
Assume Map:
$s0 = C
$s1 = A
$s2 = B

if: bge $s1, $s2, CeqA #branch to C=A if A>=B
addi $t0, $zero, 6 #t0=6
bgt $s1, $t0, CeqA #A>6
j else #unconditional jump
CeqA: addi $s0, $zero, $s1 #C=0+A -> C=A
j outsideelse
else: sub $s0, $s2, $s1 #C=B-A
outsideelse: ...



3. Convert the C snippet to assembly.
sum=0;
for( i=0; i<10; i++ )
{
  sum+=i;
}
Assume Map:
$s0 = sum
$t0 = i

addi $s0, $zero, 0 #sum=0
addi $t0, $zero, 0 #i=0
addi $t1, $zero, 10 #used for checking
for: bge $t0, $t1, outsidefor #i>=10?
add $s0, $s0, $t0 #sum+=i
add $t0, $t0, 1 #i++
j for #jump to for
outsidefor: ...



4. Convert the C snippet to assembly.
sum=0;
for(i=0;i<10;i++)
{
    j=i;
    while(j<2*i)
    {
       sum=sum+j;
       j++; 
    }
}
Assume Map:
$s0 = sum
$s1 = i
$s2 = j

addi $s0, $zero, 0 #sum=0
addi $s1, $zero, 0 #i=0
addi $t0, $zero, 10 #used for checking
for: bge $s1, $t0, outsidefor #i>=10?
add $s0, $s0, $s1 #sum+=i
addi $s2, $s2, $s1 #j=i
add $t1, $s1, $s1 #t1=2*i
while: bge $s2, $t1, outsidewhile #j>=2*i?
add $s0, $s0, $s2 #sum+=j
add $s2, $s2, 1 #j++
j while #jump to while
outsidewhile:
add $s1, $s1, 1 #i++
j for #jump to for
outsidefor: ...



5. Convert the C snippet to assembly:
while(1)
{
   sum=sum+i;
   i--;
   if(i<=0)
      break;
   else
      continue;
}
Assume Map:
$s0 = sum
$s1 =i

addi $t0, $zero, 1 #t0=1
addi $t1, $zero, 1 #t1=1
addi $t2, $zero, 0 #t2=0
addi $s0, $zero, 0 #sum=0
addi $s1, $zero, 3 #i=3
while: beq $t0, $t1, outsidewhile
add $s0, $s0, $s1 #sum+=i
sub $s1, $s1, $t0 #i--
if: bge $s1, $t2, else
j outsidewhile
else: j while
outsidewhile: ...



-example that encapsulates everything
	Write a complete MIPS program which implements the C code below.  Test your program
	 in QtSPIM.

	//memory variable
	int array[7];
	int main()
	{
  	  int i=0; //use register
  	  array[0]=5;
	  array[1]=4;
  	  for(i=2;i<7;i++)
    	    array[i] = array[i-2] + array[i-1];
	}

	main:
	#register map
	#s0 will always hold the base addr (won't change)
	#t0 will be used for i
	#t1 will be for array[i-1]
	#t2 will be for array[i-2]
	addi $t0, $zero, 0 #i = 0
	addi $t3, $zero, 5 #t3 = 5
	la $s0, array #s0 is the base addr
	sw $t3, 0($s0) #array[0]=5
	addi $t3, $zero, 4 #t3 = 4
	sw $t3, 4($s0) #array[1]=4
	addi $t0, $zero, 2 #i=2
	addi $t7, $zero, 7 #t7=7
	for: bge $t0, $t7, exitfor
	 #array[i-1]
	 addi $t4, $t0, -1 #t4=i-1
	 add $t4, $t4, $t4 #t4=2(i-1)
	 add $t4, $t4, $t4 #t4=4(i-1)
	 add $t4, $s0, $t4 #array + 4(i-1)
	 lw $t1, 0($t4) #t1=*(array + 4(i-1))
	 #array[i-2]
	 addi $t4, $t0, -2 #i-2
	 add $t4, $t4, $t4 #2(i-2)
 	 add $t4, $t4, $t4 #4(i-2)
	 add $t4, $s0, $t4 #t4=array+4(i-2)
	 lw $t2, 0($t4) #t2=x(array + 4(i-2))
	 add $t5, $t1, $t2 #t5=array[i-1]+array[i-2]
	 #array[i]
	 addi $t4, $t0, 0 #t4=i
	 add $t4, $t4, $t4 #2i
	 add $t4, $t4, $t4 #4i
	 add $t4, $s0, $t4 #array+4i 
	 sw $t5, 0($t4) #array[i]=array[i-1] + array[i-2]
	 addi $t0, $t0, 1 #i+1
	 j for 
	 exitfor:
	 li $v0, 10
	 syscall #exit program 
	-data
	array: .space 28 #space for 7 4-byte ints



1. Covert this code to MIPS:
#include <stdio.h>
int function(int a);
int main() {
  int x=5;
  int y;
  y = function(x);
  printf(“y:%d”,y);
  return 0;
}

int function(int a) {
  return 3*a+5;
}

Assumptions:
-Place arguments in $a0-$a3
-Place return values in $v0-$v1
-Return address saved automatically in $ra
-Ignore the stack for this example. (Thus, the function will destroy registers used by 
  calling function)

 .globl main
 .text
 main: 
  #register map
  addi $a0, $zero, 5  #x=5, used as an argument
  jal func  #jump to func  
  addi $s0, $v0, 0  #y= return value
  #print "y:"
  li $v0, 4  #system call code to print string
  la $a0, msg
  syscall
  #print integer
  li $v0, 1
  addi $a0, $s0, 0 #value to be printed = y
  syscall
  li $v0, 10 #exit main
  syscall


 func: addi $t0, $zero, 3 #t0=3
 mul $t1, $t0, $a0 #t1=3*a
 addi $t0, $zero, 5 #t0=5
 add $v0, $t1, $t0 #v0=3*a+5
 jr $ra #return back


 .data 
  msg: .asciiz "y:"


2. Using $sp, write the set of commands for pushing and popping a register value (say $s0)
#push operation
addi $sp, $sp, -4 #sp moves down
sw $s0, 0($sp) #push a value(s0) to stack
#pop 
lw $s0, 0($sp)  #read value first 
addi $sp, $sp, 4 #sp moves up



3. Implement the following code in MIPS:
int array[] = {2, 3, 4, 5, 6};

int main() {
  int num, position;
  scanf(“%d”,&num);
  position = search(array, num, 5);
  printf(“\n The position is: %d”,position);
}

int search(int *array, int num, int size) {
  int position = -1;
  for(int i=0;i<size;i++)
    if(array[i]==num) {
      position=i;
      break;
    }
  return position;
}

Register map:
$s0: num
$s1: position
$a0: array address
$a1: num
$a2: size
$v0: return value


.globl main 
.text
main: 
li $v0, 5 #input to num 
syscall 
move $s0, $v0 #num=read value
#save any t registers in use. None in use
#save any a registers in use. None in use 
la $a0, array #a0 is the base addr of array 
move $a1, $s0 #arg2=num 
li $a2, $5 #arg3=5
jal search #jump to function Search
move $s1, $v0 #move return value into s1
#print msg
li $v0, 4 #code for string
la $a0, msg1  #addr of msg1
syscall 
li $v0, 1 #code for int 
move $a0, $s1 #move position to a0 for printing
syscall
li $v0, 10 #exit main 
syscall

search: #save s registers used by its caller. s0 in use 
#push s0 to stack
addi $sp, $sp, -4 #sp moves down
sw $s0, 0($sp) #push s0 onto stack
#save ra onto the stack
addi $sp, $sp, -4 #sp moves down
sw $ra, 0($sp) #push previous ra onto stack
#s0 for position
li $s0, -1 #position=-1
#t0 for i
li $t0, 0 #i=0
for: bge $t0, $a2, exitfor #branch to exitfor if i>= size(arg2)
if: add $t1, $t0, $t0 #2i
add $t1, $t1, $t1 #4i (offset)
add $t1, $a0, $t1 #&array[i]
lw $t2, 0($t1) #t2=array[i]
bne $t2, $a1, outsideif #branch to outsideif if array[i]!=0
move $s0, $t0 #position=i
j exitfor #break
#if block ends here
addi $t0, $t0, 1 #i++
j for #unconditional jump to for
outsideif:
exitfor:
#function should place return value in v0
move $v0, $s0 #place position as return value
#pop whatever was pushed
lw $ra 0($sp) #read ra
addi $sp, $sp, 4 #sp moves up
lw $s0, 0($sp) #read s0
addi $sp, $sp, 4 #sp moves up 
jr ra #return to main after function was called

.data
array .word 2, 3, 4, 5, 6 #initialize array values
num: .word 0 #num=0
position: .word 0 #position=0
msg1: .asciiz "\n The position is: " #message 

