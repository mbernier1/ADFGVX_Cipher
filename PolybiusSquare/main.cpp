#include <iostream>
using namespace std;


int main() {

	int menuChoice, squareChoice;
	char keyword[6] = { '/0' };

	//Generate 3 Polybius Squares (Maybe) Display them during the choice question.
	
	do {
		cout << "Please choose a menu option. (Enter number)" << endl;
		cout << "1. Encryption" << endl;
		cout << "2. Decryption" << endl;
		cout << "3. Quit Program" << endl;
		cin >> menuChoice;

		switch(menuChoice){
		case 1:
			cout << "Please choose your polybius square from the three options below." << endl;
			do {
				cout << "Polybius Square 1" << endl;
				//Display square 1
				cout << "Polybius Square 2" << endl;
				//Display square 2
				cout << "Polybius Square 3" << endl;
				//Display square 3
				cin >> squareChoice;

				switch (squareChoice) {
				case 1:
					
					break;
				case 2:
					
					break;
				case 3:
					
					break;
				default:
					cout << "Please make a valid polybius square choice. \n" << endl;
				}
			} while (squareChoice < 1 || squareChoice > 3);
			
			cout << "Please input your polybius square keyword. ";
			cin >> keyword;
			//Take the polybius square choice and modify it to contain the keyword.


			//Encryption();
			break;
		case 2:
			//Decryption();
			break;
		case 3:
			cout << "Exiting" << endl;
			break;
		default:
			cout << "Please choose a valid menu option. \n" << endl;
		}


	} while (menuChoice != 3);

	return 0;
}