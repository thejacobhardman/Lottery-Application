// Jacob Hardman
// Comp Sci 1
// Professor Jennifer Bailey
// 11/5/19

#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>
#include <math.h>

using namespace std;

int* generateLotto() {
	static int num[5];

	srand((unsigned)time(NULL));

	for (int i = 0; i < 5; i++) {
		num[i] = rand() % 9 + 0;
	}

	return num;
}

int* getPlayerGuess() {
	static int num[5];

	for (int i = 0; i < 5; i++) {
		cout << "Number " << i + 1 << ": ";
		cin >> num[i];
	}

	return num;
}

int calculateResults(int *lotto, int *playerGuess, double& playerWinnings, double& playerBalance) {
	static int matches = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (playerGuess[i] == lotto[j]) 
			{
				matches += 1; 
				break;
			}
		}
	}

	switch (matches)
	{
	case 1:
		playerWinnings = 1.00;
		playerBalance += playerWinnings;
		break;
	case 2:
		playerWinnings = 2.00;
		playerBalance += playerWinnings;
		break;
	case 3:
		playerWinnings = 5.00;
		playerBalance += playerWinnings;
		break;
	case 4:
		playerWinnings = 10.00;
		playerBalance += playerWinnings;
		break;
	case 5:
		playerWinnings = 20.00;
		playerBalance += playerWinnings;
		break;
	default:
		playerWinnings = 0.00;
		break;
	}

	return matches;
}

void displayResults(int* lotto, int* playerGuess, int& matchedNums, double& playerWinnings) {

	cout << "Lottery Numbers: " << endl;
	for (int i = 0; i < 5; i++) {
		cout << lotto[i] << " ";
	}

	cout << endl;

	cout << "Your Numbers: " << endl;
	for (int i = 0; i < 5; i++) {
		cout << playerGuess[i] << " ";
	}

	cout << endl << "You matched " << matchedNums << " numbers." << endl;
	if (playerWinnings > 0.00) {
		cout << "You won $" << playerWinnings << "!!!" << endl;
	}
	else {
		cout << "You didn't win anything." << endl;
	}
}

void playGame(bool& isRunning, double& playerBalance) {
	bool userConfirm = false;
	string userInput;
	while (userConfirm == false) {
		cout << "Would you like to play the game? (Y/N): ";
		cin >> userInput;

		if (userInput == "Y" || userInput == "y") {
			userConfirm = true;
			playerBalance -= 5.00;
			cout << endl;
		}
		else if (userInput == "N" || userInput == "n") {
			userConfirm = true;
			isRunning = false;
		}
		else {
			cout << "Please enter a valid selection." << endl;
		}
	}
}

int main()
{
	//Init Start Params
	double playerBalance = 10.00, playerWinnings = 0.00;
	int *lotto, *playerGuess;

	cout << fixed << setprecision(2);
	cout << "Welcome to Lotto Winners!" << endl;

	bool isRunning = true, didPlayerWin;
	do {
		lotto = generateLotto();

		//Checking if the player wants to play again.
		cout << endl << "You currently have $" << playerBalance << endl << "It costs $5.00 to play the game." << endl;
		playGame(isRunning, playerBalance);
		if (isRunning == false) { break; }

		//Getting the player's guess
		cout << "Enter your 5 lottery number picks: " << endl;
		playerGuess = getPlayerGuess();

		int matchedNums = calculateResults(lotto, playerGuess, playerWinnings, playerBalance);
		
		displayResults(lotto, playerGuess, matchedNums, playerWinnings);

	} while (isRunning&& playerBalance >= 0.00);

	//Display results
 	if (playerWinnings > 0.00) {
		cout << endl << "You won $" << playerBalance - 10.00 << "!" << endl << "Congratulations!" << endl;
	}
	else if (playerWinnings < 0.00) {
		cout << endl << "You lost all of your money!" << endl << "Better luck next time!" << endl;
	}
	else {
		cout << endl << "You broke even." << endl << "Nice try!" << endl;
	}
}
