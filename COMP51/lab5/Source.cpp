#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void print(string ) {
	for (int i = 0; i < s; i++) { 
		cout << woodchuck.at(i) << " ";
	}
	cout << endl << endl;
}

int main() {
	ifstream inStream;
	string word;
	string findWord, replaceWord;
	vector<string> woodchuck;
	int size = 0, i = 0;

	inStream.open("Lab5.txt");
	if (inStream.fail()) {
		cout << "Error opening file." << endl;
	}
	cout << "Original text:" << endl;
	while (inStream >> word) {
		woodchuck.push_back(word);
		size++;
	}
	print(size);
	cout << "Enter a word to find: ";
	cin >> findWord;
	cout << "Enter a word to replace it with: ";
	cin >> replaceWord;
	vector<string>::iterator p;
	for (p = woodchuck.begin(); p != woodchuck.end(); p++) {
		if (*p == findWord) {
			*p = replaceWord;
			//cout << replaceWord;
		}
		cout << woodchuck.at(i) << " ";
	}
	

	system("pause");
}