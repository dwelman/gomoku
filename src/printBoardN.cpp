//
// Created by Dean DU TOIT on 11/28/16.
//
#include <Board.class.h>

void	Board::printBoardN(WINDOW *w, int activeX, int activeY, int xOff, int yOff)
{
	char	temp[20];
	int		xpos;

	xpos = 0;
	wattron(w, COLOR_PAIR(1));
	for (int k = 0; k <= boardDim; k++)
	{
		mvwprintw(w, 1 + yOff, 2 * xpos + xOff, "%-1d ", k );
		if (xpos != 0)
			mvwprintw(w, xpos + 1 + yOff, 0 + xOff, "%-1d ", k);
		xpos += 2;
	}

	wattron(w, COLOR_PAIR(2));
	for (int y = 0; y < boardDim; y++)
	{
		xpos = 0;
		for (int x = 0; x < boardDim; x++) {
			if (x == activeX && y == activeY)
			{
				wattron(w, COLOR_PAIR(3));
				wattron(w, WA_STANDOUT);
				wattron(w, WA_BLINK);
			}
			else
			{
				wattron(w, COLOR_PAIR(2));
				wattroff(w, WA_BLINK);
				wattroff(w, WA_STANDOUT);
			}
			//mvwprintw(w, y * 2 + 3 + yOff, 2 * xpos + 4 + xOff, "%d ", this->board[y][x]);
			switch (this->board[y][x])
			{
				case 1 :
					wattron(w, COLOR_PAIR(5));
					mvwprintw(w, y * 2 + 3 + yOff, 2 * xpos + 4 + xOff, "%-1s ", "O");
					wattroff(w, COLOR_PAIR(5));
					break;
				case 2 :
					wattron(w, COLOR_PAIR(6));
					mvwprintw(w, y * 2 + 3 + yOff, 2 * xpos + 4 + xOff, "%-1s ", "X");
					wattroff(w, COLOR_PAIR(6));
					break;
				default:
					mvwprintw(w, y * 2 + 3 + yOff, 2 * xpos + 4 + xOff, "%-1s ", ".");
					break;
			}
			wattroff(w, WA_BLINK);
			wattroff(w, WA_STANDOUT);
			xpos += 2;
		}
	}
}

void	ValBoard::printBoardN(WINDOW *w, int xOff, int yOff)
{
	char	temp[20];
	int		xpos;

	xpos = 0;
	wattron(w, COLOR_PAIR(1));
	for (int k = 0; k <= boardDim; k++)
	{
		mvwprintw(w, 1 + yOff, 2 * xpos + xOff, "%-1d ", k );
		if (xpos != 0)
			mvwprintw(w, xpos + 1 + yOff, 0 + xOff, "%-1d ", k);
		xpos += 2;
	}
	wattron(w, COLOR_PAIR(2));
	for (int y = 0; y < boardDim; y++)
	{
		xpos = 0;
		for (int x = 0; x < boardDim; x++)
		{
			if (this->board[y][x] == 0)
				wattron(w, COLOR_PAIR(2));
			else
				wattron(w, COLOR_PAIR(4));
			mvwprintw(w, y * 2 + 3 + yOff, 2 * xpos + 4 + xOff, "%3d ", this->board[y][x]);
			xpos += 2;
		}
	}
}