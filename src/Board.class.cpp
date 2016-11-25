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
	for (int k = 0; k <= boardDim; k++)
	{
		printf("\033[32m%-4d", k);
	}
	cout << endl;
	for (int y = 0; y < boardDim; y++)
	{
		printf("\033[32m%-4d\033[39m", y + 1);
		for (int x = 0; x < boardDim; x++)
		{
			if (this->board[y][x] == 1)
			{
				cout << "\033[31m";
			}
			else if (this->board[y][x] == 2)
			{
				cout << "\033[34m";
			}
			printf("%-4d\033[39m", this->board[y][x]);
		}
		cout << endl;
	}
}

int		Board::returnFreeThrees(int y, int x, int playerNum)
{
	int	p_y;
	int	p_x;
	int	freeCount;
	int	contCount;
	int	emptCount;

	freeCount = 0;
	contCount = 1;
	emptCount = 0;
	p_x = x - 5;
	for (p_y = y - 5; p_y <= y + 5; p_y++)
	{
		p_x++;
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
			else
			{
				emptCount++;
				if (emptCount > 1)
					contCount = 0;
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 1;
	emptCount = 0;
	p_x = x - 5;
	for (p_y = y + 5; p_y >= y - 5; p_y--)
	{
		p_x++;
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
			else
			{
				emptCount++;
				if (emptCount > 1)
					contCount = 0;
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 1;
	emptCount = 0;
	for (p_y = y + 5; p_y >= y - 5; p_y--)
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
			else
			{
				emptCount++;
				if (emptCount > 1)
					contCount = 0;
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 1;
	emptCount = 0;
	for (p_x = x + 5; p_x >= x - 5; p_x--)
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
			else
			{
				emptCount++;
				if (emptCount > 1)
					contCount = 0;
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	return (freeCount);
}

void	Board::checkFlanks(int y, int x, Player *player)
{
	int		playerNum;
	bool	isYDiagSizePos;
	bool	isYDiagSizeNeg;
	
	isYDiagSizePos = false;
	isYDiagSizeNeg = false;
	playerNum = player->getPlayerNum();
	if (y + 3 < boardDim)
	{
		isYDiagSizePos = true;
		if (board[y + 1][x] != 0 && board[y + 1][x] != playerNum)
		if (board[y + 2][x] != 0 && board[y + 2][x] != playerNum)
		if (board[y + 3][x] == playerNum)
		{
			board[y + 1][x] = 0;
			board[y + 2][x] = 0;
			player->incCaptures();
		}
	}
	if (y - 3 > -1)
	{
		isYDiagSizeNeg = true;		
		if (board[y - 1][x] != 0 && board[y - 1][x] != playerNum)
		if (board[y - 2][x] != 0 && board[y - 2][x] != playerNum)
		if (board[y - 3][x] == playerNum)
		{
			board[y - 1][x] = 0;
			board[y - 2][x] = 0;
			player->incCaptures();
		}
	}
	if (x + 3 < boardDim)
	{
		if (board[y][x + 1] != 0 && board[y][x + 1] != playerNum)
		if (board[y][x + 2] != 0 && board[y][x + 2] != playerNum)
		if (board[y][x + 3] == playerNum)
		{
			board[y][x + 1] = 0;
			board[y][x + 2] = 0;
			player->incCaptures();
		}
		if (isYDiagSizePos)
		{
			if (board[y + 1][x + 1] != 0 && board[y + 1][x + 1] != playerNum)
			if (board[y + 2][x + 2] != 0 && board[y + 2][x + 2] != playerNum)
			if (board[y + 3][x + 3] == playerNum)
			{
				board[y + 1][x + 1] = 0;
				board[y + 2][x + 2] = 0;
				player->incCaptures();
			}
		}
		if (isYDiagSizeNeg)
		{
			if (board[y - 1][x + 1] != 0 && board[y - 1][x + 1] != playerNum)
			if (board[y - 2][x + 2] != 0 && board[y - 2][x + 2] != playerNum)
			if (board[y - 3][x + 3] == playerNum)
			{
				board[y + 1][x + 1] = 0;
				board[y + 2][x + 2] = 0;
				player->incCaptures();
			}
		}
	}
	if (x - 3 > -1)
	{
		if (board[y][x - 1] != 0 && board[y][x - 1] != playerNum)
		if (board[y][x - 2] != 0 && board[y][x - 2] != playerNum)
		if (board[y][x - 3] == playerNum)
		{
			board[y][x - 1] = 0;
			board[y][x - 2] = 0;
			player->incCaptures();
		}
		if (isYDiagSizePos)
		{
			if (board[y + 1][x - 1] != 0 && board[y + 1][x - 1] != playerNum)
			if (board[y + 2][x - 2] != 0 && board[y + 2][x - 2] != playerNum)
			if (board[y + 3][x - 3] == playerNum)
			{
				board[y + 1][x - 1] = 0;
				board[y + 2][x - 2] = 0;
				player->incCaptures();
			}
		}
		if (isYDiagSizeNeg)
		{
			if (board[y - 1][x - 1] != 0 && board[y - 1][x - 1] != playerNum)
			if (board[y - 2][x - 2] != 0 && board[y - 2][x - 2] != playerNum)
			if (board[y - 3][x - 3] == playerNum)
			{
				board[y + 1][x - 1] = 0;
				board[y + 2][x - 2] = 0;
				player->incCaptures();
			}
		}
	}
}

bool	Board::checkVictory(int y, int x, int playerNum)
{
	int	p_y;
	int	p_x;
	int	contCount;

	contCount = 0;
	p_x = x - 5;
	for (p_y = y - 5; p_y <= y + 5; p_y++)
	{
		p_x++;
		if (p_y >= 0 && p_y < boardDim && p_x >= 0 && p_x < boardDim)
		{
			if (board[p_y][p_x] == playerNum)
			{
				contCount++;
			}
			else
			{
				contCount = 0;
			}
			if (contCount >= 5)
				return (true);
		}
	}
	contCount = 0;
	p_x = x - 5;
	for (p_y = y + 5; p_y >= y - 5; p_y--)
	{
		p_x++;
		if (p_y >= 0 && p_y < boardDim && p_x >= 0 && p_x < boardDim)
		{
			if (board[p_y][p_x] == playerNum)
			{
				contCount++;
			}
			else
			{
				contCount = 0;
			}
			if (contCount >= 5)
				return (true);
		}
	}
	contCount = 0;
	for (p_y = y + 5; p_y >= y - 5; p_y--)
	{
		if (p_y >= 0 && p_y < boardDim)
		{
			if (board[p_y][x] == playerNum)
			{
				contCount++;
			}
			else
			{
				contCount = 0;
			}
			if (contCount >= 5)
				return (true);
		}
	}
	contCount = 0;
	for (p_x = x + 5; p_x >= x - 5; p_x--)
	{
		if (p_x >= 0 && p_x < boardDim)
		{
			if (board[y][p_x] == playerNum)
			{
				contCount++;
			}
			else
			{
				contCount = 0;
			}
			if (contCount >= 5)
				return (true);
		}
	}
	return (false);
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
	if (returnFreeThrees(y, x, playerNum) > 1)
	{
		return (-1);
	}
	board[y][x] = playerNum;
	checkFlanks(y, x, player);
	if (player->getCaptures() == 5)
		return (1);
	if (checkVictory(y, x, playerNum))
		return (1);
	return (0);
}