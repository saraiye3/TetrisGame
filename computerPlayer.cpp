#include "computerPlayer.h"
#include "general.h"
using namespace std;

void ComputerPlayer::initPlayer(int min_x, int min_y, ePlayerType playerType)
{
    // Initialize the board and build the initial best path
    randomCycle = 0;
    cycleCounter = 0;
    board.initBoard(min_x, min_y);
    buildBestPath(board);
}

void ComputerPlayer::setLevel(eGameLevel level)
{
    switch (level)
    {
    case eGameLevel::BEST:
        randomCycle = 0;
        break;
    case eGameLevel::GOOD:
        randomCycle = 10;
        break;
    case eGameLevel::NOVICE:
        randomCycle = 5;
        break;
    }
}

Board& ComputerPlayer::getBoard()
{
    // Return a reference to the board
    return board;
}

void ComputerPlayer::makeMove(ComputerPlayer::eMoveType move)
{
    // Make a move based on the specified move type
    switch (move)
    {
    case ComputerPlayer::eMoveType::NOP:
        return; // No operation
    case ComputerPlayer::eMoveType::LEFT:
        board.getShape().moveLeft();
        return;
    case ComputerPlayer::eMoveType::RIGHT:
        board.getShape().moveRight();
        return;
    case ComputerPlayer::eMoveType::ROTATE_LEFT:
        board.getShape().rotate_CounterClockWise();
        return;
    case ComputerPlayer::eMoveType::ROTATE_RIGHT:
        board.getShape().rotate_ClockWise();
        return;
    }
}

void ComputerPlayer::play(int pressedKey)
{
    // Play a round of the game
    if (board.newShape())
    {
        pathToPlay.clear();
        buildBestPath(board);
    }

    if (pathToPlay.size() <= 0)
        return;

    Move moveDetails = getNextMove();
    makeMove(moveDetails.move);
}

ComputerPlayer::Move ComputerPlayer::getNextMove()
{
    // Get the next move from the front of the best path
    Move nextMove = pathToPlay.front();

    pathToPlay.pop_front();
    return nextMove;
}

list<ComputerPlayer::Move> ComputerPlayer::buildBombPath(Board& board, Point highPoint)
{
    Point bombPoint = board.getShape().getPoint(0);

    int diffX = bombPoint.getX() - highPoint.getX();
    int y = highPoint.getY();
    int diffY = highPoint.getY() - bombPoint.getY();

    if (diffX < 0)
    {
        diffX = -diffX;

        for (int i = 0; i < diffX; i++)
        {
            Move moveStep;
            moveStep.move = eMoveType::RIGHT;
            pathToPlay.push_back(moveStep);
        }
    }
    else if (diffX > 0)
    {
        for (int i = 0; i < diffX; i++)
        {
            Move moveStep;
            moveStep.move = eMoveType::LEFT;
            pathToPlay.push_back(moveStep);
        }
    }


    for (int i = 0; i < diffY; i++)
    {
        Move moveStep;
        moveStep.move = eMoveType::NOP;
        pathToPlay.push_back(moveStep);
    }
    return pathToPlay;
}


list<ComputerPlayer::Move> ComputerPlayer::buildBestPath(Board& board)
{
    Point highPoint;

    if (board.getShape().getShapeType() == Shape::eshape::BOMB)
    {
        highPoint = board.getHighestPoint();
        return  buildBombPath(board, highPoint);
    }


    cycleCounter++;
    if (cycleCounter == randomCycle)
        cycleCounter = 0;

    if (cycleCounter == 0)
        return buildRandomPath(board);
    else
        return buildHeuristicPath(board);

}
list<ComputerPlayer::Move> ComputerPlayer::buildRandomPath(Board& board)
{
    //bestPath = buildPath(board);
    for (int y = 0; y < 18; y++)
    {
        int moveType = (rand() % 5);
        Move moveStep;
        moveStep.move = (eMoveType)moveType;
        pathToPlay.push_front(moveStep);
    }

    return pathToPlay;
}
list<ComputerPlayer::Move> ComputerPlayer::buildHeuristicPath(Board& board)
{
    // Build the best path based on the current board state
    oldSite.clear();
    board.setTest(true);
    pathToPlay = buildPath(board);
    board.setTest(false);
    board.drawBoard();
    board.drawUpdatedBoard();
    board.getShape().draw(GameConfig::SHAPE_CH);
    return pathToPlay;
}

