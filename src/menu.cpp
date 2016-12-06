//
// Created by Dean DU TOIT on 12/6/16.
//

#include <gomoku.h>

void	menu(t_env *env) {
	int winX;
	int winY;
	int input;
	int selection;
	bool breakLoop;

	getmaxyx(env->win_board, winY, winX);
	input = 0;
	selection = 1;
	breakLoop = false;
	while (input != 10) {
		wattron(env->win_board, WA_BOLD | WA_UNDERLINE);
		mvwprintw(env->win_board, winY / 2 + 1 - 3, winX / 2 - 4, "GAME MODE");
		wattroff(env->win_board, WA_UNDERLINE);

		if (selection == 1)
			wattron(env->win_board, WA_STANDOUT);
		mvwprintw(env->win_board, winY / 2 + 3 - 3, winX / 2 - 8, "Player vs Player");
		wattroff(env->win_board, WA_STANDOUT);

		if (selection == 2)
			wattron(env->win_board, WA_STANDOUT);
		mvwprintw(env->win_board, winY / 2 + 5 - 3, winX / 2 - 6, "Player vs AI");
		wattroff(env->win_board, WA_STANDOUT);

		if (selection == 3)
			wattron(env->win_board, WA_STANDOUT);
		mvwprintw(env->win_board, winY / 2 + 7 - 3, winX / 2 - 6, "How to Play");
		wattroff(env->win_board, WA_STANDOUT);

		refreshAll(env);
		input = wgetch(env->win_board);
		refreshAll(env);
		switch (input) {
			case KEY_RIGHT :
			case KEY_DOWN :
				if (selection == 3)
					selection = 1;
				else
					selection++;
				break;
			case KEY_LEFT :
			case KEY_UP :
				if (selection == 1)
					selection = 3;
				else
					selection--;
				break;
			default:
				drawTitle(env);
				wclear(env->win_board);
				wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER,
						ACS_LLCORNER, ACS_LRCORNER);
		}
	}
	switch (selection) {
		case 1 :
			env->gameMode = GM_PVP;
			breakLoop = true;
			break;
		case 2 :
			env->gameMode = GM_PVAI;
			breakLoop = true;
			break;
		default :
			breakLoop = false;
			howToPlay(env);
	}
}

void	howToPlay(t_env *env)
{
	int	input;
	int	winX;
	int	winY;

	wclear(env->win_board);
	wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	getmaxyx(env->win_board, winY, winX);
	wattron(env->win_board, WA_BOLD | WA_UNDERLINE);
	mvwprintw(env->win_board, 1, winX / 2 - 5, "HOW TO PLAY");
	mvwprintw(env->win_board, 2, 2, "Controls :");
	wattroff(env->win_board, WA_BOLD | WA_UNDERLINE);
	mvwprintw(env->win_board, 3, 3, "- Arrow keys to navigate the board.");
	mvwprintw(env->win_board, 4, 3, "- Enter (return) key to place a piece.");
	wattron(env->win_board, WA_BOLD | WA_UNDERLINE);
	mvwprintw(env->win_board, 6, 2, "Game loop:");
	wattroff(env->win_board, WA_BOLD | WA_UNDERLINE);
	mvwprintw(env->win_board, 7, 3, "Players take turns placing pieces in an attempt to reach a win condition :");
	mvwprintw(env->win_board, 8, 3, "- Get 5 pieces in a row or by getting 5 flanks. ");
	mvwprintw(env->win_board, 9, 3, "- Get 5 flanks / captures (see next section on captures).");
	wattron(env->win_board, WA_BOLD | WA_UNDERLINE);
	mvwprintw(env->win_board, 11, 2, "Captures :");
	wattroff(env->win_board, WA_BOLD | WA_UNDERLINE);
	mvwprintw(env->win_board, 12, 3, "A player can capture another players pieces if the player can place a piece on either");
	mvwprintw(env->win_board, 13, 3, "side of aligning pieces of the opposing player. Capturing pieces will remove them");
	mvwprintw(env->win_board, 14, 3, "from the board. This works diagonally, horizontally or vertically");
	mvwprintw(env->win_board, 16, 3, "Example :");
	mvwprintw(env->win_board, 17, 3, "X can place a piece on 5 and will result in a capture");
	mvwprintw(env->win_board, 18, 3, "1 2 3 4 5     . . . . .");
	mvwprintw(env->win_board, 18, 3, ". X O O .  >> . X . . X");
	input = wgetch(env->win_board);
	wclear(env->win_board);
	wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	menu(env);
}