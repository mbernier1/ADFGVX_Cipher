#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

bool CheckKeyInput(char key[]);
bool CheckMessageInput(string message);
void PrintSquare(const char square[][6]);
void Sort(char array[]);
void Encryption(int squareChoice, char keyword[], char keyWordSorted[], string plaintext);
void Decryption(int squareChoice, char keyword[], char keyWordSorted[], string plaintext);

const char squareEdges[6] = { 'A', 'D', 'F', 'G', 'V', 'X' };
const char squareOne[6][6] = { { 'p', 'h', '0', 'q', 'g', '6' },
							 {  '4', 'm', 'e', 'a', '1', 'y' },
							 {  'l', '2', 'n', 'o', 'f', 'd' },
							 {  'x', 'k', 'r', '3', 'c', 'v' },
							 {  's', '5', 'z', 'w', '7', 'b' },
							 {  'j', '9', 'u', 't', 'i', '8' } };
const char squareTwo[6][6] = { 'h', 'w', '0', 'p', 'c', 'x',
							 'y', '7', 'r', 'q', '6', 'o',
							 'l', 'b', 'n', 'j', 'g', 'v',
							 '1', 'm', '9', '2', '5', 'z',
							 '8', 'k', 'd', 'a', 't', 'u',
							 'e', '3', 's', 'f', 'i', '4', };
const char squareThree[6][6] = { '9', 'm', 'c', 'r', 'v', '8',
							   'l', 't', '2', 'z', 'x', 'q',
							   'b', 'j', 'h', '4', 'g', '7',
							   'w', 'u', '3', 'd', 'n', 'f',
							   'y', '0', 'o', 's', '5', 'a',
							   'k', 'i', 'e', '1', '6', 'p', };

int main() {

	int menuChoice = 0, squareChoice = 0, pass = 0;
	char keyword[6] = { '\0' }, keywordAlpha[6] = { '\0' };
	string plaintext = { '\0' }, ciphertext = { '\0' };
	bool keyWordCheck = false, plaintextCheck = false, ciphertextCheck = false;

	do {
		cout << "Please choose a menu option. (Enter number)" << endl;
		cout << "1. Encryption" << endl;
		cout << "2. Decryption" << endl;
		cout << "3. Quit Program" << endl;
		cin >> menuChoice;

		switch (menuChoice) {
		case 1: //Encryption
			//Check for polybius square
			do {
				cout << "Polybius Square 1" << endl;
				PrintSquare(squareOne);
				cout << "Polybius Square 2" << endl;
				PrintSquare(squareTwo);
				cout << "Polybius Square 3" << endl;
				PrintSquare(squareThree);
				cout << "Please choose your polybius square from the three options above. ";
				cin >> squareChoice;
			} while (squareChoice < 1 || squareChoice > 3);

			//Check for keyword
			do {
				cout << "Please input your keyword of exactly 6 characters. ";
				cin >> keyword;

				keyWordCheck = CheckKeyInput(keyword);

			} while (keyWordCheck != true);

			//Uppercase keyword letters
			for (int i = 0; i < strlen(keyword); i++) {
				keywordAlpha[i] = toupper(keyword[i]);
			}

			Sort(keywordAlpha);

			do {
				cout << "Please input your message to be encrypted (256 max). ";
				cin.ignore(1000, '\n');
				cin.clear();
				getline(cin, plaintext);

				//Remove spaces in message
				plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), isspace), plaintext.end());

				//Check character length and that it's characters and digits
				plaintextCheck = CheckMessageInput(plaintext);

			} while (plaintextCheck != true);

			Encryption(squareChoice, keyword, keywordAlpha, plaintext);
			break;
		case 2: //Decryption
			//Check for polybius square
			do {
				cout << "Polybius Square 1" << endl;
				PrintSquare(squareOne);
				cout << "Polybius Square 2" << endl;
				PrintSquare(squareTwo);
				cout << "Polybius Square 3" << endl;
				PrintSquare(squareThree);
				cout << "Please choose your polybius square from the three options above. ";
				cin >> squareChoice;
			} while (squareChoice < 1 || squareChoice > 3);

			//Check for keyword
			do {
				cout << "Please input your keyword of exactly 6 characters. ";
				cin >> keyword;

				keyWordCheck = CheckKeyInput(keyword);

			} while (keyWordCheck != true);

			//Uppercase keyword letters
			for (int i = 0; i < strlen(keyword); i++) {
				keywordAlpha[i] = toupper(keyword[i]);
			}

			Sort(keywordAlpha);

			//Check for message to decrypt
			do {
				cout << "Please input your encrypted message to be deciphered (256 max). ";
				cin.ignore(1000, '\n');
				cin.clear();
				getline(cin, ciphertext);

				//Remove spaces in message
				ciphertext.erase(remove_if(ciphertext.begin(), ciphertext.end(), isspace), ciphertext.end());

				//Check character length and that it's characters and digits
				ciphertextCheck = CheckMessageInput(ciphertext);

			} while (ciphertextCheck != true);

			Decryption(squareChoice, keyword, keywordAlpha, ciphertext);
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

