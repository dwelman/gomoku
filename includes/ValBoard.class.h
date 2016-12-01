#pragma once

#include <gomoku.h>

using namespace std;

class ValBoard
{
	public:
		ValBoard(int boardDim);
		
		int		getBoardDim(){ return (this->boardDim); }

		void			setVal(int y, int x, int val){ this->board[y][x] = val; }
		void			placePiece(int y, int x, Board *curBoard);
		vector<int*>	fetchTiles();

	private:
		int		boardDim;
		int		**board;
};