#include "Game.h"


Game::Game()
{
	this->player1 = Player(PlayerType::human, ChessmanType::Black);
	this->player2 = Player(PlayerType::human, ChessmanType::Black);
}

Game::~Game()
{
}

/**
* @brief	����player1ָ��
* @param	void
* @return	player1��ָ��
*/
Player* Game::getPlayerOne()
{
	return (&this->player1);
}


/**
* @brief	����player2ָ��
* @param	void
* @return	player2��ָ��
*/
Player* Game::getPlayerTwo()
{
	return (&this->player2);
}