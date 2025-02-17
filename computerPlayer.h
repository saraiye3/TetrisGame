
#ifndef __COMPUTERPLAYER_H
#define __COMPUTERPLAYER_H

#include <iostream>
#include <list>
#include "player.h"
#include "board.h"
#include "shape.h"

class ComputerPlayer : public Player
{
public:
    enum eGameLevel { BEST, GOOD, NOVICE };
private:
    eGameLevel gameLevel;
    unsigned int randomCycle = 0;
    unsigned int cycleCounter = 0;
    list<Shape> oldSite;

    typedef struct move
    {
        eMoveType move;
        int numOfRowsDeleted = 0;

        Point landingMinPoint;
        int numOflandingMinPoints;

        Point landingMaxPoint;
        int numOflandingMaxPoints;

    }Move;

    list<Move> pathToPlay;
    list<Move> buildPath(Board board);

    list<Move> moveDown(Board board, Move moveStep);
    list<Move> moveNop(Board board);
    list<Move> moveLeft(Board board);
    list<Move> moveRight(Board board);
    list<Move> moveRotateLeft(Board board);
    list<Move> moveRotateRight(Board board);

    list<Move> buildBestPath(Board& board);
    list<Move> buildRandomPath(Board& board);
    list<Move> buildHeuristicPath(Board& board);
    list<Move> buildBombPath(Board& board, Point highPoint);
    Move getNextMove();
    virtual void makeMove(eMoveType move) override;

public:
    virtual ~ComputerPlayer() {};
    virtual void play(int pressedKey) override;
    virtual void initPlayer(int min_x, int min_y, ePlayerType playerType) override;
    void setLevel(eGameLevel level);
    Board& getBoard(); //cannot be a const function!
};

#endif
