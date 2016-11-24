#pragma once

#include <gomoku.h>

class	Player
{
	public:
		int		getPlayerNum(){ return (this->playerNum); }

	private:
		int		playerNum;

		int		returnFreeThrees(int y, int x, int playerNum);
};