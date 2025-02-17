#ifndef __SHAPE_H
#define __SHAPE_H

class Board;
#include "point.h"
#include "gameConfig.h"
using namespace std;


class Shape
{
public:
	enum class eshape { PLUS = 0, I, L, L_MIRRORED, SQUARE, Z, Z_MIRRORED, BOMB };
private:
	Point figure[GameConfig::SHAPE_SIZE_IN_POINTS];
	char ch;
	eshape shapeType;
	Board* myBoard;
	bool rotate(int  direction);

public:
	void init(eshape shapeType, char ch);
	void setMyBoard(Board& board);
	void draw(char ch) const;
	bool moveLeft();
	bool moveRight();
	void drop();
	bool moveDown();
	bool canMoveDown();
	bool rotate_ClockWise();
	bool rotate_CounterClockWise();
	Point getPoint(int index) const;
	char getChar() const;
	Shape::eshape getShapeType() const;


	int getYPointCount(Point yPoint); //for computer player
	Point getYminPoint(); //for computer player
	Point getYmaxPoint(); //for computer player
	bool samePlace(Shape); //for computer player
};

#endif 

