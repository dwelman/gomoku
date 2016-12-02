#include <gomoku.h>

//
// Created by Dean DU TOIT on 11/29/16.
//

void	drawTitle(t_env *env)
{
	char xo;

	getmaxyx(stdscr, env->maxY, env->maxX);
	wattron(env->win_stats, COLOR_PAIR(4));
	if (env->debug == 1)
	{
		mvwprintw(env->win_stats, 0, 0, "DEBUG MODE ACTIVATED!");
		mvwprintw(env->win_stats, 1, 0, "SELECT ACTIVE PLAYER WITH '1' or '2'");
		mvwprintw(env->win_stats, 0, 55, "Screen size : %04d x %04d", env->maxX, env->maxY);
	}
	if (env->maxX < 90 || env->maxY < 65)
		wclear(env->win_stats);
	mvwprintw(env->win_stats, 2, 0, "%s\n%s", "     ___  _____________  ____ \n"
			"    / _ \\/ __/_  __/ _ \\/ __ \\\n"
			"   / , _/ _/  / / / , _/ /_/ /\n"
			"  /_/|_/___/ /_/ /_/|_|\\____/ \n"
			"                             ", "   ________  ________  _____ ______   ________  ___  __    ___  ___     \n"
					  "  |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\   __  \\|\\  \\|\\  \\ |\\  \\|\\  \\    \n"
					  "  \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\\\\\  \\   \n"
					  "   \\ \\  \\  __\\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\ \\  \\\\\\  \\ \\   ___  \\ \\  \\\\\\  \\  \n"
					  "    \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\ \n"
					  "     \\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\\n"
					  "      \\|_______|\\|_______|\\|__|     \\|__|\\|_______|\\|__| \\|__|\\|_______|");
	wattroff(env->win_stats, COLOR_PAIR(4));
	wattron(env->win_stats, WA_BLINK);
	if (env->gameStarted == true)
	{
		if (env->player == 1)
		{
			xo = 'O';
			wattron(env->win_stats, COLOR_PAIR(5));
		}
		else
		{
			xo = 'X';
			wattron(env->win_stats, COLOR_PAIR(6));
		}
		mvwprintw(env->win_stats, 20, 32, "PLAYER %d (%c) MAKE A MOVE...", env->player, xo);
		wattroff(env->win_stats, WA_BLINK);
		wattron(env->win_stats, COLOR_PAIR(5));
		mvwprintw(env->win_stats, 15, 0, "+-----------------------------+");
		mvwprintw(env->win_stats, 16, 0, "| %-28s|", "Player 1");
		mvwprintw(env->win_stats, 17, 0, "| Captures : %-17d|", env->player1->getCaptures());
		mvwprintw(env->win_stats, 18, 0, "| Last move timer : %7ldms |", env->p1_time);
		mvwprintw(env->win_stats, 19, 0, "+_____________________________+", env->player);
		wattron(env->win_stats, COLOR_PAIR(6));
		mvwprintw(env->win_stats, 15, 59, "+-----------------------------+");
		mvwprintw(env->win_stats, 16, 59, "| %-28s|", "Player 2");
		mvwprintw(env->win_stats, 17, 59, "| Captures : %-17d|", env->player2->getCaptures());
		mvwprintw(env->win_stats, 18, 59, "| Last move timer : %7ldms |", env->p2_time);
		mvwprintw(env->win_stats, 19, 59, "+_____________________________+", env->player);
	}
	wattroff(env->win_stats, WA_BLINK);
	wattron(env->win_stats, COLOR_PAIR(6));
	if (env->placeRet == -1)
		mvwprintw(env->win_stats, 14 , 0, "INVALID MOVE!");
	else
	{
		wmove(env->win_stats, 14, 0);
		wclrtoeol(env->win_stats);
	}
	wattroff(env->win_stats, WA_BLINK);

}