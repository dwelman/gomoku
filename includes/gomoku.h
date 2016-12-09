#pragma once

class	Board;
class	ValBoard;

#include <string>
#include <ctime>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <Board.class.h>
#include <Player.class.h>
#include <ValBoard.class.h>
#include <chrono>

#define X_OFF 5
#define Y_OFF 2
#define GM_PVP 1
#define GM_PVAI 2
#define BOARD_DIM 19

typedef std::chrono::high_resolution_clock Clock;

typedef struct		s_env
{
	int			gameMode;
	bool		debug;
	int			activeX;
	int			activeY;
	int			player;
	int			placeRet;
	WINDOW		*win_board;
	WINDOW		*win_stats;
	WINDOW		*win_debug;
	int			maxX;
	int			maxY;
	bool		gameStarted;
	bool		validMoveMade;
	Player		*player1;
	Player		*player2;
	ValBoard	*valBoard;
	long		p1_time;
	long		p2_time;
	double		curTurnStart;
}					t_env;

using namespace std;

void	keyHook(t_env *env, Board *gameBoard, chrono::high_resolution_clock::time_point start_time);

void	drawTitle(t_env *env);

void	refreshAll(t_env *env);

void	initWin(t_env *env);

void	initEnv(t_env *env);

void	cleanup(t_env *env);

bool	playerAILoop(t_env *env, Board *gameBoard);

bool	playerVPlayer(t_env *env, Board *gameBoard);

bool	playerWon(t_env *, Board *gameBoard);

void	menu(t_env *env);

void	howToPlay(t_env *env);

int		minimax(Board *gameBoard, ValBoard *valBoard, Player *player, Player *otherPlayer, int alpha, int beta, int playerNum, int depth);
