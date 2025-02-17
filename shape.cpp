#include "shape.h"
#include "point.h"
#include "gameConfig.h"
#include "board.h"
using namespace std;


void Shape::init(eshape shapeType, char ch)
{
	this->ch = ch;
	this->shapeType = shapeType;

	switch (shapeType)
	{
	case Shape::eshape::PLUS:
		figure[0].init(5, 0);
		figure[1].init(6, 0);
		figure[2].init(7, 0);
		figure[3].init(6, 1);
		break;

	case Shape::eshape::L:
		figure[0].init(5, 0);
		figure[1].init(5, 1);
		figure[2].init(5, 2);
		figure[3].init(6, 2);
		break;

	case Shape::eshape::L_MIRRORED:
		figure[0].init(5, 0);
		figure[1].init(5, 1);
		figure[2].init(5, 2);
		figure[3].init(4, 2);
		break;

	case Shape::eshape::SQUARE:
		figure[0].init(5, 0);
		figure[1].init(6, 0);
		figure[2].init(5, 1);
		figure[3].init(6, 1);
		break;

	case Shape::eshape::I:
		figure[0].init(5, 0);
		figure[1].init(5, 1);
		figure[2].init(5, 2);
		figure[3].init(5, 3);

		break;

	case Shape::eshape::Z:
		figure[0].init(6, 0);
		figure[1].init(7, 0);
		figure[2].init(5, 1);
		figure[3].init(6, 1);

		break;

	case Shape::eshape::Z_MIRRORED:
		figure[0].init(5, 0);
		figure[1].init(6, 0);
		figure[2].init(6, 1);
		figure[3].init(7, 1);
		break;

	case Shape::eshape::BOMB:
		figure[0].init(5, 0);
		figure[1].init(5, 0);
		figure[2].init(5, 0);
		figure[3].init(5, 0);
		break;
	}

}


bool Shape::canMoveDown()
{
	bool flag = true;
	int x, y;

	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS && flag; i++)
	{
		x = this->figure[i].getX();
		y = this->figure[i].getY();

		if (y + 1 >= GameConfig::GAME_HEIGHT || this->myBoard->getSquareValue(y + 1, x) == GameConfig::OCCUPIED_SQUARE)
		{
			flag = false;
		}
	}


	return flag;
}

bool Shape::moveDown()
{

	if (canMoveDown())
	{
		draw(' ');
		for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
		{
			this->figure[i].moveDown();
		}

		draw(ch);
		return true;
	}

	return false;
}

Point Shape::getYminPoint()
{
	Point yMinPoint = this->figure[0];
	for (int i = 1; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
	{
		Point currP = this->figure[i];
		if (yMinPoint.getY() > currP.getY())
			yMinPoint = currP;
	}
	return yMinPoint;
}

Point Shape::getYmaxPoint()
{
	Point yMaxPoint = this->figure[0];
	for (int i = 1; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
	{
		Point currP = this->figure[i];
		if (yMaxPoint.getY() < currP.getY())
			yMaxPoint = currP;
	}
	return yMaxPoint;
}


int Shape::getYPointCount(Point yPoint)
{
	int count = 0;
	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
	{
		Point currP = this->figure[i];
		if (yPoint.getY() == currP.getY())
			count++;
	}
	return count;
}

void Shape::setMyBoard(Board& board)
{
	myBoard = &board;
}

bool Shape::samePlace(Shape shape)
{
	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
	{
		if (figure[i].getX() != shape.figure[i].getX())
			return false;
		if (figure[i].getY() != shape.figure[i].getY())
			return false;
	}
	return true;
}

void Shape::draw(char ch) const
{
	if (myBoard->getTest())
		return;
	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
	{
		figure[i].draw(ch, myBoard);
	}
}

bool Shape::moveLeft()
{
	bool flag = true;
	int x, y;
	int min_x = myBoard->getMin_X();

	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS && flag; i++)
	{
		x = this->figure[i].getX();
		y = this->figure[i].getY();
		if (x - 1 < 0 || this->myBoard->getSquareValue(y, x - 1) == 0)
			flag = false;
	}
	if (flag)
	{
		draw(' ');
		for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
		{
			this->figure[i].moveLeft();
		}
		draw(ch);
	}

	return flag;
}

bool Shape::moveRight()
{
	bool flag = true;
	int x, y;

	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS && flag; i++)
	{
		x = this->figure[i].getX();
		y = this->figure[i].getY();

		if (x + 1 >= GameConfig::GAME_WIDTH || this->myBoard->getSquareValue(y, x + 1) == 0)
			flag = false;
	}
	if (flag)
	{
		draw(' ');
		for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
		{
			this->figure[i].moveRight();
		}
		draw(ch);
	}

	return flag;
}

void Shape::drop()
{
	bool flag = true;
	int x, y;

	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS && flag; i++)
	{
		x = this->figure[i].getX();
		y = this->figure[i].getY();

		if (y + 2 >= GameConfig::GAME_HEIGHT)
			flag = false;
		else if (this->myBoard->getSquareValue(y + 2, x) == GameConfig::OCCUPIED_SQUARE || this->myBoard->getSquareValue(y + 1, x) == GameConfig::OCCUPIED_SQUARE)
			flag = false;
	}

	if (flag)
	{
		draw(' ');
		for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
		{
			this->figure[i].drop();

		}
		draw(ch);
	}

}

Point Shape::getPoint(int index) const
{
	return figure[index];
}

Shape::eshape Shape::getShapeType() const
{
	return shapeType;
}

bool Shape::rotate_CounterClockWise()
{
	return rotate(GameConfig::COUNTERCLOCKWISE);
}

bool Shape::rotate_ClockWise()
{
	return rotate(GameConfig::CLOCKWISE);

}

bool Shape::rotate(int rotateDirection)
{
	if (this->getShapeType() == Shape::eshape::SQUARE)
		return true;

	bool flag = true;
	Point center = figure[0];

	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS && flag; i++)
	{

		int relativeX = center.getX() - figure[i].getX();
		int relativeY = center.getY() - figure[i].getY();


		int newX = center.getX() + relativeY * rotateDirection;
		int newY = center.getY() - relativeX * rotateDirection;

		if (newY >= GameConfig::GAME_HEIGHT || newY < 0 || newX < 0 || newX >= GameConfig::GAME_WIDTH) //check board borders
			flag = false;
		else if (this->myBoard->getSquareValue(newY, newX) == GameConfig::OCCUPIED_SQUARE) //check if square is occupied
			flag = false;
	}

	if (flag)

	{
		Point center = figure[0];

		draw(' ');
		for (int i = 1; i < GameConfig::SHAPE_SIZE_IN_POINTS; ++i)
		{
			this->figure[i].rotate(center, rotateDirection);
		}
		draw(ch);
	}

	return flag;
}

char Shape::getChar() const
{
	return ch;
}
