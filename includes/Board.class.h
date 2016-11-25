#pragma once

#include <gomoku.h>

class   Player;

class	Board
{
    public:
        Board(int boardDim);

        int     getBoardDim(){ return (this->boardDim); }
        int     **getBoard(){ return (this->board); }

        void    printBoard();
        int     placePiece(int y, int x, Player *player);

    private:
        int     boardDim;
        int     **board;

        int		returnFreeThrees(int y, int x, int playerNum);
        void	checkFlanks(int y, int x, Player *player);
        bool    checkVictory(int y, int x, int playerNum);
};