#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

enum enGameChoice { stone = 1, papper = 2, scissors = 3 };
enum enWinner { player = 1, computer = 2, draw = 3 };

struct stRoundInfo {
	short RoundNumber;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;
};

struct stGameResults {
	short GameRounds;
	short PlayerWinTimes;
	short ComputerWinTimes;
	short DrawTimes;
	enWinner Winner;
	string WinnerName;
};

int RandomNumber(int from, int to) {
	int randomNum = rand() % (to - from + 1) + from;
	return randomNum;
}

int HowManyRounds() {
	int num;
	do {
		cout << "Enter Number of Rounds between 1 to 10 " << endl;
		cin >> num;
	} while (num < 1 || num > 10);
	return num;
}

void restScreen() {
	system("cls");
	system("color 0F");
}

void setWinnerScreenColors(enWinner winner) {
	if (winner == enWinner::player) {
		system("color 2F");
	}
	else if (winner == enWinner::computer) {
		system("color 4F");
		cout << "\a";
	}
	else {
		system("color 6F");
	}
}

string Tabs(int numberTabs) {
	string t = "";
	for (int i = 1; i <= numberTabs; i++) {
		t = t + "\t";
	}
	return t;
}

enGameChoice ChoiceOfPlayer() {
	short choice;
	do {
		cout << "Choose From Stone[1] | Papper[2] | Scissors[3] " << endl;
		cin >> choice;
	} while (choice > 3 || choice < 1);
	return enGameChoice(choice);
}

enGameChoice ChoiceOfComputer() {
	return enGameChoice(RandomNumber(1, 3));
}

enWinner whoWinRound(stRoundInfo roundInfo) {

	if (roundInfo.PlayerChoice == roundInfo.ComputerChoice) {
		return enWinner::draw;
	}

	switch (roundInfo.PlayerChoice) {

	case (enGameChoice::stone):
		if (roundInfo.ComputerChoice == enGameChoice::papper) {
			return enWinner::computer;
		}
		break;

	case (enGameChoice::papper):
		if (roundInfo.ComputerChoice == enGameChoice::scissors) {
			return enWinner::computer;
		}
		break;

	case (enGameChoice::scissors):
		if (roundInfo.ComputerChoice == enGameChoice::stone) {
			return enWinner::computer;
		}
		break;
	}

	return enWinner::player;
}

string roundWinnerName(enWinner choice) {
	string arr[3] = { "player","computer","draw" };
	return arr[choice - 1];
}

string choiceName(enGameChoice choice) {
	string arr[3] = { "Stone" , "Papper" , "Scissors" };
	return arr[choice - 1];
}

void theResultColor(stGameResults gameResult) {
	if (gameResult.PlayerWinTimes > gameResult.ComputerWinTimes) {
		system("color 2F");
		cout << "\a";
	}
	else if (gameResult.PlayerWinTimes < gameResult.ComputerWinTimes) {
		system("color 4F");
		cout << "\a";
	}
	else {
		system("color 6F");
		cout << "\a";
	}
}

void printRoundResult(stRoundInfo roundInfo) {
	cout << "---------------- Game Round [ " << roundInfo.RoundNumber << " ]----------------" << endl;
	cout << "The Player Choice      : " << choiceName(roundInfo.PlayerChoice) << endl;
	cout << "The Computer Choice    :" << choiceName(roundInfo.ComputerChoice) << endl;
	cout << "The Winner of round    :" << roundInfo.WinnerName << endl;
	cout << "-------------------------------------------------" << endl;
	setWinnerScreenColors(roundInfo.Winner);
}

enWinner WhoWinInGame(stGameResults gameResult) {
	if (gameResult.PlayerWinTimes > gameResult.ComputerWinTimes) {
		return enWinner::player;
	}
	else if (gameResult.ComputerWinTimes > gameResult.PlayerWinTimes) {
		return enWinner::computer;
	}
	else {
		return enWinner::draw;
	}


}

string GameWinnerName(enWinner winner) {
	string arr[3] = { "Player" , "Computer" , "Draw" };
	return arr[winner - 1];
}

stGameResults fillGameResults(int numberRounds, int playerWinTimes, int computerWinTimes, int drawTimes) {
	stGameResults gameResult;
	gameResult.GameRounds = numberRounds;
	gameResult.PlayerWinTimes = playerWinTimes;
	gameResult.ComputerWinTimes = computerWinTimes;
	gameResult.DrawTimes = drawTimes;
	gameResult.Winner = WhoWinInGame(gameResult);
	gameResult.WinnerName = GameWinnerName(gameResult.Winner);
	return gameResult;
}

stGameResults playGame(int numberRounds) {

	stRoundInfo roundInfo;

	int playerWinTimes = 0;
	int computerWinTimes = 0;
	int drawTimes = 0;

	for (int gameRound = 1; gameRound <= numberRounds; gameRound++) {
		roundInfo.RoundNumber = gameRound;
		roundInfo.PlayerChoice = ChoiceOfPlayer();
		roundInfo.ComputerChoice = ChoiceOfComputer();
		roundInfo.Winner = whoWinRound(roundInfo);
		roundInfo.WinnerName = roundWinnerName(roundInfo.Winner);

		if (roundInfo.Winner == enWinner::player) {
			playerWinTimes++;
		}
		else if (roundInfo.Winner == enWinner::computer) {
			computerWinTimes++;
		}
		else {
			drawTimes++;
		}

		printRoundResult(roundInfo);

	}

	return fillGameResults(numberRounds, playerWinTimes, computerWinTimes, drawTimes);

}

void showGameOver() {
	cout << endl << endl << Tabs(2) << "----------------------------------------------------------" << endl;
	cout << Tabs(2) << "---------------- *** G a m e  O v e r *** ----------------" << endl;
	cout << Tabs(2) << "----------------------------------------------------------" << endl;
}

void printGameResults(stGameResults gameResult) {
	cout << Tabs(2) << "\n\n\n-------------- *** G a m e  R e s u l t s *** --------------\n" << endl;
	cout << Tabs(2) << "The Game Rounds        :" << gameResult.GameRounds << endl;
	cout << Tabs(2) << "The Player Win Times   :" << gameResult.PlayerWinTimes << endl;
	cout << Tabs(2) << "The Computer Win Times :" << gameResult.ComputerWinTimes << endl;
	cout << Tabs(2) << "The Draw Times         :" << gameResult.DrawTimes << endl;
	cout << Tabs(2) << "The winner is          :" << gameResult.WinnerName << endl;
	theResultColor(gameResult);
}

void startGame() {
	char PlayMore = 'y';
	do {
		restScreen();
		stGameResults gameResult = playGame(HowManyRounds());
		showGameOver();
		printGameResults(gameResult);
		cout << "\n------------------------------------------------------------" << endl;
		cout << "Do You Want to play More ? ( Y / N ) ?" << endl;
		cin >> PlayMore;

	} while (PlayMore == 'y' || PlayMore == 'Y');

}

int main() {
	srand((unsigned)time(NULL));

	startGame();
	return 0;
}