void Encryption(int squareChoice, char keyword[], char keyWordSorted[], string plaintext) {

	char square[6][6] = { '\0' };
	char cipherMid[43][6] = { '\0' };

	//Assign the square values based on the users choice
	if (squareChoice == 1) {
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 6; k++) {
				square[i][k] = squareOne[i][k];
			}
		}
	}
	else if (squareChoice == 2) {
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 6; k++) {
				square[i][k] = squareTwo[i][k];
			}
		}
	}
	else if (squareChoice == 3) {
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 6; k++) {
				square[i][k] = squareThree[i][k];
			}
		}
	}

	//Convert the plaintext message to the ADFGVX variants by finding each character in the chosen square
	//and assigning the row then colum as characters in its place. 
	int m = 0, l = 0;
	for (int i = 0; i < plaintext.length(); i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 6; k++) {
				if (plaintext[i] == square[j][k]) {

					if (m < 6) {
						cipherMid[l][m] = squareEdges[j];
						m++;
						cipherMid[l][m] = squareEdges[k];
						m++;
					}
					else if (m == 6) {
						l++;
						m = 0;
						cipherMid[l][m] = squareEdges[j];
						m++;
						cipherMid[l][m] = squareEdges[k];
						m++;
					}
				}
			}
		}
	}

	// EXAMPLE: Typed in: defend the east wall of the castle
	// Converts to: defendtheeastwallofthecastle
	// Above function changes it to this: FX DF FV DF FF FX  XG AD DF  DF DG VA XG  VG DG FA FA  FG FV  XG AD DF  GV DG VA XG FA DF

	// Array must be divisable by 6 so we add G's to fill in the empty spots.						
	int len = strlen(*cipherMid);
	int lenMod = 6 - strlen(*cipherMid) % 6;
	int rowPos = (len - strlen(*cipherMid) % 6) / 6;
	if (strlen(*cipherMid) % 6 != 0) {
		for (int i = (strlen(*cipherMid) % 6); i < 6; i++) {
			if (i < 6) {
				cipherMid[rowPos][i] = 'G';
			}
		}
	}

	//Capitalize the keyword.
	for (int i = 0; i < strlen(keyword); i++) {
		keyword[i] = toupper(keyword[i]);
	}

	//Makes a temp 2D array of cipher text in column format
	char temp[43][6] = { '/0' };

	for (int i = 0; i < 6; i++)
	{
		for (int k = 0; k < 6; k++)
		{
			temp[i][k] = cipherMid[i][k];
		}
	}

	//Swaps the columns that correspond to the alphabetized keyword 
	for (int i = 0; i < 6; i++)
	{
		for (int k = 0; k < 6; k++)
		{
			if (keyword[i] == keyWordSorted[k])
			{
				for (int j = 0; j < 43; j++)
				{
					swap(cipherMid[j][i], temp[j][k]);
				}
			}
		}
	}

	//Prints out ciphertext
	cout << '\n' << "Your ciphertext message is: ";
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < plaintext.length(); j++) {
			if (temp[j][i] != NULL) {
				cout << temp[j][i];
			}
		}
	}
	cout << endl << endl;
}

