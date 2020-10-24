#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
	string line, inName, outName;
	bool orderedList = false;
	ifstream inStream;
	ofstream outStream;
	do {
		cout << "Which file would you like to open? " << endl; //enter webifyinput.txt
		getline(cin, inName);
		inStream.open(inName);
		if (inStream.fail())
		{
			cout << "Enter a valid file name." << endl;
		}
	} while (inStream.fail());
	cout << "What file would you like to output into? " << endl; //enter webifyoutput.html
	getline(cin, outName);
	outStream.open(outName);
	if (outStream.fail())
	{
		cout << "Enter a valid file name." << endl;
		system("pause");
		exit(1);
	}
	outStream << "<html>" << endl;
	outStream << "<head>" << endl;
	outStream << "<title>" << inName << "converted to HTML" << "</title>" << endl;
	outStream << "</head>" << endl;
	outStream << "<body>" << endl;
	while (getline(inStream, line)) {
		if (line[0] != '0' && orderedList == true)
		{
			outStream << "</ol>";
			orderedList = false;
		}
		switch (line[0]) {
		case '1':
			line.replace(0, 2, "");
			line.insert(0, "<h1>");
			line.append("</h1>");
			break;
		case '2':
			line.replace(0, 2, "");
			line.insert(0, "<h2>");
			line.append("</h2>");
			break;
		case '3':
			line.replace(0, 2, "");
			line.insert(0, "<h3>");
			line.append("</h3>");
			break;
		case '4':
			line.replace(0, 2, "");
			line.insert(0, "<h4>");
			line.append("</h4>");
			break;
		case '5':
			line.replace(0, 2, "");
			line.insert(0, "<h5>");
			line.append("</h5>");
			break;
		case '-':
			outStream << "<ul>" << endl;
			while (line[0] == '-') {
				line.replace(0, 2, "");
				line.insert(0, "<li>");
				line.append("</li>");
				outStream << line << endl;
				getline(inStream, line);
			}
			outStream << "</ul>";
			break;
		case '0':
			if(orderedList == false) {
				outStream << "<ol>" << endl;
				orderedList = true;
			}
			line.replace(0, 2, "");
			line.insert(0, "<li>");
			line.append("</li>");
			break;
		case '6':
			line.replace(0, 2, "");
			line.insert(0, "<h6>");
			line.append("</h6>");
			break;
		default:
			break;
		}
		if (line.at(line.length()-1)== '.') {
				line.append("<br/>");
			}
		if (line.find("www") != string::npos) { //THIS IS FOR EXTRA CREDIT: ADDING HYPERLINK
			line.insert(line.find("www"), "<a href= \"http://");
			line.insert(line.find("com") + 3, "\">www.w3schools.com</a>");
		}
		outStream << line << endl;
	}


	system("pause");
}