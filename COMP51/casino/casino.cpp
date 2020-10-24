#include <iostream>
#include <ctime>
using namespace std;

void intValidate(int& input) {
	if (cin.fail()) {
		cin.clear();
		cin.ignore(80,'\n');
		input = 0;
	}
}

int gamble(int money) {
	int bet = 0;

	do {
	cout << "How much would you like to bet? $";
	cin >> bet;
	intValidate(bet);
		if (bet <= 0) {
			cout << "Please enter a valid amount." << endl;
		}
		else if (bet > money) {
			cout << "You do not have enough money." << endl;
		}
		else {
		}
	} while (bet <= 0 || bet > money);
	return bet;
}

int randomGamble(int& money) {
	int randomGamble = 0;
	randomGamble = rand() % money + 1;
	cout << "Betting $" << randomGamble << endl;
	return randomGamble;
}

int highLow(int& money) {
	int bet;
	int yourNum, dealerNum;
	char hiLow;
	
	
	cout << "You have $" << money << endl;
	bet = gamble(money);
	yourNum = rand() % 10 + 1;
	dealerNum = rand() % 10 + 1;
	if (yourNum == dealerNum) {
		do {
			yourNum = rand() % 10 + 1;
		} while (yourNum == dealerNum);
	}
	cout << "The number is: " << yourNum << endl;
	cout << "Will the next number be (h)igher or (l)ower than " << yourNum << "? ";
	cin >> hiLow;
	if (hiLow == 'h' || hiLow == 'H') {
		if (yourNum < dealerNum) {
			cout << "Dealer number = " << dealerNum << endl;
			cout << "You win!" << endl;
			money = money + bet;
		}
		else {
			cout << "Dealer number = " << dealerNum << endl;
			cout << "You lose" << endl;
			money = money - bet;
		}
	}
	else {
		if (yourNum > dealerNum) {
			cout << "Dealer number = " << dealerNum << endl;
			cout << "You win!" << endl;
			money = money + bet;
		}
		else {
			cout << "Dealer number = " << dealerNum << endl;
			cout << "You lose" << endl;
			money = money - bet;
		}
	cout << "Thank you for playing High Low." << endl;
	cout << endl;
	}
	return money;
}


int twentyOne(int money) {
	int bet;
	int dealer, card1, card2, newCard, total;
	char agree;

	cout << "You have $" << money << endl;
	bet = gamble(money);
	dealer = rand() % 22 + 1;
	cout << "Your cards are: ";
	card1 = rand() % 10 + 1;
	card2 = rand() % 10 + 1;
	cout << card1 << " " << card2 << endl;
	total = card1 + card2;
	cout << "Total = " << total << endl;
		do {
			cout << "Would you like to hit? ";
			cin >> agree;
			if (agree == 'y' || agree == 'Y') {
				newCard = rand() % 10 + 1;
				cout << "New card = " << newCard << endl;
				total = total + newCard;
				cout << "Total = " << total << endl;
			}
			else {
				if (total > dealer) {
					cout << "Dealer = " << dealer << endl;
					cout << "You win!" << endl;
					money = money + (bet * 2);
					cout << "Thank you for playing 21." << endl;
					cout << endl;
					break;
				}
				else if (total = dealer) {
					cout << "Draw" << endl;
					break;
				}
				else {
					cout << "You lose." << endl;
					money = money - bet;
					cout << "Thank you for playing 21." << endl;
					cout << endl;
				}
			}
		} while (total <= 21);
	return money;
}

int craps(int money) {
	int bet;
	int num1, num2, sum, newNum, newSum;
	char agree;

	cout << "You have $" << money << endl;
	bet = gamble(money);
	cout << "Bet on (p)ass or (n)o pass?" << endl;
	cin >> agree;
	num1 = rand() % 6 + 1;
	num2 = rand() % 6 + 1;
	cout << "You rolled:" << num1 << " " << num2 << endl;
	sum = num1 + num2;
	cout << "Total = " << sum << endl;
	if (sum == 2 || sum == 3 || sum == 12) {
		if (agree == 'p' || agree == 'P') {
			cout << "You lose" << endl;
			money = money - bet;
		}
		else {
			cout << "You win" << endl;
			money = money + bet;
		}
	}
	else if (sum == 7 || sum == 11) {
		if (agree == 'p' || agree == 'P') {
			cout << "You win" << endl;
			money = money + bet;
		}
		else {
			cout << "You lose" << endl;
			money = money - bet;
		}
	}
	else {
		do {
			newNum = rand() % 6 + 1;
			newSum = num1 + newNum;
		} while (newSum != 7);
		cout << "New total = " << newSum << endl;
		if (newSum == 7) {
			if (agree == 'p' || agree == 'P') {
				cout << "You lose" << endl;
				money = money - bet;
			}
			else {
				cout << "You win!" << endl;
				money = money + bet;
			}
		}
		else {
			if (agree == 'p' || agree == 'P') {
				cout << "You win!" << endl;
				money = money + bet;
			}
			else {
				cout << "You lose" << endl;
				money = money - bet;
			}
		}
	}
	cout << "Thank you for playing Craps." << endl;
	cout << endl;
	return money;
}


