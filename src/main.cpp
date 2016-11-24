#include <gomoku.h>

int	main()
{
	Board	*gameBoard;

	gameBoard = new Board(BOARD_DIM);
	gameBoard->printBoard();
}