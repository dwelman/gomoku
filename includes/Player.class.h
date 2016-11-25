#pragma once

#include <gomoku.h>

class	Player
{
	public:
		Player(int playerNum);

		int		getPlayerNum(){ return (this->playerNum); }
		int		getCaptures(){ return (this->captures); }

		void	incCaptures(){ this->captures++; }

	private:
		int		playerNum;
		int		captures;
};