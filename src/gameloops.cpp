//
// Created by Dean DU TOIT on 12/6/16.
//

#include <gomoku.h>

bool	playerAILoop(t_env *env, Board *gameBoard)
{
	chrono::high_resolution_clock::time_point	start_time;
	int		*coord; //free?
	int		topScore;
	int		value;
	int		bestCoord[2];
	int		curCount;
	bool	done;
	int		**valTemp;
	int		**boardTemp;
	int		tempCaps;
	vector<int *>	coords;

	valTemp = (int **)malloc(sizeof(int *) * BOARD_DIM);
	for (int y = 0; y < BOARD_DIM; y++)
	{
		valTemp[y] = (int *)malloc(sizeof(int) * BOARD_DIM);
		for (int x = 0; x < BOARD_DIM; x++)
		{
			valTemp[y][x] = 0;
		}
	}
	boardTemp = (int **)malloc(sizeof(int *) * BOARD_DIM);
	for (int y = 0; y < BOARD_DIM; y++)
	{
		boardTemp[y] = (int *)malloc(sizeof(int) * BOARD_DIM);
		for (int x = 0; x < BOARD_DIM; x++)
		{
			boardTemp[y][x] = 0;
		}
	}
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
			env->placeRet = -1;
			curCount = 0;
			topScore = -1000;
			bestCoord[0] = 0;
			bestCoord[1] = 0;
			coords = env->valBoard->fetchTiles();
			while (curCount < coords.size())
			{
				gameBoard->copyBoard(boardTemp);
				tempCaps = env->player2->getCaptures();
				//env->placeRet = gameBoard->placePiece(coords.at(curCount)[0], coords.at(curCount)[1], env->player2);
				value = minimax(gameBoard, env->valBoard, env->player2, env->player1, 0, 0, 2, 1);
				//cout << value << endl;
				if (value > topScore)
				{
					env->placeRet = gameBoard->placePiece(coords.at(curCount)[1], coords.at(curCount)[2], env->player2);
					env->player2->setCaptures(tempCaps);
					gameBoard->setBoard(boardTemp);
					if (env->placeRet != -1)
					{
						topScore = value;
						bestCoord[0] = coords.at(curCount)[1];
						bestCoord[1] = coords.at(curCount)[2];
					}
				}
				/*if (env->placeRet != -1)
				{
					env->valBoard->copyBoard(valTemp);
					if (env->placeRet == 1)
						env->valBoard->placePiece(coords.at(curCount)[0], coords.at(curCount)[1], gameBoard, true);
					else
						env->valBoard->placePiece(coords.at(curCount)[0], coords.at(curCount)[1], gameBoard, false);
					value = minimax(gameBoard, env->valBoard, env->player2, 1, 5);
					if (value > topScore)
					{
						topScore = value;
						bestCoord[0] = coords.at(curCount)[0];
						bestCoord[1] = coords.at(curCount)[1];
					}
					env->player2->setCaptures(tempCaps);
					env->valBoard->setBoard(valTemp);
					gameBoard->setBoard(boardTemp);
				}*/
				curCount++;
			}
			//cout << "y = " << bestCoord[0] + 1 << " x = " << bestCoord[1] + 1 << endl;
			env->placeRet = gameBoard->placePiece(bestCoord[0], bestCoord[1], env->player2);
			/*while (env->placeRet == -1)
			{
				coord = env->player2->getBestMove(gameBoard, env->valBoard, &curCount);
				mvwprintw(env->win_stats, 20, 64, "Y = %d, X = %d, Val = %d", coord[0] + 1, coord[1] + 1, gameBoard->getBoard()[coord[0]][coord[2]]);
				env->placeRet = gameBoard->placePiece(coord[0], coord[1], env->player2);
			}*/
			auto end_time = chrono::high_resolution_clock::now();
			auto time = end_time - start_time;
			env->p2_time = chrono::duration_cast<chrono::milliseconds>(time).count();
			//mvwprintw(env->win_stats, 20, 64, "Y = %d, X = %d, Ret = %d", coord[0] - 1, coord[1] - 1, env->placeRet);
			if (env->placeRet == 1)
				env->valBoard->placePiece(bestCoord[0], bestCoord[1], gameBoard, true);
			else
				env->valBoard->placePiece(bestCoord[0], bestCoord[1], gameBoard, false);
			if (env->placeRet != 2)
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
	return (playerWon(env, gameBoard));
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
	return (playerWon(env, gameBoard));
}