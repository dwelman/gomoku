//
// Created by Dean DU TOIT on 11/28/16.
//
#include <Board.class.h>
//int mvwprintw(WINDOW *win, int y, int x, const char *fmt, ...);

void	Board::printBoardN(WINDOW *w, int activeX, int activeY)
{
	char	temp[20];
	int		xpos;
	//static int	activeX = 1;
	//static int	activeY = 1;

	xpos = 0;


	wattron(w, COLOR_PAIR(1));
	for (int k = 0; k <= boardDim; k++)
	{
		mvwprintw(w, 1, 2 * xpos, "%-1d ", k );
		if (xpos != 0)
			mvwprintw(w, xpos + 1, 0, "%-1d ", k);
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
			switch (this->board[y][x])
			{
				case 1 :
					wattron(w, COLOR_PAIR(5));
					mvwprintw(w, y * 2 + 3, 2 * xpos + 4, "%-1s ", "O");
					wattroff(w, COLOR_PAIR(5));
					break;
				case 2 :
					wattron(w, COLOR_PAIR(6));
					mvwprintw(w, y * 2 + 3, 2 * xpos + 4, "%-1s ", "X");
					wattroff(w, COLOR_PAIR(6));
					break;
				default:
					mvwprintw(w, y * 2 + 3, 2 * xpos + 4, "%-1s ", ".");
					break;
			}
			wattroff(w, WA_BLINK);
			wattroff(w, WA_STANDOUT);
/*			if (this->board[y][x] == 0)
				mvwprintw(w, y * 2 + 3, 2 * xpos + 4, "%-1s ", ".");
			else
				mvwprintw(w, y * 2 + 3, 2 * xpos + 4, "%-1d ", this->board[y][x]);
*/			xpos += 2;
		}
	}
}
