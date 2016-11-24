#include <Board.class.h>

Board::Board(int boardDim)
{
	this->boardDim = boardDim;

	this->board = (int **)malloc(sizeof(int *) * boardDim);
	for (int y = 0; y < boardDim; y++)
	{
		this->board[y] = (int *)malloc(sizeof(int) * boardDim);
		for (int x = 0; x < boardDim; x++)
		{
			this->board[y][x] = 0;
		}
	}
}

void	Board::printBoard()
{
	for (int y = 0; y < boardDim; y++)
	{
		for (int x = 0; x < boardDim; x++)
		{
			cout << this->board[y][x] << " ";
		}
		cout << endl;
	}
}

int		returnFreeThrees(int y, int x, int playerNum, int **board, int boardDim)
{
	int	p_y;
	int	p_x;
	int	freeCount;
	int	contCount;

	freeCount = 0;
	contCount = 1;
	for (p_y = y - 5; p_y <= y + 5; p_y++)
	{
		for (p_x = x - 5; p_x <= x + 5; p_x++)
		{
			if (p_y >= 0 && p_y < boardDim && p_x >= 0 && p_x < boardDim)
			{
				if (board[p_y][p_x] == playerNum)
				{
					contCount++;
				}
				else if (board[p_y][p_x] != 0 && contCount > 0)
				{
					contCount = 0;
				}
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 1;
	for (p_y = y + 5; p_y >= y - 5; p_y++)
	{
		for (p_x = x - 5; p_x <= x + 5; p_x++)
		{
			if (p_y >= 0 && p_y < boardDim && p_x >= 0 && p_x < boardDim)
			{
				if (board[p_y][p_x] == playerNum)
				{
					contCount++;
				}
				else if (board[p_y][p_x] != 0 && contCount > 0)
				{
					contCount = 0;
				}
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 1;
	for (p_y = y + 5; p_y >= y - 5; p_y++)
	{
		if (p_y >= 0 && p_y < boardDim)
		{
			if (board[p_y][x] == playerNum)
			{
				contCount++;
			}
			else if (board[p_y][x] != 0 && contCount > 0)
			{
				contCount = 0;
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 1;
	for (p_x = x + 5; p_x >= x - 5; p_x++)
	{
		if (p_x >= 0 && p_x < boardDim)
		{
			if (board[y][p_x] == playerNum)
			{
				contCount++;
			}
			else if (board[y][p_x] != 0 && contCount > 0)
			{
				contCount = 0;
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
}

int		Board::placePiece(int y, int x, Player *player)
{
	int	playerNum;

	playerNum = player->getPlayerNum();
	if ((y < 0 || y >= boardDim) || (x < 0 || x >= boardDim))
	{
		return (-1);
	}
	if (board[y][x] != 0)
	{
		return (-1);
	}

	return (0);
}