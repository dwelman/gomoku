#pragma once

#include <gomoku.h>

using namespace std;

class ValBoard
{
	public:
		ValBoard();
		ValBoard(int boardDim);
		ValBoard(const ValBoard &obj);

		int		getBoardDim(){ return (this->boardDim); }
		int		**getBoard(){ return (this->board); }

		void			setBoard(int **newArr);
		void			copyBoard(int **newArr);
		void			setVal(int y, int x, int val){ this->board[y][x] = val; }
		void			placePiece(int y, int x, Board *curBoard, bool wasFlank);
		void			removePiece(int y, int x, Board *curBoard);
		vector<int*>	fetchTiles();
		void			printBoardN(WINDOW *w, int xOff, int yOff);


private:
		int		boardDim;
		int		**board;

		void	markFlanks(int y, int x, int playerNum, int **curBoard);
		void	unmarkFlanks(int y, int x, int playerNum, Board *curBoard);
		void	markFreeThrees(int y, int x, int playerNum, int **curBoard);
		void	markVictory(int y, int x, int playerNum, int **curBoard);
};