#ifndef __MENU_H
#define __MENU_H
#include "gameConfig.h"

class Menu
{
public:
	int printMenu(bool printContinuePause) const;
	int getLevel() const;
	void printInstructionsAndKeys() const;
	void printInstructions() const;
	void printKeysTable(const char* table[][GameConfig::KEYS_TABLE_COLS], size_t rows, size_t cols) const;
};

#endif