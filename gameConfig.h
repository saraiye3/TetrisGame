#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

#include <iostream>

class GameConfig
{
public:
	enum class eKeys { BA_LEFT = 'a', BA_RIGHT = 'd', BA_ROTATE_CLOCKWISE = 's', BA_ROTATE_COUNTER_CLOCKWISE = 'w', BA_DROP = 'x', BB_LEFT = 'j', BB_RIGHT = 'l', BB_ROTATE_CLOCKWISE = 'k', BB_ROTATE_COUNTER_CLOCKWISE = 'i', BB_DROP = 'm', ESC = 27 };
	enum class eDirection { DOWN = 0, LEFT, RIGHT, DROP, ROTATE };
	static constexpr int UPPER_CASE = 32;
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X_BOARD_A = 16;
	static constexpr int MIN_Y_BOARD_A = 5;
	static constexpr int MIN_X_BOARD_B = 40;
	static constexpr int MIN_Y_BOARD_B = 5;

	static constexpr int SHAPE_SIZE_IN_POINTS = 4;
	static constexpr int NUM_OF_SHAPE_KINDS = 7;

	static constexpr int AVAILABLE_SQUARE = 1;
	static constexpr int OCCUPIED_SQUARE = 0;

	static constexpr char SHAPE_CH = '0';

	static constexpr int CLEARED_ROW_BONUS = 50;
	static constexpr int WINNER_BONUS = 300;

	static constexpr int CLOCKWISE = 1;
	static constexpr int COUNTERCLOCKWISE = -1;

	const static int KEYS_TABLE_ROWS = 6;
	const static int KEYS_TABLE_COLS = 3;

	static constexpr char BOMB_CH = 'B';
	static constexpr int BOMB_RANGE = 4;
	static constexpr int SQUARE_LENGTH = 9;

	static constexpr char BEST = 'a';
	static constexpr char GOOD = 'b';
	static constexpr char NOVICE = 'c';

};
#endif

