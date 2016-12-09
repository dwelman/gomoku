#include <gomoku.h>

bool	playerWon(t_env *env, Board	*gameBoard)
{
	int		winX;
	int		winY;
	int		input;
	bool	ret;

	wmove(env->win_stats, 20, 32);
	wclear(env->win_stats);
	wclrtoeol(env->win_stats);
	env->gameStarted = false;
	drawTitle(env);
	if (env->player == 1)
		wattron(env->win_stats, COLOR_PAIR(5));
	else
		wattron(env->win_stats, COLOR_PAIR(6));
	wattron(env->win_stats, WA_BLINK);
	mvwprintw(env->win_stats, 20, 29,"Player %d won! Play Again ? (Y / N)",  env->player);
	wattroff(env->win_stats, WA_BLINK);
	wattroff(env->win_board, COLOR_PAIR(4));
	input = 0;
	refreshAll(env);
	while (input != 110 && input != 121)
	{
		input = wgetch(env->win_board);
		ret = false;
		if (input == 110)
			ret = false;
		else if (input == 121)
			ret = true;
		else
		{
			getmaxyx(stdscr, winY, winX);
			wclear(env->win_board);
			if (winX < 90 || winY < 65)
			{
				mvwprintw(env->win_board, 1, 1, "%s", "Please Enlarge window to view board.");
			}
			else
				gameBoard->printBoardN(env->win_board, -1, -1, X_OFF, Y_OFF);
			drawTitle(env);
			wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
			wmove(env->win_stats, 20, 32);
			wclrtoeol(env->win_stats);
			if (env->player == 1)
				wattron(env->win_stats, COLOR_PAIR(5));
			else
				wattron(env->win_stats, COLOR_PAIR(6));
			wattron(env->win_stats, WA_BLINK);
			mvwprintw(env->win_stats, 20, 29,"Player %d won! Play Again ? (Y / N)",  env->player);
			wattroff(env->win_stats, WA_BLINK);
			wattroff(env->win_board, COLOR_PAIR(4));
			refreshAll(env);
			input = wgetch(env->win_board);
		}
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	t_env			env;
	Board			*gameBoard;
	ValBoard		*valBoard;
	bool			exit;

	exit = true;
	env.debug = false;
	if (argc == 2)
	{
		if (strcmp(argv[1], "-d") == 0)
			env.debug = true;
	}
	do {
		initEnv(&env);
		gameBoard = new Board(BOARD_DIM);
		env.valBoard = new ValBoard(BOARD_DIM);
		menu(&env);
		env.gameStarted = true;
		drawTitle(&env);
		if (env.maxX < 90 || env.maxY < 65)
		{
			wclear(env.win_board);
			mvwprintw(env.win_board, 1, 1, "%s", "Please Enlarge window to view board.");
		} else
			gameBoard->printBoardN(env.win_board, env.activeX, env.activeY, X_OFF, Y_OFF);
		refreshAll(&env);
		if (env.gameMode == GM_PVAI)
			exit = playerAILoop(&env, gameBoard);
		else
			exit = playerVPlayer(&env, gameBoard);
	}
	while (exit);
	endwin();
}

//CHECK FOR STALEMATE