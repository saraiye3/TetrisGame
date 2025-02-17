#include "humanPlayer.h"

void HumanPlayer::initPlayer(int min_x, int min_y, ePlayerType playerType)
{
	this->board.initBoard(min_x, min_y);
	this->playerType = playerType;
}

void HumanPlayer::play(int pressedKey)
{

	HumanPlayer::eMoveType move=HumanPlayer::eMoveType::NOP;

	if (this->playerType == ePlayerType::LEFT_HUMAN)
	{
		move = moveLeftHuman(pressedKey);
	}
	else if (this->playerType == ePlayerType::RIGHT_HUMAN)
	{
		move = moveRightHuman(pressedKey);
	}
	
	makeMove(move);
}

HumanPlayer::eMoveType HumanPlayer::moveLeftHuman(int pressedKey)
{

	switch (pressedKey)
	{
	case (int)GameConfig::eKeys::BA_LEFT:
	case (int)GameConfig::eKeys::BA_LEFT - (int)GameConfig::UPPER_CASE:
		return eMoveType::LEFT;

	case (int)GameConfig::eKeys::BA_RIGHT:
	case (int)GameConfig::eKeys::BA_RIGHT - (int)GameConfig::UPPER_CASE:
		return eMoveType::RIGHT;

	case (int)GameConfig::eKeys::BA_ROTATE_CLOCKWISE:
	case (int)GameConfig::eKeys::BA_ROTATE_CLOCKWISE - (int)GameConfig::UPPER_CASE:
		return eMoveType::ROTATE_RIGHT;

	case (int)GameConfig::eKeys::BA_ROTATE_COUNTER_CLOCKWISE:
	case (int)GameConfig::eKeys::BA_ROTATE_COUNTER_CLOCKWISE - (int)GameConfig::UPPER_CASE:
		return eMoveType::ROTATE_LEFT;

	case (int)GameConfig::eKeys::BA_DROP:
	case (int)GameConfig::eKeys::BA_DROP - (int)GameConfig::UPPER_CASE:
		return eMoveType::DROP;

	default:
		return eMoveType::NOP;

	}
}

HumanPlayer::eMoveType HumanPlayer::moveRightHuman(int pressedKey)
{
	
	switch (pressedKey)
	{
	case (int)GameConfig::eKeys::BB_LEFT:
	case (int)GameConfig::eKeys::BB_LEFT - (int)GameConfig::UPPER_CASE:
		return eMoveType::LEFT;

	case (int)GameConfig::eKeys::BB_RIGHT:
	case (int)GameConfig::eKeys::BB_RIGHT - (int)GameConfig::UPPER_CASE:
		return eMoveType::RIGHT;

	case (int)GameConfig::eKeys::BB_ROTATE_CLOCKWISE:
	case (int)GameConfig::eKeys::BB_ROTATE_CLOCKWISE - (int)GameConfig::UPPER_CASE:
		return eMoveType::ROTATE_RIGHT;

	case (int)GameConfig::eKeys::BB_ROTATE_COUNTER_CLOCKWISE:
	case (int)GameConfig::eKeys::BB_ROTATE_COUNTER_CLOCKWISE - (int)GameConfig::UPPER_CASE:
		return eMoveType::ROTATE_LEFT;

	case (int)GameConfig::eKeys::BB_DROP:
	case (int)GameConfig::eKeys::BB_DROP - (int)GameConfig::UPPER_CASE:
		return eMoveType::DROP;

	default:
		return eMoveType::NOP;

	}
}

void HumanPlayer::makeMove(HumanPlayer::eMoveType move)
{
	switch (move)
	{
	case HumanPlayer::eMoveType::LEFT:
		board.getShape().moveLeft();
		break;
	case HumanPlayer::eMoveType::RIGHT:
		board.getShape().moveRight();
		break;
	case HumanPlayer::eMoveType::ROTATE_LEFT:
		board.getShape().rotate_CounterClockWise();
		break;
	case HumanPlayer::eMoveType::ROTATE_RIGHT:
		board.getShape().rotate_ClockWise();
		break;
	case HumanPlayer::eMoveType::DROP:
		board.getShape().drop();
		break;
	case HumanPlayer::eMoveType::NOP:
		break;

	}
}

