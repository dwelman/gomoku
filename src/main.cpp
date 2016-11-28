#include <gomoku.h>
//void    printBoardN(WINDOW *w, int activeX, int activeY);

void	drawTitle(WINDOW *win_stats, int player, int error)
{
	char xo;
	wattron(win_stats, COLOR_PAIR(4));
	mvwprintw(win_stats, 0 , 0, "%s\n%s", "   ___  _____________  ____ \n"
			"  / _ \\/ __/_  __/ _ \\/ __ \\\n"
			" / , _/ _/  / / / , _/ /_/ /\n"
			"/_/|_/___/ /_/ /_/|_|\\____/ \n"
			"                           "," ________  ________  _____ ______   ________  ___  __    ___  ___     \n"
					  "|\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\   __  \\|\\  \\|\\  \\ |\\  \\|\\  \\    \n"
					  "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\\\\\  \\   \n"
					  " \\ \\  \\  __\\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\ \\  \\\\\\  \\ \\   ___  \\ \\  \\\\\\  \\  \n"
					  "  \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \n"
					  "   \\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\\n"
					  "    \\|_______|\\|_______|\\|__|     \\|__|\\|_______|\\|__| \\|__|\\|_______|");
	wattroff(win_stats, COLOR_PAIR(4));
	wattron(win_stats, WA_BLINK);
	if (player == 1)
		xo = 'O';
	else
		xo = 'X';
	mvwprintw(win_stats, 13 , 0, "PLAYER %d (%c) MAKE A MOVE...",  player, xo);
	wattroff(win_stats, WA_BLINK);
	wattron(win_stats, COLOR_PAIR(6));
	if (error == -1)
		mvwprintw(win_stats, 14 , 0, "INVALID MOVE!");
	else
	{
		wmove(win_stats, 14, 0);
		wclrtoeol(win_stats);
	}
	wattroff(win_stats, WA_BLINK);

}

void	initWin(WINDOW **win_board, WINDOW **win_stats, int player)
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
	*win_board = newwin(80, 80, 15, 0);
	*win_stats = newwin(16, 80, 0, 0);
	drawTitle(*win_stats, player, 0);
	keypad(*win_board, TRUE);
	curs_set(0);
	refresh();
	wrefresh(*win_board);
	wrefresh(*win_stats);
}


int		main(int argc, char **argv)
{
	t_env	env;
	Board	*gameBoard;
	Player	*player1;
	Player	*player2;
	int		x;
	int		y;
	int		ax;
	int		ay;
	int		player;
	int		ret;
	WINDOW	*win;
	WINDOW	*win_stats;
	int		input;


	if (argc == 2)
	{
		if (strcmp(argv[1], "-d") == 0)
			env.debug = 1;

	}

	gameBoard = new Board(BOARD_DIM);

	player1 = new Player(1);
	player2 = new Player(2);

	ax = 0;
	ay = 0;
	player = 1;
	ret = 0;

	initWin(&win, &win_stats, player);
	gameBoard->printBoardN(win, ax, ay);
	refresh();
	wrefresh(win);
	wrefresh(win_stats);

	int lim = 0;
	ret = 0;
	while (ret != 1)
	{
		input = wgetch(win);
		switch (input)
		{
			case KEY_LEFT :
				if (ax > 0)
					ax--;
				else
					ax = 18;
				break ;
			case KEY_RIGHT :
				if (ax < 18)
					ax++;
				else
					ax = 0;
				break ;
			case KEY_DOWN :
				if (ay < 18)
					ay++;
				else
					ay = 0;
				break ;
			case KEY_UP :
				if (ay > 0)
					ay--;
				else
					ay = 18;
				break ;
			case 10 :
				if (player == 1)
				{
					ret = gameBoard->placePiece(ay, ax , player1);
					if (ret == 0 && !env.debug)
						player = 2;
				}
				else
				{
					ret = gameBoard->placePiece(ay, ax , player2);
					if (ret == 0 && !env.debug)
						player = 1;
				}
				break ;
			case 27 :
				mvwprintw(win_stats, 14 , 0, "ESC Pressed");
				delwin(win);
				delwin(win_stats);
				endwin();
				exit(1);
			case '1' :
				if (env.debug == 1)
					player = 1;
				break ;
			case '2' :
				if (env.debug == 1)
					player = 2;
				break ;
			default:
				break;
		}
		gameBoard->printBoardN(win, ax, ay);
		drawTitle(win_stats, player, ret);
		refresh();
		wrefresh(win);
		wrefresh(win_stats);
	}
	endwin();
}