#ifndef __TETRISGAME_H
#define __TETRISGAME_H

#include "board.h"
#include "menu.h"
#include "computerPlayer.h"


class TetrisGame
{
	Menu mainMenu;
	Player* playerA = NULL;
	Player* playerB = NULL;

	bool hasWinner();
	void refreshGame(); //cannot be const! 


public:
	void run(); //cannot be const
	int runGame(); //cannot be const
};
#endif

