#include <gomoku.h>

//
// Created by Dean DU TOIT on 11/29/16.
//

void	keyHook(t_env *env, Board *gameBoard, chrono::high_resolution_clock::time_point start_time)
{
	int		input;

	input = wgetch(env->win_board);
	env->validMoveMade = false;
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
				env->placeRet = gameBoard->placePiece(env->activeY, env->activeX , env->player1);
				if ((env->placeRet == 0 && !env->debug)
					|| (env->placeRet == 0 && env->debug && env->gameMode == GM_PVAI))
				{
					if (env->placeRet == 1)
						env->valBoard->placePiece(env->activeY, env->activeX, gameBoard, true);
					else
						env->valBoard->placePiece(env->activeY, env->activeX, gameBoard, false);
					if (env->placeRet != 2)
						env->player = 2;
					auto end_time = chrono::high_resolution_clock::now();
					auto time = end_time - start_time;
					env->p1_time = chrono::duration_cast<chrono::milliseconds>(time).count();
					env->validMoveMade = true;
				}
			}
			else
			{
				env->placeRet = gameBoard->placePiece(env->activeY, env->activeX , env->player2);
				if ((env->placeRet == 0 && !env->debug) || env->gameMode == GM_PVAI)
				{
					auto end_time = chrono::high_resolution_clock::now();
					auto time = end_time - start_time;
					env->p2_time = chrono::duration_cast<chrono::milliseconds>(time).count();
					env->player = 1;
					env->validMoveMade = true;
				}
			}
			break ;
		case 27 :
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