#include "player.h"
#include "computerPlayer.h"
#include "humanPlayer.h"
#include "tetrisGame.h"
#include "general.h"
#include "menu.h"

#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool TetrisGame::hasWinner()
{
	bool flag = false;
	Board& playerA_board = playerA->getBoard();
	Board& playerB_board = playerB->getBoard();

	if (playerA_board.isLoser() && !playerB_board.isLoser())
	{
		playerB_board.setScore(playerB_board.getScore() + GameConfig::WINNER_BONUS);
		clrscr();
		cout << "player B won!" << endl;
		cout << "player B score is: " << playerB_board.getScore() << endl;
		cout << "player A score is: " << playerA_board.getScore() << endl;
		flag = true;
	}

	else if (playerB_board.isLoser() && !playerA_board.isLoser())
	{
		playerA_board.setScore(playerA_board.getScore() + GameConfig::WINNER_BONUS);
		clrscr();
		cout << "player A won!" << endl;
		cout << "player A score is: " << playerA_board.getScore() << endl;
		cout << "player B score is: " << playerB_board.getScore() << endl;
		flag = true;

	}

	else if (playerA_board.isLoser() && playerB_board.isLoser())
	{
		if (playerA_board.getScore() > playerB_board.getScore())
		{
			clrscr();
			cout << "player A won!" << endl;
			cout << "player A score is: " << playerA_board.getScore() << endl;
			cout << "player B score is: " << playerB_board.getScore() << endl;
			flag = true;

		}

		else if (playerB_board.getScore() > playerA_board.getScore())
		{
			clrscr();
			cout << "player B won!" << endl;
			cout << "player B score is: " << playerB_board.getScore() << endl;
			cout << "player A score is: " << playerA_board.getScore() << endl;
			flag = true;

		}

		else
		{
			clrscr();
			cout << "It's a tie!" << endl;
			flag = true;

		}

	}
	if (flag)
		cout << endl << "Press ESC to return to main menu" << endl;

	while (flag)
	{
		int keyPressed = _getch();
		if (keyPressed == (int)GameConfig::eKeys::ESC)
			break;
	}
	return flag;
}


void TetrisGame::refreshGame()
{

	if (playerA != NULL)
	{
		playerA->getBoard().drawUpdatedBoard();
		playerA->getBoard().getShape().draw(GameConfig::SHAPE_CH);
	}
	if (playerA != NULL)
	{
		playerB->getBoard().drawUpdatedBoard();
		playerB->getBoard().getShape().draw(GameConfig::SHAPE_CH);
	}
}



void TetrisGame::run()
{

	bool puase = false;
	int option = 0;
	char level = '0';

	while (true)
	{

		option = mainMenu.printMenu(puase);
		clrscr();

		switch (option)
		{
		case 1:
			if (playerA != NULL)
				delete playerA;
			if (playerB != NULL)
				delete playerB;
			playerA = new HumanPlayer();
			playerB = new HumanPlayer();

			playerA->initPlayer(GameConfig::MIN_X_BOARD_A, GameConfig::MIN_Y_BOARD_A, Player::ePlayerType::LEFT_HUMAN);
			playerB->initPlayer(GameConfig::MIN_X_BOARD_B, GameConfig::MIN_Y_BOARD_B, Player::ePlayerType::RIGHT_HUMAN);

			playerA->getBoard().drawBoard();
			playerA->getBoard().getShape().draw(GameConfig::SHAPE_CH);

			playerB->getBoard().drawBoard();
			playerB->getBoard().getShape().draw(GameConfig::SHAPE_CH);

			puase = true;
			refreshGame();
			runGame();
			break;
		case 2:
			if (playerA != NULL)
				delete playerA;
			if (playerB != NULL)
				delete playerB;
			clrscr();
			level = mainMenu.getLevel();
			clrscr();
			playerA = new HumanPlayer();
			playerB = new ComputerPlayer();

			playerA->initPlayer(GameConfig::MIN_X_BOARD_A, GameConfig::MIN_Y_BOARD_A, Player::ePlayerType::LEFT_HUMAN);
			playerB->initPlayer(GameConfig::MIN_X_BOARD_B, GameConfig::MIN_Y_BOARD_B, Player::ePlayerType::RIGHT_COMPUTER);

			((ComputerPlayer*)playerB)->setLevel((ComputerPlayer::eGameLevel)level);

			playerA->getBoard().drawBoard();
			playerA->getBoard().getShape().draw(GameConfig::SHAPE_CH);

			playerB->getBoard().drawBoard();
			playerB->getBoard().getShape().draw(GameConfig::SHAPE_CH);

			puase = true;
			refreshGame();
			runGame();
			break;

		case 3:
			if (playerA != NULL)
				delete playerA;
			if (playerB != NULL)
				delete playerB;
			clrscr();
			level = mainMenu.getLevel();
			clrscr();
			playerA = new ComputerPlayer();
			playerB = new ComputerPlayer();

			playerA->initPlayer(GameConfig::MIN_X_BOARD_A, GameConfig::MIN_Y_BOARD_A, Player::ePlayerType::LEFT_COMPUTER);
			playerB->initPlayer(GameConfig::MIN_X_BOARD_B, GameConfig::MIN_Y_BOARD_B, Player::ePlayerType::RIGHT_COMPUTER);

			((ComputerPlayer*)playerA)->setLevel((ComputerPlayer::eGameLevel)level);
			((ComputerPlayer*)playerB)->setLevel((ComputerPlayer::eGameLevel)level);

			playerA->getBoard().drawBoard();
			playerA->getBoard().getShape().draw(GameConfig::SHAPE_CH);

			playerB->getBoard().drawBoard();
			playerB->getBoard().getShape().draw(GameConfig::SHAPE_CH);

			puase = true;
			refreshGame();
			runGame();
			break;
		case 4:
			refreshGame();
			runGame();
			break;
		case 8:
			option = 0;
			mainMenu.printInstructionsAndKeys();
			clrscr();
			refreshGame();
			break;
		case 9:
			if (playerA != NULL)
				delete playerA;
			if (playerB != NULL)
				delete playerB;
			return; //exit
		}

	}
}

int TetrisGame::runGame()
{

	playerA->getBoard().drawBoard();
	playerB->getBoard().drawBoard();
	bool pause = false;
	while (true)
	{
		int pressedKey = 0;
		if (_kbhit())
		{
			pressedKey = _kbhit();

			while (_kbhit() == pressedKey)
			{
				pressedKey = _getch();
			}

			if (pressedKey == (int)GameConfig::eKeys::ESC)
				return 0;

		}
		playerA->play(pressedKey);
		playerB->play(pressedKey);

		playerA->getBoard().moveDown();
		playerB->getBoard().moveDown();

		if (hasWinner())
			return 0;

		Sleep(500);


	}
}
