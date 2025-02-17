#include "board.h"
#include "general.h"
#include "gameConfig.h"
#include <stdlib.h>
#include <Windows.h>
using namespace std;

void Board::initBoard(int min_x, int min_y)
{
	this->min_x = min_x;
	this->min_y = min_y;
	this->score = 0;

	//initialize all elements in board to 1
	for (int i = 0; i < GameConfig::GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::GAME_WIDTH; j++)
		{
			gameBoard[i][j] = GameConfig::AVAILABLE_SQUARE;
		}
	}

	//set first shape
	shapeFactory.init();
	shape = shapeFactory.alloc();
	shape.setMyBoard(*this);
}

Shape& Board::getShape()
{
	return shape;
}

void Board::setShape(Shape& shape1)
{
	shape = shape1;
}

int Board::getMin_X() const
{
	return min_x;
}

int Board::getMin_Y() const
{
	return min_y;
}

/*this function draws the board's frame*/
void Board::drawBoard() const
{
	//return;
	for (int col = min_x - 1; col < GameConfig::GAME_WIDTH + min_x; col++)
	{
		gotoxy(col, min_y - 1);
		cout << "-";

		gotoxy(col, GameConfig::GAME_HEIGHT + min_y);
		cout << "-";
	}

	for (int row = min_y - 1; row <= GameConfig::GAME_HEIGHT + min_y; row++)
	{
		gotoxy(min_x - 1, row);
		cout << "|";

		gotoxy(GameConfig::GAME_WIDTH + min_x, row);
		cout << "|";
	}
}

/*this function returns 0 if a square is occupied and 1 otherwise*/
int Board::getSquareValue(int row, int col) const
{
	return gameBoard[row][col];
}

/*this function updates the matrix
to reflect the presence of a given shape on the game board*/
void Board::updateMatrixWithZeros(const Shape& shape)
{
	int x, y;

	for (int i = 0; i < GameConfig::SHAPE_SIZE_IN_POINTS; i++)
	{
		x = shape.getPoint(i).getX();
		y = shape.getPoint(i).getY();
		gameBoard[y][x] = GameConfig::OCCUPIED_SQUARE;
	}
}

/*this function searches for completed rows to clear*/
int Board::identifyCompletedRows()
{
	int numOfRowsCleared = 0;

	for (int i = 0; i < GameConfig::GAME_HEIGHT; i++)
	{
		bool flag = true;

		for (int j = 0; j < GameConfig::GAME_WIDTH && flag; j++)
		{
			if (gameBoard[i][j] == GameConfig::AVAILABLE_SQUARE) //if there's an available square in the row (it's not all zeros)
				flag = false;
		}

		if (flag) //if the entire row is zeros
		{
			numOfRowsCleared++;
			clearRow(i);
		}

	}

	return numOfRowsCleared;
}


/*this function removes a completed row from the matrix.
 It shifts down all rows above the specified row
 by copying each element from the row above to the corresponding position in the current row.
The bottom row is left unchanged, and the specified row is effectively removed.*/
void Board::clearRow(int row)
{
	for (int i = row; i > 0; i--)
	{
		for (int j = 0; j < GameConfig::GAME_WIDTH; j++)
		{
			gameBoard[i][j] = gameBoard[i - 1][j];
		}
	}

	for (int j = 0; j < GameConfig::GAME_WIDTH; j++) //make first row available
	{
		gameBoard[0][j] = GameConfig::AVAILABLE_SQUARE;
	}

}

/*this function re-draws the board
once a completed line is cleared off the board*/
void Board::drawUpdatedBoard() const
{

	for (int i = 0; i < GameConfig::GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::GAME_WIDTH; j++)
		{
			gotoxy(j + min_x, i + min_y);

			if (gameBoard[i][j] == GameConfig::OCCUPIED_SQUARE)
				cout << GameConfig::SHAPE_CH;
			else
				cout << ' ';
		}
	}
}

/*this function returns true if a player has lost the game*/
bool Board::isLoser() const
{
	if (shape.getShapeType() == Shape::eshape::BOMB)
		return false;
	else
	{
		bool flag = false;

		for (int j = 0; j < GameConfig::GAME_WIDTH && !flag; j++)
		{
			if (gameBoard[0][j] == GameConfig::OCCUPIED_SQUARE)
			{
				flag = true;
			}

		}
		return flag;
	}
}

