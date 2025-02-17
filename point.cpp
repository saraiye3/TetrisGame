#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include <iostream>
#include "board.h"
using namespace std;

void Point::init(int x, int y)
{
	this->x = x;
	this->y = y;
	diff_x = 0;
	diff_y = 1;
}

void Point::draw(char ch, const Board* board) const
{
	gotoxy(x + board->getMin_X(), y + board->getMin_Y());
	cout << ch;
}

void Point::moveDown()
{
	int x = getX();
	int y = getY();
	init(x, y + 1);
}

void Point::moveLeft()
{
	int x = getX();
	int y = getY();
	init(x - 1, y);
}

void Point::moveRight()
{
	int x = getX();
	int y = getY();
	init(x + 1, y);
}

void Point::drop()
{
	int x = getX();
	int y = getY();
	init(x, y + 2);
}

void Point::rotate(const Point& center, int rotateDirection)
{
	int relativeX = center.x - getX();
	int relativeY = center.y - getY();

	int newX = center.x + relativeY * rotateDirection;
	int newY = center.y - relativeX * rotateDirection;

	init(newX, newY);

}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}