list<ComputerPlayer::Move> ComputerPlayer::buildPath(Board board)
{
    list<Move> bestPath;
    {
        // Build a path for each possible move and choose the best one

        list<Move> moveNopPath = moveNop(board);
        bestPath = moveNopPath;

        list<Move> moveLeftPath = moveLeft(board);
        if (bestPath.empty())
            bestPath = moveLeftPath;

        list<Move> moveRightPath = moveRight(board);
        if (bestPath.empty())
            bestPath = moveRightPath;

        list<Move> moveRotateLeftPath = moveRotateLeft(board);
        if (bestPath.empty())
            bestPath = moveRotateLeftPath;

        list<Move> moveRotateRightPath = moveRotateRight(board);
        if (bestPath.empty())
            bestPath = moveRotateRightPath;

        if (bestPath.empty())
            return bestPath;



        if (moveLeftPath.size() > 0 && moveLeftPath.back().numOfRowsDeleted > bestPath.back().numOfRowsDeleted)
            bestPath = moveLeftPath;
        if (moveNopPath.size() > 0 && moveNopPath.back().numOfRowsDeleted > bestPath.back().numOfRowsDeleted)
            bestPath = moveNopPath;
        if (moveRotateLeftPath.size() > 0 && moveRotateLeftPath.back().numOfRowsDeleted > bestPath.back().numOfRowsDeleted)
            bestPath = moveRotateLeftPath;
        if (moveRotateRightPath.size() > 0 && moveRotateRightPath.back().numOfRowsDeleted > bestPath.back().numOfRowsDeleted)
            bestPath = moveRotateRightPath;
        if (moveRightPath.size() > 0 && moveRightPath.back().numOfRowsDeleted > bestPath.back().numOfRowsDeleted)
            bestPath = moveRightPath;



        // If no rows are deleted, choose the best move based on landing position
        if (bestPath.back().numOfRowsDeleted == 0)
        {
            if (moveLeftPath.size() > 0 && moveLeftPath.back().landingMinPoint.getY() > bestPath.back().landingMinPoint.getY())
                bestPath = moveLeftPath;

            if (moveNopPath.size() > 0 && moveNopPath.back().landingMinPoint.getY() > bestPath.back().landingMinPoint.getY())
                bestPath = moveNopPath;

            if (moveRightPath.size() > 0 && moveRightPath.back().landingMinPoint.getY() > bestPath.back().landingMinPoint.getY())
                bestPath = moveRightPath;

            if (moveRotateLeftPath.size() > 0 && moveRotateLeftPath.back().landingMinPoint.getY() > bestPath.back().landingMinPoint.getY())
                bestPath = moveRotateLeftPath;

            if (moveRotateRightPath.size() > 0 && moveRotateRightPath.back().landingMinPoint.getY() > bestPath.back().landingMinPoint.getY())
                bestPath = moveRotateRightPath;

        }

    }
    return bestPath;
}

list<ComputerPlayer::Move> ComputerPlayer::moveNop(Board board)
{
    // Create a move with no operation
    list<Move> bestPath;
    Move moveStep;
    moveStep.move = ComputerPlayer::eMoveType::NOP;
    bestPath.push_front(moveStep);

    // Move down with the no-operation move
    bestPath = moveDown(board, moveStep);

    return bestPath;
}

list<ComputerPlayer::Move> ComputerPlayer::moveLeft(Board board)
{
    // Create a move to the left
    list<Move> bestPath;
    Move moveStep;
    moveStep.move = ComputerPlayer::eMoveType::LEFT;
    bestPath.push_front(moveStep);

    // Move left and recursively build the path
    if (board.getShape().moveLeft())
        bestPath = moveDown(board, moveStep);

    return bestPath;
}

list<ComputerPlayer::Move> ComputerPlayer::moveRight(Board board)
{
    // Create a move to the right
    list<Move> bestPath;
    Move moveStep;
    moveStep.move = ComputerPlayer::eMoveType::RIGHT;
    bestPath.push_front(moveStep);

    // Move right and recursively build the path
    if (board.getShape().moveRight())
        bestPath = moveDown(board, moveStep);

    return bestPath;
}

list<ComputerPlayer::Move> ComputerPlayer::moveRotateLeft(Board board)
{
    // Create a move to rotate left
    list<Move> bestPath;
    Move moveStep;
    moveStep.move = ComputerPlayer::eMoveType::ROTATE_LEFT;
    bestPath.push_front(moveStep);

    // Rotate left and recursively build the path
    if (board.getShape().rotate_CounterClockWise())
        bestPath = moveDown(board, moveStep);

    return bestPath;
}

list<ComputerPlayer::Move> ComputerPlayer::moveRotateRight(Board board)
{
    // Create a move to rotate right
    list<Move> bestPath;
    Move moveStep;
    moveStep.move = ComputerPlayer::eMoveType::ROTATE_RIGHT;
    bestPath.push_front(moveStep);

    // Rotate right and recursively build the path
    if (board.getShape().rotate_ClockWise())
        bestPath = moveDown(board, moveStep);

    return bestPath;
}


list<ComputerPlayer::Move> ComputerPlayer::moveDown(Board board, Move moveStep)
{
    list<Move> bestPath;

    Shape boardShape = board.getShape();
    list<Shape>::iterator itr = oldSite.begin();

    for (; itr != oldSite.end(); ++itr)
        if (itr->samePlace(boardShape))
            return list<Move>();

    oldSite.push_back(board.getShape());

    bool moveDown = board.getShape().moveDown();


    // Check if the shape can move down
    if (board.getShape().canMoveDown())
    {
        // If yes, continue with the recursive call
        bestPath = buildPath(board);
    }

    else // Stopping condition
    {
        Shape shape = board.getShape();
        board.updateMatrixWithZeros(shape);
        int completedRows = board.identifyCompletedRows();
        moveStep.numOfRowsDeleted = completedRows;
        moveStep.landingMinPoint = shape.getYminPoint();
        moveStep.numOflandingMinPoints = shape.getYPointCount(moveStep.landingMinPoint);
        moveStep.landingMaxPoint = shape.getYmaxPoint();
        moveStep.numOflandingMaxPoints = shape.getYPointCount(moveStep.landingMinPoint);

    }
    bestPath.push_front(moveStep);

    return bestPath;
}