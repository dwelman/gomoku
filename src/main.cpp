#include <gomoku.h>

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
	input = wgetch(env->win_board);
	cout << "input bef = " << input << endl;
	while (input != 110 && input != 121)
	{
		if (input == 110)
			ret = false;
		else if (input == 121)
			ret = true;
		else
			input = wgetch(env->win_board);
		cout << "input = " << input << endl;
	}
	cout << "ret = " << ret << endl;
	return (ret);
}

bool	playerAILoop(t_env *env, Board *gameBoard)
{
	chrono::high_resolution_clock::time_point	start_time;
	int		*coord; //free?

	while (env->placeRet != 2)
	{
		wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
		if (env->validMoveMade == true)
			start_time = chrono::high_resolution_clock::now();
		//Some if statement 
		if (env->player == 1)
			keyHook(env, gameBoard, start_time);
		else
		{
			//AI make move
			coord = env->player2->getBestMove(gameBoard, env->valBoard);
			mvwprintw(env->win_stats, 20, 64, "Y = %d, X = %d, Val = %d", coord[0] + 1, coord[1] + 1, gameBoard->getBoard()[coord[0]][coord[2]]);
			env->placeRet = gameBoard->placePiece(coord[0], coord[1], env->player2);
			//mvwprintw(env->win_stats, 20, 64, "Y = %d, X = %d, Ret = %d", coord[0] - 1, coord[1] - 1, env->placeRet);
			env->valBoard->placePiece(coord[0], coord[1], gameBoard);
			env->player = 1;
		}
		if (env->maxX < 90 || env->maxY < 65)
		{
			wclear(env->win_board);
			mvwprintw(env->win_board, 1, 1, "%s", "Please Enlarge window to view board.");
		}
		else
		{
			wmove(env->win_board, 1, 1);
			wclrtoeol(env->win_board);
			gameBoard->printBoardN(env->win_board, env->activeX, env->activeY, X_OFF, Y_OFF);
			if (env->debug == true)
				env->valBoard->printBoardN(env->win_debug, X_OFF, Y_OFF);

		}
		drawTitle(env);
		refreshAll(env);
	}
	return (playerWon(env));
}


bool	playerVPlayer(t_env *env, Board *gameBoard)
{
	chrono::high_resolution_clock::time_point	start_time;

	while (env->placeRet != 2)
	{
		wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
		if (env->validMoveMade == true)
			start_time = chrono::high_resolution_clock::now();
		keyHook(env, gameBoard, start_time);
		if (env->maxX < 90 || env->maxY < 65)
		{
			wclear(env->win_board);
			mvwprintw(env->win_board, 1, 1, "%s", "Please Enlarge window to view board.");
		}
		else {
			wmove(env->win_board, 1, 1);
			wclrtoeol(env->win_board);
			gameBoard->printBoardN(env->win_board, env->activeX, env->activeY, X_OFF, Y_OFF);
		}
		drawTitle(env);
		refreshAll(env);
	}
	return (playerWon(env));
}

int		main(int argc, char **argv)
{
	t_env		env;
	Board		*gameBoard;
	ValBoard	*valBoard;
	bool		exit;

	exit = false;
	env.debug = false;
	if (argc == 2)
	{
		if (strcmp(argv[1], "-d") == 0)
			env.debug = true;
	}
	do {
		cout << "RESTARTING ..." << endl;
		initEnv(&env);
		gameBoard = new Board(BOARD_DIM);
		env.valBoard = new ValBoard(BOARD_DIM);
		//env.valBoard = valBoard; //Why ?
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
	while (!exit);
	endwin();
}

//CHECK FOR STALEMATE