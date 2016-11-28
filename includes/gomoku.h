#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <Board.class.h>
#include <Player.class.h>

typedef struct		s_env
{
	int		debug;
}					t_env;

using namespace std;

#define BOARD_DIM 19