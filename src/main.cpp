#include <gomoku.h>

void	initWin(t_env *env)
{
	initscr();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	raw();
	noecho();
	cbreak();
	env->win_board = newwin(45, 90, 22, 2);
	wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	env->win_stats = newwin(21, 90, 0, 2);
	drawTitle(env);
	keypad(env->win_board, TRUE);
	curs_set(0);
	refresh();
	wrefresh(env->win_board);
	wrefresh(env->win_stats);
}

void	initEnv(t_env *env)
{
	env->activeX = 0;
	env->activeY = 0;
	env->player = 1;
	env->placeRet = 0;
	env->gameMode = GM_PVP;
	env->gameStarted = false;
	env->p1_time = 0;
	env->p2_time = 0;
	initWin(env);
	getmaxyx(stdscr, env->maxY, env->maxX);
}

void	refreshAll(t_env *env)
{
	refresh();
	wrefresh(env->win_board);
	wrefresh(env->win_stats);
}

void	menu(t_env *env)
{
	int	winX;
	int	winY;
	int	input;

	getmaxyx(env->win_board, winY, winX);
	input = 0;
	while (input != 10)
	{
		wattron(env->win_board, WA_BOLD | WA_UNDERLINE);
		mvwprintw(env->win_board, winY / 2 + 1 - 3, winX / 2 - 4, "GAME MODE",  env->gameMode);
		wattroff(env->win_board, WA_UNDERLINE);
		if (env->gameMode == GM_PVP)
			wattron(env->win_board, WA_STANDOUT);
		mvwprintw(env->win_board ,winY / 2 + 3 - 3, winX / 2 - 8, "Player vs Player",  env->gameMode);
		wattroff(env->win_board, WA_STANDOUT);
		if (env->gameMode == GM_PVAI)
			wattron(env->win_board, WA_STANDOUT);
		mvwprintw(env->win_board, winY / 2 + 5 - 3, winX / 2 - 6, "Player vs AI",  env->gameMode);
		wattroff(env->win_board, WA_STANDOUT);
		refreshAll(env);
		input = wgetch(env->win_board);
		switch (input)
		{
			case KEY_RIGHT :
			case KEY_DOWN :
			case KEY_LEFT :
			case KEY_UP :
				if (env->gameMode == GM_PVP)
					env->gameMode = GM_PVAI;
				else
					env->gameMode = GM_PVP;
				break ;
			default:
				drawTitle(env);
				wclear(env->win_board);
				wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
		}

	}
}

int		main(int argc, char **argv)
{
	t_env	env;
	Board	*gameBoard;
	Player	*player1;
	Player	*player2;
	int		x;
	int		y;
	int		input;

	env.debug = 0;
	if (argc == 2)
	{
		if (strcmp(argv[1], "-d") == 0)
			env.debug = 1;
	}
	initEnv(&env);
	gameBoard = new Board(BOARD_DIM);
	env.player1 = new Player(1);
	env.player2 = new Player(2);
	menu(&env);
	env.gameStarted = true;
	drawTitle(&env);
	if (env.maxX < 90 || env.maxY < 65)
	{
		wclear(env.win_board);
		mvwprintw(env.win_board, 1, 1, "%s", "Please Enlarge window to view board.");
	}
	else
		gameBoard->printBoardN(env.win_board, env.activeX, env.activeY, X_OFF, Y_OFF);
	refreshAll(&env);
	while (env.placeRet != 1)
	{
		wborder(env.win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
		keyHook(&env, gameBoard);
		if (env.maxX < 90 || env.maxY < 65)
		{
			wclear(env.win_board);
			mvwprintw(env.win_board, 1, 1, "%s", "Please Enlarge window to view board.");
		}
		else
		{
			wmove(env.win_board, 1, 1);
			wclrtoeol(env.win_board);
			gameBoard->printBoardN(env.win_board, env.activeX, env.activeY, X_OFF, Y_OFF);
		}
		drawTitle(&env);
		refreshAll(&env);
	}
	endwin();
}