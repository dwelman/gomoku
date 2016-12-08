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

Board::Board(const Board &obj)
{
	this->boardDim = obj.boardDim;

	this->board = (int **)malloc(sizeof(int *) * boardDim);
	for (int y = 0; y < boardDim; y++)
	{
		this->board[y] = (int *)malloc(sizeof(int) * boardDim);
		for (int x = 0; x < boardDim; x++)
		{
			this->board[y][x] = obj.board[y][x];
		}
	}
}

void			Board::setBoard(int **newArr)
{
	for (int y = 0; y < boardDim; y++)
	{
		for (int x = 0; x < boardDim; x++)
		{
			board[y][x] = newArr[y][x];
		}
	}
}

void			Board::copyBoard(int **newArr)
{
	for (int y = 0; y < boardDim; y++)
	{
		for (int x = 0; x < boardDim; x++)
		{
			newArr[y][x] = board[y][x];
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
	contCount = 0;
	emptCount = 0;
	p_x = x - 5;
	for (p_y = y - 5; p_y <= y + 5; p_y++)
	{
		if (p_y >= 0 && p_y < boardDim && p_x >= 0 && p_x < boardDim)
		{
			if (board[p_y][p_x] == playerNum)
			{
				contCount++;
				if (p_y - 1 == -1 || p_x - 1 == -1 || p_y + 1 == boardDim || p_x + 1 == boardDim)
					contCount--;
			}
			else if (board[p_y][p_x] != 0)
			{                      
				contCount = -1;
			}
			else
			{
				if (contCount < 0)
					contCount = 0;
				emptCount++;
			}
		}
		p_x++;
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 0;
	emptCount = 0;
	p_x = x + 5;
	for (p_y = y - 5; p_y <= y + 5; p_y++)
	{
		if (p_y >= 0 && p_y < boardDim && p_x >= 0 && p_x < boardDim)
		{
			if (board[p_y][p_x] == playerNum)
			{
				contCount++;
				if (p_y - 1 == -1 || p_x - 1 == -1 || p_y + 1 == boardDim || p_x + 1 == boardDim)
					contCount--;
			}
			else if (board[p_y][p_x] != 0)
			{                      
				contCount = -1;
			}
			else
			{
				if (contCount < 0)
					contCount = 0;
				emptCount++;
			}
		}
		p_x--;
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 0;
	emptCount = 0;
	for (p_y = y + 5; p_y >= y - 5; p_y--)
	{
		if (p_y >= 0 && p_y < boardDim)
		{
			if (board[p_y][x] == playerNum)
			{
				contCount++;
				if (p_y - 1 == -1 || p_y + 1 == boardDim)
					contCount--;
			}
			else if (board[p_y][x] != 0)
			{                      
				contCount = -1;
			}
			else
			{
				if (contCount < 0)
					contCount = 0;
				emptCount++;
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	contCount = 0;
	emptCount = 0;
	for (p_x = x + 5; p_x >= x - 5; p_x--)
	{
		if (p_x >= 0 && p_x < boardDim)
		{
			if (board[y][p_x] == playerNum)
			{
				contCount++;
				if (p_x - 1 == -1 || p_x + 1 == boardDim)
					contCount--;
			}
			else if (board[y][p_x] != 0)
			{                      
				contCount = -1;
			}
			else
			{
				if (contCount < 0)
					contCount = 0;
				emptCount++;
			}
		}
	}
	if (contCount >= 3)
		freeCount++;
	return (freeCount);
}

int		Board::checkFlanks(int y, int x, int playerNum)
{
	int		ret;
	bool	isYDiagSizePos;
	bool	isYDiagSizeNeg;
	
	ret = 0;
	isYDiagSizePos = false;
	isYDiagSizeNeg = false;
	if (y + 3 < boardDim)
	{
		isYDiagSizePos = true;
		if (board[y + 1][x] != 0 && board[y + 1][x] != playerNum)
		if (board[y + 2][x] != 0 && board[y + 2][x] != playerNum)
		if (board[y + 3][x] == playerNum)
		{
			board[y + 1][x] = 3;
			board[y + 2][x] = 3;
			ret++;
		}
	}
	if (y - 3 > -1)
	{
		isYDiagSizeNeg = true;		
		if (board[y - 1][x] != 0 && board[y - 1][x] != playerNum)
		if (board[y - 2][x] != 0 && board[y - 2][x] != playerNum)
		if (board[y - 3][x] == playerNum)
		{
			board[y - 1][x] = 3;
			board[y - 2][x] = 3;
			ret++;
		}
	}
	if (x + 3 < boardDim)
	{
		if (board[y][x + 1] != 0 && board[y][x + 1] != playerNum)
		if (board[y][x + 2] != 0 && board[y][x + 2] != playerNum)
		if (board[y][x + 3] == playerNum)
		{
			board[y][x + 1] = 3;
			board[y][x + 2] = 3;
			ret++;
		}
		if (isYDiagSizePos)
		{
			if (board[y + 1][x + 1] != 0 && board[y + 1][x + 1] != playerNum)
			if (board[y + 2][x + 2] != 0 && board[y + 2][x + 2] != playerNum)
			if (board[y + 3][x + 3] == playerNum)
			{
				board[y + 1][x + 1] = 3;
				board[y + 2][x + 2] = 3;
				ret++;
			}
		}
		if (isYDiagSizeNeg)
		{
			if (board[y - 1][x + 1] != 0 && board[y - 1][x + 1] != playerNum)
			if (board[y - 2][x + 2] != 0 && board[y - 2][x + 2] != playerNum)
			if (board[y - 3][x + 3] == playerNum)
			{
				board[y - 1][x + 1] = 3;
				board[y -  2][x + 2] = 3;
				ret++;
			}
		}
	}
	if (x - 3 > -1)
	{
		if (board[y][x - 1] != 0 && board[y][x - 1] != playerNum)
		if (board[y][x - 2] != 0 && board[y][x - 2] != playerNum)
		if (board[y][x - 3] == playerNum)
		{
			board[y][x - 1] = 3;
			board[y][x - 2] = 3;
			ret++;
		}
		if (isYDiagSizePos)
		{
			if (board[y + 1][x - 1] != 0 && board[y + 1][x - 1] != playerNum)
			if (board[y + 2][x - 2] != 0 && board[y + 2][x - 2] != playerNum)
			if (board[y + 3][x - 3] == playerNum)
			{
				board[y + 1][x - 1] = 3;
				board[y + 2][x - 2] = 3;
				ret++;
			}
		}
		if (isYDiagSizeNeg)
		{
			if (board[y - 1][x - 1] != 0 && board[y - 1][x - 1] != playerNum)
			if (board[y - 2][x - 2] != 0 && board[y - 2][x - 2] != playerNum)
			if (board[y - 3][x - 3] == playerNum)
			{
				board[y - 1][x - 1] = 3;
				board[y - 2][x - 2] = 3;
				ret++;
			}
		}
	}
	return (ret);
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
		p_x++;
	}
	contCount = 0;
	p_x = x - 5;
	for (p_y = y + 5; p_y >= y - 5; p_y--)
	{
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
		p_x++;
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
	int		playerNum;
	bool	madeCapture;
	int		caps;

	madeCapture = false;
	playerNum = player->getPlayerNum();
	if ((y < 0 || y >= boardDim) || (x < 0 || x >= boardDim))
	{
		return (-1);
	}
	if (board[y][x] != 0)
	{
		return (-1);
	}
	board[y][x] = playerNum;
	if ((caps = checkFlanks(y, x, playerNum)) > 0)
	{
		player->incCaptures(caps);
		madeCapture = true;
	}
	if (player->getCaptures() >= 5)
		return (2);
	if (checkVictory(y, x, playerNum))
		return (2);
	if (madeCapture)
		return (1);
	if (returnFreeThrees(y, x, playerNum) > 1)
	{
		board[y][x] = 0;
		return (-1);
	}
	return (0);
}