void Board::moveDown()
{
	new_shape = false;

	if (!shape.moveDown())
	{
		if (shape.getShapeType() != Shape::eshape::BOMB)
		{
			this->updateMatrixWithZeros(shape);
			int completedRows = identifyCompletedRows();

			if (completedRows > 0)
			{
				drawUpdatedBoard();
				setScore(this->score + (completedRows * GameConfig::CLEARED_ROW_BONUS));
			}
		}
		else //if is a bomb
		{
			detonateBomb(shape);
			drawUpdatedBoard();
			shiftSquaresDown();
			drawUpdatedBoard();
		}

		dropNewShape();
	}
}

void Board::dropNewShape()
{
	new_shape = true;
	srand(static_cast<unsigned int>(time(nullptr)));
	nextShapeNum = rand() % 101;

	if (nextShapeNum >= 1 && nextShapeNum <= 5) //there's a 5% chance the random number is between 1 to 5
	{
		shape.init(Shape::eshape::BOMB, GameConfig::BOMB_CH);
	}
	else
	{
		shape = shapeFactory.alloc();
		shape.setMyBoard(*this);
	}
	shape.draw(shape.getChar());
}

void Board::setScore(int score)
{
	this->score = score;
}

int Board::getScore() const
{
	return score;
}

/*This function updates the game board
to reflect the bomb detonation effects,
removing any occupied squares within the explosion radius of the bomb
(in the shape of a square)*/
void Board::detonateBomb(const Shape& shape)
{
	int bombX = shape.getPoint(0).getX();
	int bombY = shape.getPoint(0).getY();
	int leftTopCornerX = bombX - GameConfig::BOMB_RANGE;
	int leftTopCornerY = bombY - GameConfig::BOMB_RANGE;

	for (int i = leftTopCornerX; i < leftTopCornerX + GameConfig::SQUARE_LENGTH; ++i)
	{
		for (int j = leftTopCornerY; j < leftTopCornerY + GameConfig::SQUARE_LENGTH; ++j)
		{
			if (checkBorders(i, j) && gameBoard[j][i] == GameConfig::OCCUPIED_SQUARE)
			{
				gameBoard[j][i] = GameConfig::AVAILABLE_SQUARE;
			}
		}
	}
}

/*This function returns true if a square is within board borders*/
bool Board::checkBorders(int x, int y)
{

	if (x < 0 || x >= GameConfig::GAME_WIDTH)
		return false;
	else if (y < 0 || y >= GameConfig::GAME_HEIGHT)
		return false;
	else
		return true;
}

/*This function is designed
to handle the post-explosion aftermath on the game board.
It systematically moves each available square
downward to the lowest possible position
within its respective column,
following the removal of squares due to a bomb explosion.*/
void Board::shiftSquaresDown()
{
	for (int j = 0; j < GameConfig::GAME_WIDTH; j++)
	{
		for (int i = GameConfig::GAME_HEIGHT - 1; i > 0; i--)
		{
			if (gameBoard[i][j] == GameConfig::AVAILABLE_SQUARE)
			{
				int closestOccupiedRow = i - 1;
				while (closestOccupiedRow >= 0 && gameBoard[closestOccupiedRow][j] == GameConfig::AVAILABLE_SQUARE)
				{
					closestOccupiedRow--;
				}

				if (closestOccupiedRow >= 0) //if an occupied square is found above - swap them
				{
					gameBoard[i][j] = GameConfig::OCCUPIED_SQUARE;
					gameBoard[closestOccupiedRow][j] = GameConfig::AVAILABLE_SQUARE;
				}
			}
		}
	}
}

/*This fucntion returns the highest occupied square in the game board,
which is where the computer player places a bomb at BEST level*/
Point Board::getHighestPoint() 
{
	Point p;
	int sequence = 0;
	int maxSequence = 0;
	int sequenceX = 0;
	int sequenceY = 0;


	for (int y = 0; y < GameConfig::GAME_HEIGHT; y++)
	{
		sequenceY = y;
		for (int x = 0; x < GameConfig::GAME_WIDTH; x++)
		{
			sequence = 0;

			while (gameBoard[y][x] == GameConfig::OCCUPIED_SQUARE && x < GameConfig::GAME_WIDTH)
			{
				x++;
				sequence++;
			}

			if (sequence > maxSequence)
			{
				maxSequence = sequence;
				sequenceX = x - 1;
			}
		}
		if (maxSequence > 0)
			break;
	}

	p.init(sequenceX - maxSequence / 2, sequenceY);

	return p;
}
