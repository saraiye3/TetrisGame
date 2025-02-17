
#ifndef __HUMANPLAYER_H
#define __HUMANPLAYER_H

#include <iostream>
#include "board.h"
#include "player.h"

class HumanPlayer : public Player
{
private:
    HumanPlayer::eMoveType moveLeftHuman(int key);
    HumanPlayer::eMoveType moveRightHuman(int key);

public:
    virtual ~HumanPlayer() {};
    virtual void play(int pressedKey) override;
    virtual void makeMove(eMoveType move) override;
    virtual void initPlayer(int min_x, int min_y, ePlayerType playerType) override;
};

#endif
