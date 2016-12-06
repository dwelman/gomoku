#pragma once

#include <gomoku.h>

using namespace std;

class ValBoard
{
	public:
		ValBoard(int boardDim);
		
		int		getBoardDim(){ return (this->boardDim); }

		void			setVal(int y, int x, int val){ this->board[y][x] = val; }
		void			placePiece(int y, int x, Board *curBoard, bool wasFlank);
		vector<int*>	fetchTiles();
		void			printBoardN(WINDOW *w, int xOff, int yOff);


private:
		int		boardDim;
		int		**board;

		void	markFlanks(int y, int x, int playerNum, int **curBoard);
		void	unmarkFlanks(int y, int x, int playerNum, Board *curBoard);
		bool	markVictory(int x, int y, int playerNum, int **curBoard);
};