void slots(int money) {
	int num1, num2, num3;
	int bet;

	cout << "You have $" << money << endl;
	bet = gamble(money);

	num1 = rand() % 10;
	num2 = rand() % 10;
	num3 = rand() % 10;

	cout << num1 << " " << num2 << " " << num3 << endl;

	if (num1 == num2 || num1 == num3 || num2 == num3) {
		cout << "You win!" << endl;
		money = money + (bet * 10);
	}
	else if (num1 == num2 && num1 == num3 && num2 == num3) {
		cout << "Jackpot!!" << endl;
		money = money + (bet * 99);
	}
	else {
		cout << "You lose" << endl;
		money = money - bet;
	}
	cout << "Thank you for playing Slots." << endl;
	cout << endl;
}

int roulette(int money) { // THIS IS FOR EXTRA CREDIT
	int tableNum, betNum1, betNum2;
	int bet;

	cout << "You have $" << money << endl;
	cout << "Choose two numbers between 1 and 12 to bet on: ";
	cin >> betNum1 >> betNum2;
	intValidate(betNum1);
	intValidate(betNum2);
	if (betNum1 > 12 || betNum1 < 1) {
		do {
			cout << "Please enter a valid response." << endl;
			cin >> betNum1;
		} while (betNum1 > 12 || betNum1 < 1);
	}
	else if (betNum2 > 12 || betNum2 < 1) {
		do {
			cout << "Please enter a valid response." << endl;
			cin >> betNum2;
		} while (betNum2 > 12 || betNum2 < 1);
	}
	else {
		bet = gamble(money);
	}
	tableNum = rand() % 12 + 1;
	if (betNum1 == tableNum) {
		cout << "Number was: " << tableNum << endl;
		cout << "Your number: " << betNum1 << endl;
		cout << "You win!" << endl;
		cout << endl;
		money = money + (bet * 50);
	}
	else if (betNum2 == tableNum) {
		cout << "Number was: " << tableNum << endl;
		cout << "Your number: " << betNum2 << endl;
		cout << "You win!" << endl;
		cout << endl;
		money = money + (bet * 50);
	}
	else {
		cout << "Roulette number was: " << tableNum << endl;
		cout << "You lose" << endl;
		cout << endl;
		money = money - bet;
	}
	cout << "Thank you for playing Roulette." << endl;
	cout << endl;
	return money;
}

void slotsTest(int money) {
	int num1, num2, num3;
	int bet;

	cout << "You have $" << money << endl;
	bet = randomGamble(money);

	num1 = rand() % 10;
	num2 = rand() % 10;
	num3 = rand() % 10;

	cout << num1 << " " << num2 << " " << num3 << endl;

	if (num1 == num2 || num1 == num3 || num2 == num3) {
		cout << "You win!" << endl;
		money = money + (bet * 10);
	}
	else if (num1 == num2 && num1 == num3 && num2 == num3) {
		cout << "Jackpot!!" << endl;
		money = money + (bet * 99);
	}
	else {
		cout << "You lose" << endl;
		money = money - bet;
	}
	cout << "Thank you for playing Slots." << endl;
	cout << endl;
}

void testDrive(int& money) {
	int bet = 0, amount;

	cout << "How many times would you like to run through the slots program? ";
	cin >> amount;
	intValidate(amount);
	for (int i = 0; i < amount; i++) {
		slotsTest(money);
	}
}


int main() {
	srand(unsigned(time(0)));
	int choice, balance;

	cout << "Welcome to the Lotus Casino!" << endl;
	balance = rand() % 101 + 100;
	cout << "You have $" << balance << endl;
	do {
		cout << "Please select a game to play: " << endl;
		cout << "1) High-low" << endl;
		cout << "2) 21" << endl;
		cout << "3) Craps" << endl;
		cout << "4) The Slots" << endl;
		cout << "5) Roulette" << endl; //THIS IS FOR EXTRA CREDIT
		cout << "6) Run Test Cases" << endl;
		cout << "7) Leave the Lotus Casino" << endl;
		cin >> choice;
		intValidate(choice);
		switch (choice) {
		case 1:
			balance = highLow(balance);
			break;
		case 2:
			balance = twentyOne(balance);
			break;
		case 3:
			balance = craps(balance);
			break;
		case 4:
			slots(balance);
			break;
		case 5:
			balance = roulette(balance);
			break;
		case 6:
			testDrive(balance);
			break;
		case 7:
			break;
		default:
			cout << "Please enter a valid response." << endl;
			cout << endl;
			continue;
		}
	} while (choice != 7 || balance <= 1);
	cout << "Thank you for playing at the Lotus Casino." << endl;
	cout << "Your total winnings: $" << balance << endl;

	system("pause");
}