void Decryption(int squareChoice, char keyword[], char keyWordSorted[], string ciphertext) {

	char square[6][6] = { '\0' };
	char cipherMid[43][6] = { '\0' };

	//Assign the square values based on the users choice
	if (squareChoice == 1) {
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 6; k++) {
				square[i][k] = squareOne[i][k];
			}
		}
	}
	else if (squareChoice == 2) {
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 6; k++) {
				square[i][k] = squareTwo[i][k];
			}
		}
	}
	else if (squareChoice == 3) {
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 6; k++) {
				square[i][k] = squareThree[i][k];
			}
		}
	}

	//Assigns the ciphertext input to temp as a 2d array
	int len = ciphertext.length();
	int rows = ciphertext.length() / 6;
	int j = 0;
	char temp[43][6] = { '/0' };

	for (int i = 0; i < 6; i++)
	{
		for (int k = 0; k < rows; k++)
		{
			temp[k][i] = ciphertext[j];
			j++;
		}
	}

	//Capitalize the keyword.
	for (int i = 0; i < strlen(keyword); i++) {
		keyword[i] = toupper(keyword[i]);
	}

	//Swaps the columns that correspond to the alphabetized keyword
	for (int i = 0; i < 6; i++)
	{
		for (int k = 0; k < 6; k++)
		{
			if (keyWordSorted[i] == keyword[k])
			{
				for (int j = 0; j < 43; j++)
				{
					swap(temp[j][i], cipherMid[j][k]);
				}
			}
		}
	}

	//EXAMPLE: Input was FFDVDFADFGXFGFGAVFAFFDXDXFFDVDFFDGGAGVGGVXFAGGDGAGDFADVFXGXG
	//keyword was German
	//Output not using alphabatized keyword is FXFFVDFFDFXFDGXDFAVFDGADDGXGGVFAFAGFAVFGDXDFDVGGFAVGAXGFDGGG
	//After swap FXDFFVDFFFFXXGADDFDFDGVAXGVGDGFAFAFGFVXGADDFGVDGVAXGFADFGGGG
	cout << endl;
	cout << "Your plaintext message is: ";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 6; k++) {
				if (cipherMid[i][j] == squareEdges[k]) {
					for (int l = 0; l < 6; l++) {
						if (cipherMid[i][j + 1] == squareEdges[l]) {
							//Prints out plaintext
							cout << square[k][l];
							k = 6;
						}
					}
					j++;
				}
			}
		}
	}
	cout << endl << endl;
}

void PrintSquare(const char square[][6]) {

	cout << "   ";
	for (int i = 0; i < 6; i++) {
		cout << squareEdges[i] << "  ";
	}
	cout << endl;

	for (int h = 0; h < 6; h++) {
		cout << squareEdges[h] << "  ";
		for (int k = 0; k < 6; k++) {
			cout << square[h][k] << "  ";
		}
		cout << endl;
	}
}

bool CheckKeyInput(char key[]) {

	bool check = true;

	//Check for negatives
	for (int i = 0; i < strlen(key); i++) {
		if (key[i] < 0) {
			check = false;
		}
	}
	//Check for char length
	if (check == true) {
		if (strlen(key) != 6) {
			check = false;
		}
	}
	//Check for letters only
	if (check == true) {
		for (int i = 0; i < strlen(key); i++) {
			int uppercaseWord = toupper(key[i]);
			if (uppercaseWord < 'A' || uppercaseWord > 'Z') {
				check = false;
			}
		}
	}

	return check;
}

bool CheckMessageInput(string message) {

	bool check = true;

	//Check for char length
	if (check == true) {
		if (message.length() > 256) {
			check = false;
		}
	}
	//Check for characters and digits only
	for (int i = 0; i < message.length(); i++) {
		if (isalpha(message[i]) || isdigit(message[i])) {
			check = true;
		}
		else
			check = false;
	}
	return check;
}

void Sort(char array[]) {
	int pass = 0;

	for (int i = 0; i < 6; i++) {
		bool sorted = true;
		for (int j = 0; j < 6 - pass - 1; j++) {
			if (array[j] > array[j + 1]) {
				sorted = false;
				swap(array[j], array[j + 1]);
			}
		}
		pass++;
	}
}
