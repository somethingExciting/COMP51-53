#include <iostream>
#include <ctime>
#include <string>
using namespace std;

int fact(int num);  //function prototype
bool heads(string coin);

int main() {
	srand((unsigned)time(0));
	string value;
	cout << "Heads or tails: ";
	cin >> value;
	cout << heads(value) << endl;
	// cout << fact(5) << endl;
	system("pause");
}

/* int fact(int num) {
	int result = abs(num);
	while (num > 0) {
		result = result * num;
		num--;
	}

	for (int i = 1; i < num; i++) {
		result = result * i;
	}
	return (result)
}
*/

bool heads(string coin) {
	int num = rand() % 100;
	bool result;

	if (num % 2 == 0) {
		if (coin == "heads") {
			result = true;
		}
		else {
			result = false;
		}
	}
	else {
		if (coin == "tails") {
			result = true;
		}
		else {
			result = false;
		}
	}
	return result;
} 