//
// Created by Dean DU TOIT on 12/3/16.
//
#include <gomoku.h>

void	cleanup(t_env *env)
{
	delwin(env->win_board);
	delwin(env->win_stats);
	delwin(env->win_debug);
	delete (env->player1);
	delete (env->player2);
	delete (env->valBoard);
	env->gameStarted = false;
}