#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <Board.class.h>
#include <Player.class.h>

#define X_OFF 5
#define Y_OFF 2

typedef struct		s_env
{
	int		debug;
	int		activeX;
	int		activeY;
	int		player;
	int		placeRet;
	WINDOW	*win_board;
	WINDOW	*win_stats;
	int		maxX;
	int		maxY;
}					t_env;

using namespace std;

#define BOARD_DIM 19