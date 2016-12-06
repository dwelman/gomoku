//
// Created by Dean DU TOIT on 12/6/16.
//

#include <gomoku.h>

bool	playerAILoop(t_env *env, Board *gameBoard)
{
	chrono::high_resolution_clock::time_point	start_time;
	int		*coord; //free?
	int		curMove;

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
			curMove = 0;
			while (env->placeRet == -1)
			{
				coord = env->player2->getBestMove(gameBoard, env->valBoard, &curMove);
				mvwprintw(env->win_stats, 20, 64, "Y = %d, X = %d, Val = %d", coord[0] + 1, coord[1] + 1, gameBoard->getBoard()[coord[0]][coord[2]]);
				env->placeRet = gameBoard->placePiece(coord[0], coord[1], env->player2);
			}
			auto end_time = chrono::high_resolution_clock::now();
			auto time = end_time - start_time;
			env->p2_time = chrono::duration_cast<chrono::milliseconds>(time).count();
			//mvwprintw(env->win_stats, 20, 64, "Y = %d, X = %d, Ret = %d", coord[0] - 1, coord[1] - 1, env->placeRet);
			if (env->placeRet == 1)
				env->valBoard->placePiece(coord[0], coord[1], gameBoard, true);
			else
				env->valBoard->placePiece(coord[0], coord[1], gameBoard, false);
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