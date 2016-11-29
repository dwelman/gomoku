#include <gomoku.h>
//void    printBoardN(WINDOW *w, int activeX, int activeY);

void	drawTitle(t_env *env) {
	char xo;

	getmaxyx(stdscr, env->maxY, env->maxX);
	wattron(env->win_stats, COLOR_PAIR(4));
	if (env->debug == 1) {
		mvwprintw(env->win_stats, 0, 0, "DEBUG MODE ACTIVATED!");
		mvwprintw(env->win_stats, 0, 55, "Screen size : %04d x %04d", env->maxX, env->maxY);
	}
	if (env->maxX < 90 || env->maxY < 65)
		wclear(env->win_stats);
	mvwprintw(env->win_stats, 1, 0, "%s\n%s", "   ___  _____________  ____ \n"
			"  / _ \\/ __/_  __/ _ \\/ __ \\\n"
			" / , _/ _/  / / / , _/ /_/ /\n"
			"/_/|_/___/ /_/ /_/|_|\\____/ \n"
			"                           ", " ________  ________  _____ ______   ________  ___  __    ___  ___     \n"
					  "|\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\   __  \\|\\  \\|\\  \\ |\\  \\|\\  \\    \n"
					  "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\\\\\  \\   \n"
					  " \\ \\  \\  __\\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\ \\  \\\\\\  \\ \\   ___  \\ \\  \\\\\\  \\  \n"
					  "  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \n"
					  "   \\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\\n"
					  "    \\|_______|\\|_______|\\|__|     \\|__|\\|_______|\\|__| \\|__|\\|_______|");
	wattroff(env->win_stats, COLOR_PAIR(4));
	wattron(env->win_stats, WA_BLINK);
	if (env->player == 1)
	{
		xo = 'O';
		wattron(env->win_stats, COLOR_PAIR(5));
	}
	else
	{
		xo = 'X';
		wattron(env->win_stats, COLOR_PAIR(6));
	}
	mvwprintw(env->win_stats, 20, 0, "PLAYER %d (%c) MAKE A MOVE...",  env->player, xo);
	wattroff(env->win_stats, WA_BLINK);
	wattron(env->win_stats, COLOR_PAIR(6));
	if (env->placeRet == -1)
		mvwprintw(env->win_stats, 14 , 0, "INVALID MOVE!");
	else
	{
		wmove(env->win_stats, 14, 0);
		wclrtoeol(env->win_stats);
	}
	wattroff(env->win_stats, WA_BLINK);

}

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
	env->win_board = newwin(45, 90, 22, 0);
	wborder(env->win_board, '|', '|', '-', '-', '+', '+', '+', '+');
	env->win_stats = newwin(21, 90, 0, 0);
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
	initWin(env);
	getmaxyx(stdscr, env->maxY, env->maxX);
}

void	keyHook(t_env *env, Board *gameBoard, Player *player1, Player *player2)
{
	int		input;

	input = wgetch(env->win_board);

	switch (input)
	{
		case KEY_LEFT :
			if (env->activeX > 0)
				env->activeX--;
			else
				env->activeX = 18;
			break ;
		case KEY_RIGHT :
			if (env->activeX < 18)
				env->activeX++;
			else
				env->activeX = 0;
			break ;
		case KEY_DOWN :
			if (env->activeY < 18)
				env->activeY++;
			else
				env->activeY = 0;
			break ;
		case KEY_UP :
			if (env->activeY > 0)
				env->activeY--;
			else
				env->activeY = 18;
			break ;
		case 10 :
			if (env->player == 1)
			{
				env->placeRet = gameBoard->placePiece(env->activeY, env->activeX , player1);
				if (env->placeRet == 0 && !env->debug)
					env->player = 2;
			}
			else
			{
				env->placeRet = gameBoard->placePiece(env->activeY, env->activeX , player2);
				if (env->placeRet == 0 && !env->debug)
					env->player = 1;
			}
			break ;
		case 27 :
			mvwprintw(env->win_stats, 14 , 0, "ESC Pressed");
			delwin(env->win_board);
			delwin(env->win_stats);
			endwin();
			exit(1);
		case '1' :
			if (env->debug == 1)
				env->player = 1;
			break ;
		case '2' :
			if (env->debug == 1)
				env->player = 2;
			break ;
		default:
			wclear(env->win_board);
			break;
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
	player1 = new Player(1);
	player2 = new Player(2);
	if (env.maxX < 90 || env.maxY < 65)
	{
		wclear(env.win_board);
		mvwprintw(env.win_board, 1, 1, "%s", "Please Enlarge window to view board.");
	}
	else
		gameBoard->printBoardN(env.win_board, env.activeX, env.activeY, X_OFF, Y_OFF);
	refresh();
	wrefresh(env.win_board);
	wrefresh(env.win_stats);
	while (env.placeRet != 1)
	{
		wborder(env.win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
		keyHook(&env, gameBoard, player1, player2);
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
		refresh();
		wrefresh(env.win_board);
		wrefresh(env.win_stats);
	}
	endwin();
}