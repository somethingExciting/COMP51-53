#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
	int quantity, item, shipping;
	int shoppingCart = 0;
	double price, total, shippingCost, tax;
	double subtotal = 0;
	const double TAX_RATE = 8.75 / 100;
	char name[256];
	char address[256];
	string list;
	
	cout << "Welcome to Belethor's Emporium!" << endl;
	cout << "We sell everything you need to prepare for your journey and battles!" << endl;
	cout << "To begin shopping you must first create an account." << endl;
	cout << "Enter your name: ";
	cin.clear();
	cin.getline(name, 256);
	cout << "Enter your address: ";
	cin.clear();
	cin.getline(address, 256);
	cout << "Thank you for signing up!" << endl;
	cout << endl;
	cout << "Select the number of the item you would like to purchase." << endl;
	do {
		cout << "1: Sword" << endl;
		cout << "2: Armor" << endl;
		cout << "3: Sweet Rolls(2)" << endl;
		cout << "4: Lockpicks(3)" << endl;
		cout << "5: Water Jug" << endl;
		cout << "6: Quit Shopping/Checkout" << endl;
		cin >> item;
		switch (item) {
		case 1:
			cout << "The sword costs $48.00." << endl;
			price = 48.00;
			cout << "How many would you like to purchase? ";
			cin >> quantity;
			subtotal = subtotal + (price * quantity);
			cout << "Your subtotal is $" << subtotal << endl;
			cout << endl;
			shoppingCart = shoppingCart + quantity;
			list = list + "1"; // later uses 1 for sword text display
			break;		
		case 2:
			cout << "The armor costs $64.00." << endl;
			price = 64.00;
			cout << "How many would you like to purchase? ";
			cin >> quantity;
			subtotal = subtotal + (price * quantity);
			cout << "Your subtotal is $" << subtotal << endl;
			cout << endl;
			shoppingCart = shoppingCart + quantity;
			list = list + "2";
			break;
		case 3:
			cout << "The sweet rolls(2) costs $6.00." << endl;
			price = 6.00;
			cout << "How many would you like to purchase? ";
			cin >> quantity;
			subtotal = subtotal + (price * quantity);
			cout << "Your subtotal is $" << subtotal << endl;
			cout << endl;
			shoppingCart = shoppingCart + quantity;
			list = list + "3";
			break;			
		case 4:
			cout << "The lockpicks(3) costs $10.00." << endl;
			price = 10.00;
			cout << "How many would you like to purchase? ";
			cin >> quantity;
			subtotal = subtotal + (price * quantity);
			cout << "Your subtotal is $" << subtotal << endl;
			cout << endl;
			shoppingCart = shoppingCart + quantity;
			list = list + "4";
			break;
		case 5:
			cout << "The water jug costs $4.00" << endl;
			price = 5.00;
			cout << "How many would you like to purchase? ";
			cin >> quantity;
			subtotal = subtotal + (price * quantity);
			cout << "Your subtotal is $" << subtotal << endl;
			cout << endl;
			shoppingCart = shoppingCart + quantity;
			list = list + "5";
			break;
		case 6:
			cout << endl;
			if (shoppingCart == 0) {
				cout << "You cannot checkout with no items, please make a purchase." << endl;
				return 0; 
			}
			else {
				break;
			}
		default:
			cout << "Please enter a valid response." << endl;
			cout << endl;
			break;
		}
	} while (item != 6);
	cout << "Proceeding to checkout..." << endl;
	cout << "Choose your preferred type of shipping: " << endl;
	cout << "1: Standard shipping (5 days)" << endl;
	cout << "2: Two day" << endl;
	cout << "3: Overnight" << endl;
	cin >> shipping;
	switch (shipping) {
	case 1:
		cout << "You have selected standard shipping." << endl;
		shippingCost = 0.00;
		break;
	case 2:
		cout << "You have selected two day shipping." << endl;
		shippingCost = 9.99;
		break;
	case 3:
		cout << "You have selected overnight shipping." << endl;
		shippingCost = 19.99;
		break;
	default:
		cout << "You have selected standard shipping." << endl;
		shippingCost = 0.00;
		break;
	}
	tax = subtotal * TAX_RATE;
	cout << endl;
	cout << "Thank you " << name << " for your purchases today." << endl;
	cout << shoppingCart << " item(s) shipping to: " << endl;
	cout << name << endl << address << endl;
	cout << endl;
	cout << "Your order includes: " << endl;
	for (int i = 0; i < list.length(); i++) {
		if (list[i] == '1') { // finds location of i and assigns text
			cout << "Sword" << setw(20) << setfill(' ') << "$48.00" << endl; // aligns all items
		}
		else if (list[i] == '2') {
			cout << "Armor" << setw(20) << setfill(' ') << "$64.00" << endl;
		}
		else if (list[i] == '3') {
			cout << "Sweet Rolls" << setw(13) << setfill(' ') << "$6.00" <<endl;
		}
		else if (list[i] == '4') {
			cout << "Lockpicks" << setw(16) << setfill(' ') << "$10.00" << endl;
		}
		else {
			cout << "Water Jug" << setw(15) << setfill(' ') << "$4.00" << endl;
		}
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Subtotal " << setprecision(3) << setw(11) << setfill(' ') << "$" << subtotal << endl;
	cout << "Tax " << setprecision(3) << setw(16) << setfill(' ') << "$" << tax << endl;
	cout << "Shipping " << setw(11) << setfill(' ') << "$" << shippingCost << endl;
	total = subtotal + shippingCost + tax;
	cout << "Total " << setw(14) << setfill(' ') << "$" << total << endl;
	cout << endl;
	cout << "Thank you for shopping at Belethor's Emporium! ";
	cout << "Please come again!" << endl;

	system("pause");
}