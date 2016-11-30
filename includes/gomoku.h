#pragma once

class	Board;

#include <string>
#include <ctime>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <Board.class.h>
#include <Player.class.h>
#include <chrono>

#define X_OFF 5
#define Y_OFF 2
#define GM_PVP 1
#define GM_PVAI 2

typedef std::chrono::high_resolution_clock Clock;

typedef struct		s_env
{
	int		gameMode;
	int		debug;
	int		activeX;
	int		activeY;
	int		player;
	int		placeRet;
	WINDOW	*win_board;
	WINDOW	*win_stats;
	int		maxX;
	int		maxY;
	bool	gameStarted;
	bool	validMoveMade;
	Player	*player1;
	Player	*player2;
	long	p1_time;
	long	p2_time;
	double	curTurnStart;
}					t_env;

using namespace std;

#define BOARD_DIM 19

void	keyHook(t_env *env, Board *gameBoard, chrono::high_resolution_clock::time_point start_time);

void	drawTitle(t_env *env);
