#ifndef __POINT_H 
#define __POINT_H
#include "gameConfig.h"

class Board;

class Point
{
	int x = 0;
	int y = 0;
	int diff_x = 0;
	int diff_y = 0;

public:
	void init(int x, int y);
	void draw(char ch, const Board* board) const;
	void moveDown();
	void moveLeft();
	void moveRight();
	void drop();
	void rotate(const Point& center, int rotateDirection);
	int getX() const;
	int getY() const;


};

#endif 
