#include <conio.h> // for kbhit+getch
#include <iostream>
#include <Windows.h> // for Sleep
using namespace std;

#include "general.h"
#include "gameConfig.h"
#include "point.h"
#include "shape.h"
#include "tetrisGame.h"

void playGame();


int main()
{
	playGame();

}

void playGame()
{

	TetrisGame theGame;

	theGame.run();

}