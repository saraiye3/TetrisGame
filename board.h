#ifndef __BOARD_H
#define __BOARD_H

#include "gameConfig.h"
#include "shape.h"
#include "shapeFactory.h"

class Board
{
private:

	int nextShapeNum;
	int gameBoard[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	int min_x = 0;
	int min_y = 0;
	int score = 0;
	ShapeFactory shapeFactory;
	Shape shape;
	bool new_shape = false;
	bool testing = false; //for computer player

public:

	void initBoard(int min_x, int min_y);
	int getMin_X() const;
	int getMin_Y() const;
	void drawBoard() const;
	int getSquareValue(int row, int col) const;
	void updateMatrixWithZeros(const Shape& shape);
	int identifyCompletedRows();
	void clearRow(int row);
	void drawUpdatedBoard() const;
	bool isLoser() const;
	void setScore(int score);
	int getScore() const;
	Shape& getShape(); //cannot be a const function!
	void setShape(Shape& shape);
	void moveDown();
	void dropNewShape();

	void detonateBomb(const Shape& shape);
	bool checkBorders(int x, int y);
	void shiftSquaresDown();

	bool newShape() { return new_shape; } //for computer player
	void setTest(bool test) { testing = test; } //for computer player
	bool getTest() { return testing; } //for computer player
	Point getHighestPoint(); //for computer player
};

#endif