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
							 {  '4', 'm', 'e', 'a', 'l', 'y' },
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

	//Swap new arrays around to be in alphabetical ordered Keyword
	//Print out each new area position by position with spaces between each 2 characters
	char square[6][6] = { '\0' };
	char cipherMid[43][6] = { '\0' };
	cout << plaintext << endl;
	for (int i = 0; i < plaintext.length(); i++) {
		for (int j = 0; j < 6; j++) {
			cipherMid[i][j] = NULL;
		}
	}

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
	int m = 0, l = 0;
	for (int i = 0; i < plaintext.length(); i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 6; k++) {
				if (plaintext[i] == square[j][k]) {
					//cout << squareEdges[j] << squareEdges[k] << " ";

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

	char temp1[][6] = { '\0' };
	if (strlen(*cipherMid) % 6 != 0)
	{
		// add letters to end of array
		int len = (strlen(*cipherMid) + 6 -1) / 6;
		temp1[len + 1][6] = 'X';
	}
	
	
	for (int i = 0; i < strlen(keyword); i++) {
		keyword[i] = toupper(keyword[i]);
	}

	// makes a temp 2D array of cipher text in column format
	char temp[43][6]= { '/0' };
	
	for (int i = 0; i < 6; i++)
	{
		for (int k = 0; k < 6; k++)
		{
			temp[i][k] = cipherMid[i][k];
		}
	}

	// swaps the columns that correspond to the alphabetized keyword 
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
	cout << '\n' << "Your ciphertext message is: ";
	// prints out ciphertext
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < plaintext.length(); j++) {
			if (temp[j][i] != NULL)
			{
				cout << temp[j][i];
			} 
		}
	}
	cout << endl << endl;
}

void Decryption(int squareChoice, char keyword[], char keyWordSorted[], string ciphertext) {
	char square[6][6] = { '\0' };
	char cipherMid[43][6] = { '\0' };

	for (int i = 0; i < 43; i++) {
		for (int j = 0; j < 6; j++) {
			cipherMid[i][j] = ' ';
		}
	}

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
	// take in message
	// put message in square by column
	// 
	/*int m = 0, l = 0;
	for (int i = 0; i < ciphertext.length(); i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 6; k++) {
				if (plaintext[i] == square[j][k]) {
					//cout << squareEdges[j] << squareEdges[k] << " ";

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
	}*/

	for (int i = 0; i < strlen(keyword); i++) {
		keyword[i] = toupper(keyword[i]);
	}

	// makes a temp 2D array of cipher text in column format
	char temp[43][6] = { '/0' };

	for (int i = 0; i < 6; i++)
	{
		for (int k = 0; k < 6; k++)
		{
			temp[i][k] = cipherMid[i][k];
		}
	}

	// swaps the columns that correspond to the alphabetized keyword 
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
	cout << '\n' << "Your plaintext message is: ";
	// prints out plaintext
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 43; j++) {
			if (temp[j][i] != ' ')
			{
				cout << temp[j][i];
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
	//array[6] = '\0';
}
