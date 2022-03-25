//Tic-Tac-Toe v1
//The user plays against the computer in a match of tic-tac-toe. The cpu makes its choices on randomized spots.
//Brian Nguyen

#include <iostream>
#include <time.h>
#include <algorithm>
using namespace std;

void printBoard(char gameboard[9]) {
	for (int i = 0; i < 9; i++) {
			cout << " " << gameboard[i];
			if (i == 2 || i == 5) {
				cout << endl << "-----------" << endl;;
			}
			else if(i == 8){
				cout << endl << endl;
			}
			else {
				cout << " |";
			}
	}
}

bool isFull(char gameboard[9]) {
	for (int i = 0; i < 9; i++) {
		if (gameboard[i] == ' ') {
			return false;
		}
	}
	return true;
}

bool checkWin(char gameboard[9], char piece) {
	if ((gameboard[0] == piece && gameboard[1] == piece && gameboard[2] == piece)
		|| (gameboard[3] == piece && gameboard[4] == piece && gameboard[5] == piece)
		|| (gameboard[6] == piece && gameboard[7] == piece && gameboard[8] == piece)
		|| (gameboard[0] == piece && gameboard[3] == piece && gameboard[6] == piece)
		|| (gameboard[1] == piece && gameboard[4] == piece && gameboard[7] == piece)
		|| (gameboard[2] == piece && gameboard[5] == piece && gameboard[8] == piece)
		|| (gameboard[0] == piece && gameboard[4] == piece && gameboard[8] == piece)
		|| (gameboard[2] == piece && gameboard[4] == piece && gameboard[6] == piece)) {
		return true;
	}
	else {
		return false;
	}
}

int evaluate(char gameboard[9], char cpuPiece, char playerPiece) {
	if (checkWin(gameboard, cpuPiece)) {
		return 10;
	}
	if (checkWin(gameboard, playerPiece)) {
		return -10;
	}
	return 0;
}

int minimax(char gameboard[9], char cpuPiece, char playerPiece, bool isMax) {
	int score = evaluate(gameboard, cpuPiece, playerPiece);
	if (score == 10 || score == -10) {
		return score;
	}
	if (isFull(gameboard)) {
		return 0;
	}

	if (isMax) {
		int best = -1000;
		for (int i = 0; i < 9; i++) {
			if (gameboard[i] == ' ') {
				gameboard[i] = cpuPiece;
				best = max(best, minimax(gameboard, cpuPiece, playerPiece, !isMax));
				gameboard[i] = ' ';
			}
		}
		return best;
	}
	else {
		int best = 1000;
		for (int i = 0; i < 9; i++) {
			if (gameboard[i] == ' ') {
				gameboard[i] = playerPiece;
				best = min(best, minimax(gameboard, cpuPiece, playerPiece, !isMax));
				gameboard[i] = ' ';
			}
		}
		return best;
	}
}

int findBestMove(char gameboard[9], char cpuPiece, char playerPiece) {
	int bestVal = -1000;
	int bestIndex = -1;
	for (int i = 0; i < 9; i++) {
		if (gameboard[i] == ' ') {
			gameboard[i] = cpuPiece;
			int moveVal = minimax(gameboard, cpuPiece, playerPiece, false);
			gameboard[i] = ' ';
			if (moveVal > bestVal) {
				bestIndex = i;
				bestVal = moveVal;
			}
		}
	}
	return bestIndex;
}

void compTurn(char (&gameboard)[9], char cpuPiece, char playerPiece) {
	int index = findBestMove(gameboard, cpuPiece, playerPiece);
	gameboard[index] = cpuPiece;
}

void playerTurn(char (&gameboard)[9], char piece) {
	int index;
	while (true) {
		cout << "Select a number (1-9) to indicate where your piece is going: ";
		cin >> index;
		cout << endl;
		if (gameboard[index - 1] == ' ') {
			gameboard[index - 1] = piece;
			break;
		}
		else {
			cout << "Invalid spot." << endl;
		}
	}
}



int main() {
	cout << "Tic-Tac-Toe created by Brian Nguyen." << endl << "Press Enter to continue." << endl;
	cin.ignore();

	bool flag = true;
	while (flag){
		char tempBoard[9] = { '1', '2', '3','4','5','6','7','8','9' };
		cout << "Use this template to input your piece to the board: " << endl;
		printBoard(tempBoard);

		char gameboard[9] = {' ',' ',' ',
							    ' ',' ',' ',
							    ' ',' ',' '};
		cout << "Here is the game board: " << endl;
		printBoard(gameboard);

		cout << "Choose an option (X or O). Type 1 for X and 2 for O: ";
		int input;
		cin >> input;
		while (true) {
			if (input != 1 && input != 2) {
				cout << "Not a vaild option, try again." << endl;
			}
			else {
				break;
			}
			cout << "Choose an option (X or O). Type 1 for X and 2 for O: ";
			cin >> input;
		}

		char playerPiece;
		char cpuPiece;
		if (input == 2) {
			playerPiece = 'O';
			cpuPiece = 'X';
			compTurn(gameboard, cpuPiece, playerPiece);
		}
		else {
			playerPiece = 'X';
			cpuPiece = 'O';
		}
		system("cls");
		cout << "Here is the board status: " << endl;
		printBoard(gameboard);
		while (true) {
			playerTurn(gameboard, playerPiece);
			system("cls");
			if (checkWin(gameboard, playerPiece)) {
				cout << "You won!" << endl << endl;
				printBoard(gameboard);
				break;
			}
			if (isFull(gameboard)) {
				cout << "It's a tie!" << endl << endl;
				printBoard(gameboard);
				break;
			}
			compTurn(gameboard, cpuPiece, playerPiece);
			if (checkWin(gameboard, cpuPiece)) {
				cout << "You lost." << endl << endl;
				printBoard(gameboard);
				break;
			}
			if (isFull(gameboard)) {
				cout << "It's a tie!" << endl;
				printBoard(gameboard);
				break;
			}
			cout << "Here is the board status: " << endl;
			printBoard(gameboard);
		}
		
		int input2;
		cout << "Would you like to play again? (1 for Yes, 2 for No): ";
		cin >> input2;
		while (true) {
			if (input2 != 1 && input2 != 2) {
				cout << "Not a vaild option, try again." << endl;
			}
			else {
				break;
			}
			cout << "Would you like to play again? (1 for Yes, 2 for No): ";
			cin >> input2;
		}

		if (input2 == 2) {
			flag = false;
		}
		system("cls");
	}

	return 0;
}