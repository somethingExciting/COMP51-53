#include <iostream>
#include <string>
using namespace std;

struct fencer {
	string name, weapon;
	int score1, score2;
};

void getTeam(fencer team[]) {
	for (int i = 0; i < 5; i++) {
		cout << "Info for fencer #" << i << endl;
		cout << "Please enter the fencer's name: ";
		cin >> team[i].name;
		do {
			cout << "Please enter the fencer's weapon: ";
			cin >> team[i].weapon;
		} while (team[i].weapon != "Foil" && team[i].weapon != "Saber" && team[i].weapon != "Epee");
		cout << "Please enter the fencer's scores: ";
		cin >> team[i].score1 >> team[i].score2;
	}
	cout << endl;
}

void printTeam(fencer team[]) {
	for (int i = 0; i < 5; i++) {
		cout << team[i].name << ", " << team[i].weapon << ": ";
		if (team[i].score1 > team[i].score2) {
			cout << team[i].score1;
		}
		else {
			cout << team[i].score2;
		}
		cout << endl;
	}
	cout << endl;
}

void weaponChoice(fencer team[]) {
	string findWeapon;
	bool found = false;

	cout << "Please select a weapon: ";
	cin >> findWeapon;
	for (int i = 0; i < 5; i++) {
		if (findWeapon == team[i].weapon) {
			cout << team[i].name << endl;
			found = true;
		}
	}
	if (found == false) {
		cout << "Nobody has this weapon." << endl;
	}
	cout << endl;
}


int main() {
	fencer team[5];
	
	getTeam(team);
	printTeam(team);
	weaponChoice(team);

	system("pause");
}