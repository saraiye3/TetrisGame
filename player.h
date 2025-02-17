#ifndef __PLAYER_H
#define __PLAYER_H

#include "board.h"

class Player
{
public:
    enum class eMoveType { NOP = 0, LEFT, RIGHT, ROTATE_LEFT, ROTATE_RIGHT, DROP };
    enum class ePlayerType { LEFT_COMPUTER = 0, RIGHT_COMPUTER, LEFT_HUMAN, RIGHT_HUMAN };

protected:
    Board board;
    ePlayerType playerType;

public:
    virtual ~Player() {};
    virtual void play(int pressedKey) {};
    virtual void makeMove(eMoveType move) {};
    virtual void initPlayer(int min_x, int min_y, ePlayerType playerType) {};
    Board& getBoard() { return this->board; };

};

#endif