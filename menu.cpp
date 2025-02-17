#include "menu.h"
#include "general.h"
#include "gameConfig.h"

#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;


int Menu::printMenu(bool printContinuePause) const
{
	int playerChoice;

	clrscr();
	cout << "(1) Start a new game - Human vs Human" << endl;
	cout << "(2) Start a new game - Human vs Computer" << endl;
	cout << "(3) Start a new game - Computer vs Computer" << endl;
	if (printContinuePause)
		cout << "(4) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;


	while (true)
	{
		cin >> playerChoice;

		if (playerChoice == 1)
			break;
		if (playerChoice == 2)
			break;
		if (playerChoice == 3)
			break;
		if (playerChoice == 8)
			break;
		if (playerChoice == 9)
			break;
		if ((playerChoice == 4) && (printContinuePause))
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << "Looks like you've got your keys confused there. Try again" << endl;
	}

	return playerChoice;
}

int Menu::getLevel() const
{
	char playerChoice;

	clrscr();
	cout << "Please choose the game level" << endl;
	cout << "(a) BEST" << endl;
	cout << "(b) GOOD" << endl;
	cout << "(c) NOVICE" << endl;

	while (true)
	{
		cin >> playerChoice;

		if (playerChoice == GameConfig::BEST)
			break;
		if (playerChoice == GameConfig::GOOD)
			break;
		if (playerChoice == GameConfig::NOVICE)
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Looks like you've got your keys confused there. Try again" << endl;
	}

	return playerChoice - 'a';
}


void Menu::printInstructionsAndKeys() const
{
	clrscr();

	const char* keysTable[GameConfig::KEYS_TABLE_ROWS][GameConfig::KEYS_TABLE_COLS];
	keysTable[0][0] = "                           ";
	keysTable[0][1] = "Left Player";
	keysTable[0][2] = "Right Player";
	keysTable[1][0] = "LEFT";
	keysTable[1][1] = "a or A";
	keysTable[1][2] = "j or J";
	keysTable[2][0] = "RIGHT";
	keysTable[2][1] = "d or D";
	keysTable[2][2] = "l or L";
	keysTable[3][0] = "ROTATE clockwise";
	keysTable[3][1] = "s or S";
	keysTable[3][2] = "k or K";
	keysTable[4][0] = "ROTATE counterclockwise";
	keysTable[4][1] = "w or W";
	keysTable[4][2] = "i or I";
	keysTable[5][0] = "DROP";
	keysTable[5][1] = "x or X";
	keysTable[5][2] = "m or M";

	printInstructions();
	printKeysTable(keysTable, GameConfig::KEYS_TABLE_ROWS, GameConfig::KEYS_TABLE_COLS);

	while (true)
	{
		cout << "\nPress ESC to continue" << endl;
		int keyPressed = _getch();
		if (keyPressed == (int)GameConfig::eKeys::ESC)
			return;
	}
}

void Menu::printInstructions() const
{
	cout << "GOAL - CLEARING LINES - To clear a line, fill every square within a single row." << endl;
	cout << endl << "SCORE POINTS - earn points by clearing lines." << endl;
	cout << "Each line you clear is worth 50 points. " << "Winner gets a 300 points bonus!" << endl;
	cout << endl << "GAME OVER - the player whose bricks stack" << endl << "to the top of the matrix first loses the game." << endl;

}

void Menu::printKeysTable(const char* table[][GameConfig::KEYS_TABLE_COLS], size_t rows, size_t cols) const
{
	cout << endl << "keys:" << endl;
	cout << " ___________________________________________________________________" << endl;
	cout << "|" << table[0][0] << "| " << table[0][1] << "           " << "| " << table[0][2] << "  " << "|" << endl;
	cout << " ___________________________________________________________________" << endl;
	cout << "|" << table[1][0] << "                       " << "| " << table[1][1] << "                " << "| " << table[1][2] << "        " << "|" << endl;
	cout << " ___________________________________________________________________" << endl;
	cout << "|" << table[2][0] << "                      " << "| " << table[2][1] << "                " << "| " << table[2][2] << "        " << "|" << endl;
	cout << " ___________________________________________________________________" << endl;
	cout << "|" << table[3][0] << "           " << "| " << table[3][1] << "                " << "| " << table[3][2] << "        " << "|" << endl;
	cout << " ___________________________________________________________________" << endl;
	cout << "|" << table[4][0] << "    " << "| " << table[4][1] << "                " << "| " << table[4][2] << "        " << "|" << endl;
	cout << " ___________________________________________________________________" << endl;
	cout << "|" << table[5][0] << "                       " << "| " << table[5][1] << "                " << "| " << table[5][2] << "        " << "|" << endl;
	cout << " ___________________________________________________________________" << endl;

}