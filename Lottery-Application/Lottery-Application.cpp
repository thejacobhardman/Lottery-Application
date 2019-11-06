// Jacob Hardman
// Comp Sci 1
// Professor Jennifer Bailey
// 11/5/19

#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

int* generateLotto(int& powerball) {
	static int num[5];
	vector<int> alreadyGenerated;

	for (int i = 0; i < 5; i++) {
		bool allUnique = false;
		num[i] = rand() % 9 + 0;

		if (alreadyGenerated.size() > 0) {
			while (!allUnique) {
				if (find(alreadyGenerated.begin(), alreadyGenerated.end(), num[i]) != alreadyGenerated.end()) {
					num[i] = rand() % 9 + 0;
				}
				else {
					allUnique = true;
					alreadyGenerated.push_back(num[i]);
				}
			}
		}
		else {
			alreadyGenerated.push_back(num[i]);
		}
	}

	powerball = rand() % 3 + 1;

	return num;
}

int* getPlayerGuess(int& playerPowerball) {
	static int num[5];
	vector<int> alreadyGuessed;
	int size = sizeof(alreadyGuessed);

	for (int i = 0; i < 5; i++) {
		bool allUnique = false;
		cout << "Number " << i + 1 << ": ";
		cin >> num[i];
		if (alreadyGuessed.size() > 0) {
			while (!allUnique) {
				if (find(alreadyGuessed.begin(), alreadyGuessed.end(), num[i]) != alreadyGuessed.end()) {
					cout << "You've already guessed that number. Please enter a unique number." << endl;
					cout << "Number " << i + 1 << ": ";
					cin >> num[i];
				}
				else {
					allUnique = true;
					alreadyGuessed.push_back(num[i]);
				}
			}
		}
		else {
			alreadyGuessed.push_back(num[i]);
		}
	}

	cout << "Enter your guess for the powerball: ";
	cin >> playerPowerball;

	return num;
}

int* getPlayerGuess(bool isRandom, int& playerPowerball) {
	static int num[5];
	vector<int> alreadyGenerated;

	for (int i = 0; i < 5; i++) {
		bool allUnique = false;
		num[i] = rand() % 9 + 0;

		if (alreadyGenerated.size() > 0) {
			while (!allUnique) {
				if (find(alreadyGenerated.begin(), alreadyGenerated.end(), num[i]) != alreadyGenerated.end()) {
					num[i] = rand() % 9 + 0;
				}
				else {
					allUnique = true;
					alreadyGenerated.push_back(num[i]);
				}
			}
		}
		else {
			alreadyGenerated.push_back(num[i]);
		}
	}

	playerPowerball = rand() % 3 + 1;

	return num;
}

int calculateResults(int *lotto, int *playerGuess, double& winAmount, double& playerWinnings, double& playerBalance, int& powerball, int& playerPowerball) {
	int matches = 0;

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
		winAmount = 1.00;
		break;
	case 2:
		winAmount = 2.00;
		break;
	case 3:
		winAmount = 5.00;
		break;
	case 4:
		winAmount = 10.00;
		break;
	case 5:
		winAmount = 20.00;
		break;
	}

	if (powerball == playerPowerball) {
		winAmount *= 2.00;
	}

	playerBalance += winAmount;
	playerWinnings += winAmount;

	return matches;
}

void displayResults(int* lotto, int* playerGuess, int& powerball, int& playerPowerball, int& matchedNums, double& winAmount) {

	cout << "Lottery Numbers: ";
	for (int i = 0; i < 5; i++) {
		cout << lotto[i] << " ";
	}

	cout << "Powerball: " << powerball << endl;

	cout << "Your Numbers:    ";
	for (int i = 0; i < 5; i++) {
		cout << playerGuess[i] << " ";
	}

	cout << "Powerball: " << playerPowerball << endl;

	cout << endl << "You matched " << matchedNums << " numbers." << endl;
	if (winAmount > 0.00) {
		cout << "You won $" << winAmount << "!!!" << endl;
	}
	else {
		cout << "You didn't win anything." << endl;
	}

	if (powerball == playerPowerball) { cout << "You matched the powerball! Winnings were increased by 2x!" << endl; }
}

void playGame(bool& isRunning, double& playerBalance, double& playerWinnings) {
	bool userConfirm = false;
	string userInput;
	while (userConfirm == false) {
		cout << "Would you like to play the game? (Y/N): ";
		cin >> userInput;

		if (userInput == "Y" || userInput == "y") {
			userConfirm = true;
			playerBalance -= 5.00;
			playerWinnings -= 5.00;
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
	double playerBalance = 10.00, playerWinnings = 0.00, winAmount = 0.00;
	int* lotto, * playerGuess = 0, powerball = 0, playerPowerball = 1;
	string userInput;

	cout << fixed << setprecision(2);
	srand((unsigned)time(NULL));

	cout << "Welcome to Lotto Winners!" << endl;

	bool isRunning = true;
	do {
		lotto = generateLotto(powerball);

		//Checking if the player wants to play again.
		cout << endl << "You currently have $" << playerBalance << endl << "It costs $5.00 to play the game." << endl;
		playGame(isRunning, playerBalance, playerWinnings);
		if (isRunning == false) { break; }

		//Is the player's guess random?
		bool isRandom = false, userConfirm = false;
		while (userConfirm == false) {
			cout << "Would you like to generate your guess randomly? (Y/N): ";
			cin >> userInput;

			if (userInput == "Y" || userInput == "y") {
				isRandom = true;
				userConfirm = true;
				playerGuess = getPlayerGuess(isRandom, playerPowerball); //Generating the player's guess
			}
			else if (userInput == "N" || userInput == "n") {
				userConfirm = true;
				cout << "Enter your 5 lottery number picks: " << endl;
				playerGuess = getPlayerGuess(playerPowerball); //Getting the player's guess
			}
			else {
				cout << "Please enter a valid selection." << endl;
			}
		}
		
		//Calculating the results
		int matchedNums = calculateResults(lotto, playerGuess, winAmount, playerWinnings, playerBalance, powerball, playerPowerball);
		
		//Displaying the results
		displayResults(lotto, playerGuess, powerball, playerPowerball, matchedNums, winAmount);

		//Debug

	} while (isRunning&& playerBalance >= 5.00);

	//Display results
	//The player lost the game.
	if (playerBalance < 5.00) { 
		cout << endl << "You only have $" << playerBalance << ". That's not enough to play the game." << endl; 
		if (playerBalance == 0.00) {
			cout << endl << "You lost all of your money!" << endl << "Better luck next time!" << endl;
		}
		else {
			cout << endl << "You lost $" << (playerBalance - 10.00) * -1 << endl << "Better luck next time!" << endl;
		}
	}
	//The player chose to quit
	else {
		if (playerBalance > 10.00 && playerWinnings > 0.00) {
			cout << endl << "You won $" << playerBalance - 10.00 << "!" << endl << "Congratulations!" << endl;
		}
		else if (playerWinnings < 0.00 && playerBalance > 0.00) {
			cout << endl << "You lost $" << (playerBalance - 10.00) * -1 << endl << "Better luck next time!" << endl;
		}
		else if (playerWinnings == 0.00)
		{
			cout << endl << "You broke even." << endl << "Nice try!" << endl;
		}
	}
}
