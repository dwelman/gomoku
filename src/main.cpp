#include <gomoku.h>

bool	playerWon(t_env *env)
{
	int		winX;
	int		winY;
	int		input;
	bool	ret;

	ret = false;
	getmaxyx(env->win_board, winY, winX);
	wclear(env->win_board);
	if (env->player == 1)
		wattron(env->win_board, COLOR_PAIR(5));
	else
		wattron(env->win_board, COLOR_PAIR(6));
	wattron(env->win_board, WA_BLINK);
	mvwprintw(env->win_board ,winY / 2 + 3 - 3, winX / 2 - 8, "Player %d won!",  env->player);
	mvwprintw(env->win_board ,winY / 2 + 3 - 2, winX / 2 - 8, "Play Again ? (Y / N) ",  env->player);
	wattroff(env->win_stats, WA_BLINK);
	wattroff(env->win_board, COLOR_PAIR(4));
	input = 0;
	while (input != 110 && input != 121)
	{
		input = wgetch(env->win_board);
		if (input == 110)
			ret = false;
		else if (input == 121)
			ret = true;
		else
			input = wgetch(env->win_board);
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	t_env		env;
	Board		*gameBoard;
	ValBoard	*valBoard;
	bool		exit;

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
		cout << "exit " << exit << endl;
	}
	while (exit);
	endwin();
}

//CHECK FOR STALEMATE