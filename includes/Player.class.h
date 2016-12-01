#pragma once

#include <gomoku.h>

class	Player
{
	public:
		Player(int playerNum);

		int		getPlayerNum(){ return (this->playerNum); }
		int		getCaptures(){ return (this->captures); }

		void	incCaptures(int val){ this->captures += val; }

	private:
		int		playerNum;
		int		captures;
};