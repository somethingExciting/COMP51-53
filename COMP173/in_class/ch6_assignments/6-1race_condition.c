#include <stdio.h>
#include <pthread.h>

//pthreads only work for 2 processes, so if there was another couple
//trying to withdraw/deposit, using pthreads would not work

//deposit(100) /OR/ counter++
void deposit() {
	flag[i] = TRUE; //process is ready
	turn = j;
	while (flag[j] && turn == j); 
	register1 = balance
	register1 = register1 + 100
	balance = register1
	flag[i] = FALSE; 
}

//withdraw(50) /OR/ counter--
void withdraw() {
	flag[j] = TRUE;
	turn = i;
	while (flag[i] && turn == i); 
	register2 = balance
	register2 = register2 - 50
	balance = register2
	flag[j] = FALSE; //process is not ready 
}

int main() {
	//interleaving with balance=100 initially
	S0: producer execute register1 = balance {register1 = 5}
	S1: producer execute register1 = register1 + 100 {register1 = 6}
	S2: consumer execute register2 = counter {register2 = 5}
	S3: consumer execute register2 = register2 - 1 {register2 = 4}
	S4: producer execute counter = register1 {counter = 6 }
	S5: consumer execute counter = register2 {counter = 4}

	S0: producer execute register1 = counter {register1 = 5}
	S1: consumer execute register2 = counter {register2 = 5}
	S2: producer execute register1 = register1 + 1 {register1 = 6}
	S3: consumer execute register2 = register2 - 1 {register2 = 4}
	S4: consumer execute counter = register2 {counter = 4}
	S5: producer execute counter = register1 {counter = 6}

	return 0;
}

