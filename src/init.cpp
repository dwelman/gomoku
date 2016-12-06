//
// Created by Dean DU TOIT on 12/2/16.
//

#include <gomoku.h>

void	refreshAll(t_env *env)
{
	refresh();
	wrefresh(env->win_board);
	wrefresh(env->win_stats);
	wrefresh(env->win_debug);
}

void	initWin(t_env *env)
{
	initscr();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_GREEN , COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	raw();
	noecho();
	cbreak();
	env->win_board = newwin(45, 90, 22, 2);
	wborder(env->win_board, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	env->win_stats = newwin(21, 90, 0, 2);
	env->win_debug = newwin(45, 90, 22, 92);
	drawTitle(env);
	keypad(env->win_board, TRUE);
	curs_set(0);
	refreshAll(env);
}

void	initEnv(t_env *env)
{
	env->activeX = 0;
	env->activeY = 0;
	env->player1 = new Player(1);
	env->player2 = new Player(2);
	env->player = 1;
	env->placeRet = 0;
	env->gameMode = GM_PVP;
	env->gameStarted = false;
	env->p1_time = 0;
	env->p2_time = 0;
	env->validMoveMade = true;
	initWin(env);
	getmaxyx(stdscr, env->maxY, env->maxX);
}