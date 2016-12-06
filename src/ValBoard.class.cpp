#include <ValBoard.class.h>

ValBoard::ValBoard(int boardDim)
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
	for (int y = (boardDim / 2) - 1; y < (boardDim / 2) + 1; y++)
	{
		for (int x = (boardDim / 2) - 1; x < (boardDim / 2) + 1; x++)
		{
			setVal(y, x, 1);
		}
	}
}

vector<int*>	ValBoard::fetchTiles()
{
	vector<int*>	ret;
	int				*vals;

	for (int y = 0; y < boardDim; y++)
	{
		for (int x = 0; x < boardDim; x++)
		{
			if (board[y][x] > 0)
			{
				vals = (int *)malloc(sizeof(int) * 3);
				vals[0] = board[y][x];
				vals[1] = y;
				vals[2] = x;
				ret.push_back(vals);
			}
		}
	}
	sort(ret.begin(), ret.end(),
		[](int *a, int *b){
			return (a[0] > b[0]);
		}
	);
	return (ret);
}

void	ValBoard::placePiece(int y, int x, Board *curBoard, bool wasFlank)
{
	int		p_y;
	int		p_x;
	int		curPlayNum;
	bool	isYDiagSizePos;
	bool	isYDiagSizeNeg;

	board[y][x] = -1000;
	curPlayNum = curBoard->getBoard()[y][x];
	if (wasFlank)
		unmarkFlanks(y, x, curPlayNum, curBoard);

	p_y = y - 1;
	p_x = x - 1;
	while ((p_y >= 0 && p_x >= 0) && (p_y > y - 5 && p_x > x - 5))
	{
		if (!(curBoard->getBoard()[p_y][p_x] == 0 || curBoard->getBoard()[p_y][p_x] == curPlayNum))
			break;
		board[p_y][p_x]++;
		p_y--;
		p_x--;
	}

	p_y = y + 1;
	p_x = x + 1;
	while ((p_y < boardDim && p_x < boardDim) && (p_y < y + 5 && p_x < x + 5))
	{
		if (!(curBoard->getBoard()[p_y][p_x] == 0 || curBoard->getBoard()[p_y][p_x] == curPlayNum))
			break;
		board[p_y][p_x]++;
		p_y++;
		p_x++;
	}

	p_y = y - 1;
	p_x = x + 1;
	while ((p_y >= 0 && p_x < boardDim) && (p_y > y - 5 && p_x < x + 5))
	{
		if (!(curBoard->getBoard()[p_y][p_x] == 0 || curBoard->getBoard()[p_y][p_x] == curPlayNum))
			break;
		board[p_y][p_x]++;
		p_y--;
		p_x++;
	}

	p_y = y + 1;
	p_x = x - 1;
	while ((p_y < boardDim && p_x >= 0) && (p_y < y + 5 && p_x > x - 5))
	{
		if (!(curBoard->getBoard()[p_y][p_x] == 0 || curBoard->getBoard()[p_y][p_x] == curPlayNum))
			break;
		board[p_y][p_x]++;
		p_y++;
		p_x--;
	}

	p_y = y + 1;
	while (p_y < boardDim && p_y < y + 5)
	{
		if (!(curBoard->getBoard()[p_y][x] == 0 || curBoard->getBoard()[p_y][x] == curPlayNum))
			break;
		board[p_y][x]++;
		p_y++;
	}

	p_y = y - 1;
	while (p_y >= 0 && p_y > y - 5)
	{
		if (!(curBoard->getBoard()[p_y][x] == 0 || curBoard->getBoard()[p_y][x] == curPlayNum))
			break;
		board[p_y][x]++;
		p_y--;
	}

	p_x = x + 1;
	while (p_x < boardDim && p_x < x + 5)
	{
		if (!(curBoard->getBoard()[y][p_x] == 0 || curBoard->getBoard()[y][p_x] == curPlayNum))
			break;
		board[y][p_x]++;
		p_x++;
	}

	p_x = x - 1;
	while (p_x >= 0 && p_x > x - 5)
	{
		if (!(curBoard->getBoard()[y][p_x] == 0 || curBoard->getBoard()[y][p_x] == curPlayNum))
			break;
		board[y][p_x]++;
		p_x--;
	}
	
	markFlanks(y, x, curPlayNum, curBoard->getBoard());
	markFreeThrees(y, x, curPlayNum, curBoard->getBoard());
	markVictory(y, x, curPlayNum, curBoard->getBoard());
}

void	ValBoard::markFreeThrees(int y, int x, int playerNum, int **curBoard)
{
	int		contCount;
	int		p_y;
	int		p_x;

	contCount = 1;
	p_y = y + 1;
	while (p_y < boardDim && p_y < y + 5)
	{
		if (curBoard[p_y][x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][x] != 0)
		{
			break;
		}
		p_y++;
	}
	p_y = y - 1;
	while (p_y >= 0 && p_y > y - 5)
	{
		if (curBoard[p_y][x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][x] != 0)
		{
			break;
		}
		p_y--;
	}
	if (contCount >= 3)
	{
		p_y = y + 1;
		while (p_y < boardDim && p_y < y + 5)
		{
			if (curBoard[p_y][x] == 0)
			{
				board[p_y][x] = 1500;
				break;
			}
			else if (curBoard[p_y][x] != playerNum)
			{
				break;
			}
			p_y++;
		}
		p_y = y - 1;
		while (p_y < boardDim && p_y < y + 5)
		{
			if (curBoard[p_y][x] == 0)
			{
				board[p_y][x] = 1500;
				break;
			}
			else if (curBoard[p_y][x] != playerNum)
			{
				break;
			}
			p_y--;
		}
	}

	contCount = 1;
	p_x = x + 1;
	while (p_x < boardDim && p_x < x + 5)
	{
		if (curBoard[y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[y][p_x] != 0)
		{
			break;
		}
		p_x++;
	}
	p_x = x - 1;
	while (p_x >= 0 && p_x > x - 5)
	{
		if (curBoard[y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[y][p_x] != 0)
		{
			break;
		}
		p_x--;
	}
	if (contCount >= 3)
	{
		p_x = x + 1;
		while (p_x < boardDim && p_x < x + 5)
		{
			if (curBoard[y][p_x] == 0)
			{
				board[y][p_x] = 1500;
				break;
			}
			else if (curBoard[y][p_x] != playerNum)
			{
				break;
			}
			p_x++;
		}
		p_x = x - 1;
		while (p_x < boardDim && p_x < x + 5)
		{
			if (curBoard[y][p_x] == 0)
			{
				board[y][p_x] = 1500;
				break;
			}
			else if (curBoard[y][p_x] != playerNum)
			{
				break;
			}
			p_x--;
		}
	}

	contCount = 1;
	p_x = x + 1;
	p_y = y + 1;
	while ((p_x < boardDim && p_x < x + 5) && (p_y < boardDim && p_y < y + 5))
	{
		if (curBoard[p_y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][p_x] != 0)
		{
			break;
		}
		p_x++;
		p_y++;
	}
	p_x = x - 1;
	p_y = y - 1;
	while ((p_x >= 0 && p_x > x - 5) && (p_y >= 0 && p_y > y - 5))
	{
		if (curBoard[p_y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][p_x] != 0)
		{
			break;
		}
		p_x--;
		p_y--;
	}
	if (contCount >= 3)
	{
		p_x = x + 1;
		p_y = y + 1;
		while ((p_x < boardDim && p_x < x + 5) && (p_y < boardDim && p_y < y + 5))
		{
			if (curBoard[p_y][p_x] == 0)
			{
				board[p_y][p_x] = 1500;
				break;
			}
			else if (curBoard[p_y][p_x] != playerNum)
			{
				break;
			}
			p_x++;
			p_y++;
		}
		p_x = x - 1;
		p_y = y - 1;
		while ((p_x >= 0 && p_x > x - 5) && (p_y >= 0 && p_y > y - 5))
		{
			if (curBoard[p_y][p_x] == 0)
			{
				board[p_y][p_x] = 1500;
				break;
			}
			else if (curBoard[p_y][p_x] != playerNum)
			{
				break;
			}
			p_x--;
			p_y--;
		}
	}

	contCount = 1;
	p_x = x - 1;
	p_y = y + 1;
	while ((p_x >= 0 && p_x > x - 5) && (p_y < boardDim && p_y < y + 5))
	{
		if (curBoard[p_y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][p_x] != 0)
		{
			break;
		}
		p_x--;
		p_y++;
	}
	p_x = x + 1;
	p_y = y - 1;
	while ((p_x < boardDim && p_x < x + 5) && (p_y >= 0 && p_y > y - 5))
	{
		if (curBoard[p_y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][p_x] != 0)
		{
			break;
		}
		p_x++;
		p_y--;
	}
	if (contCount >= 3)
	{
		p_x = x - 1;
		p_y = y + 1;
		while ((p_x >= 0 && p_x > x - 5) && (p_y < boardDim && p_y < y + 5))
		{
			if (curBoard[p_y][p_x] == 0)
			{
				board[p_y][p_x] = 1500;
				break;
			}
			else if (curBoard[p_y][p_x] != playerNum)
			{
				break;
			}
			p_x--;
			p_y++;
		}
		p_x = x + 1;
		p_y = y - 1;
		while ((p_x < boardDim && p_x < x + 5) && (p_y >= 0 && p_y > y - 5))
		{
			if (curBoard[p_y][p_x] == 0)
			{
				board[p_y][p_x] = 1500;
				break;
			}
			else if (curBoard[p_y][p_x] != playerNum)
			{
				break;
			}
			p_x++;
			p_y--;
		}
	}
}

void	ValBoard::markVictory(int y, int x, int playerNum, int **curBoard)
{
	int		contCount;
	int		p_y;
	int		p_x;

	contCount = 1;
	p_y = y + 1;
	while (p_y < boardDim && p_y < y + 5)
	{
		if (curBoard[p_y][x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][x] != 0)
		{
			break;
		}
		p_y++;
	}
	p_y = y - 1;
	while (p_y >= 0 && p_y > y - 5)
	{
		if (curBoard[p_y][x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][x] != 0)
		{
			break;
		}
		p_y--;
	}
	if (contCount >= 4)
	{
		p_y = y + 1;
		while (p_y < boardDim && p_y < y + 5)
		{
			if (curBoard[p_y][x] == 0)
			{
				board[p_y][x] = 2000;
				break;
			}
			else if (curBoard[p_y][x] != playerNum)
			{
				break;
			}
			p_y++;
		}
		p_y = y - 1;
		while (p_y < boardDim && p_y < y + 5)
		{
			if (curBoard[p_y][x] == 0)
			{
				board[p_y][x] = 2000;
				break;
			}
			else if (curBoard[p_y][x] != playerNum)
			{
				break;
			}
			p_y--;
		}
	}

	contCount = 1;
	p_x = x + 1;
	while (p_x < boardDim && p_x < x + 5)
	{
		if (curBoard[y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[y][p_x] != 0)
		{
			break;
		}
		p_x++;
	}
	p_x = x - 1;
	while (p_x >= 0 && p_x > x - 5)
	{
		if (curBoard[y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[y][p_x] != 0)
		{
			break;
		}
		p_x--;
	}
	if (contCount >= 4)
	{
		p_x = x + 1;
		while (p_x < boardDim && p_x < x + 5)
		{
			if (curBoard[y][p_x] == 0)
			{
				board[y][p_x] = 2000;
				break;
			}
			else if (curBoard[y][p_x] != playerNum)
			{
				break;
			}
			p_x++;
		}
		p_x = x - 1;
		while (p_x < boardDim && p_x < x + 5)
		{
			if (curBoard[y][p_x] == 0)
			{
				board[y][p_x] = 2000;
				break;
			}
			else if (curBoard[y][p_x] != playerNum)
			{
				break;
			}
			p_x--;
		}
	}

	contCount = 1;
	p_x = x + 1;
	p_y = y + 1;
	while ((p_x < boardDim && p_x < x + 5) && (p_y < boardDim && p_y < y + 5))
	{
		if (curBoard[p_y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][p_x] != 0)
		{
			break;
		}
		p_x++;
		p_y++;
	}
	p_x = x - 1;
	p_y = y - 1;
	while ((p_x >= 0 && p_x > x - 5) && (p_y >= 0 && p_y > y - 5))
	{
		if (curBoard[p_y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][p_x] != 0)
		{
			break;
		}
		p_x--;
		p_y--;
	}
	if (contCount >= 4)
	{
		p_x = x + 1;
		p_y = y + 1;
		while ((p_x < boardDim && p_x < x + 5) && (p_y < boardDim && p_y < y + 5))
		{
			if (curBoard[p_y][p_x] == 0)
			{
				board[p_y][p_x] = 2000;
				break;
			}
			else if (curBoard[p_y][p_x] != playerNum)
			{
				break;
			}
			p_x++;
			p_y++;
		}
		p_x = x - 1;
		p_y = y - 1;
		while ((p_x >= 0 && p_x > x - 5) && (p_y >= 0 && p_y > y - 5))
		{
			if (curBoard[p_y][p_x] == 0)
			{
				board[p_y][p_x] = 2000;
				break;
			}
			else if (curBoard[p_y][p_x] != playerNum)
			{
				break;
			}
			p_x--;
			p_y--;
		}
	}

	contCount = 1;
	p_x = x - 1;
	p_y = y + 1;
	while ((p_x >= 0 && p_x > x - 5) && (p_y < boardDim && p_y < y + 5))
	{
		if (curBoard[p_y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][p_x] != 0)
		{
			break;
		}
		p_x--;
		p_y++;
	}
	p_x = x + 1;
	p_y = y - 1;
	while ((p_x < boardDim && p_x < x + 5) && (p_y >= 0 && p_y > y - 5))
	{
		if (curBoard[p_y][p_x] == playerNum)
		{
			contCount++;
		}
		else if (curBoard[p_y][p_x] != 0)
		{
			break;
		}
		p_x++;
		p_y--;
	}
	if (contCount >= 4)
	{
		p_x = x - 1;
		p_y = y + 1;
		while ((p_x >= 0 && p_x > x - 5) && (p_y < boardDim && p_y < y + 5))
		{
			if (curBoard[p_y][p_x] == 0)
			{
				board[p_y][p_x] = 2000;
				break;
			}
			else if (curBoard[p_y][p_x] != playerNum)
			{
				break;
			}
			p_x--;
			p_y++;
		}
		p_x = x + 1;
		p_y = y - 1;
		while ((p_x < boardDim && p_x < x + 5) && (p_y >= 0 && p_y > y - 5))
		{
			if (curBoard[p_y][p_x] == 0)
			{
				board[p_y][p_x] = 2000;
				break;
			}
			else if (curBoard[p_y][p_x] != playerNum)
			{
				break;
			}
			p_x++;
			p_y--;
		}
	}
}

void	ValBoard::unmarkFlanks(int y, int x, int playerNum, Board *curBoard)
{
	bool	isYDiagSizePos;
	bool	isYDiagSizeNeg;
	
	isYDiagSizePos = false;
	isYDiagSizeNeg = false;
	if (y + 3 < boardDim)
	{
		isYDiagSizePos = true;
		if (curBoard->getBoard()[y + 1][x] == 3)
		if (curBoard->getBoard()[y + 2][x] == 3)
		if (curBoard->getBoard()[y + 3][x] == playerNum)
		{
			board[y + 1][x] += 1000;
			board[y + 2][x] += 1000;
			curBoard->setTile(y + 1, x, 0);
			curBoard->setTile(y + 2, x, 0);
		}
	}
	if (y - 3 > -1)
	{
		isYDiagSizeNeg = true;		
		if (curBoard->getBoard()[y - 1][x] == 3)
		if (curBoard->getBoard()[y - 2][x] == 3)
		if (curBoard->getBoard()[y - 3][x] == playerNum)
		{
			board[y - 1][x] += 1000;
			board[y - 2][x] += 1000;
			curBoard->setTile(y - 1, x, 0);	
			curBoard->setTile(y - 2, x, 0);	
		}
	}
	if (x + 3 < boardDim)
	{
		if (curBoard->getBoard()[y][x + 1] == 3)
		if (curBoard->getBoard()[y][x + 2] == 3)
		if (curBoard->getBoard()[y][x + 3] == playerNum)
		{
			board[y][x + 1] += 1000;
			board[y][x + 2] += 1000;
			curBoard->setTile(y, x + 1, 0);	
			curBoard->setTile(y, x + 2, 0);	
		}
		if (isYDiagSizePos)
		{
			if (curBoard->getBoard()[y + 1][x + 1] == 3)
			if (curBoard->getBoard()[y + 2][x + 2] == 3)
			if (curBoard->getBoard()[y + 3][x + 3] == playerNum)
			{
				board[y + 1][x + 1] += 1000;
				board[y + 2][x + 2] += 1000;
				curBoard->setTile(y + 1, x + 1, 0);	
				curBoard->setTile(y + 2, x + 2, 0);	
			}
		}
		if (isYDiagSizeNeg)
		{
			if (curBoard->getBoard()[y - 1][x + 1] == 3)
			if (curBoard->getBoard()[y - 2][x + 2] == 3)
			if (curBoard->getBoard()[y - 3][x + 3] == playerNum)
			{
				board[y - 1][x + 1] += 1000;
				board[y - 2][x + 2] += 1000;
				curBoard->setTile(y - 1, x + 1, 0);	
				curBoard->setTile(y - 2, x + 2, 0);	
			}
		}
	}
	if (x - 3 > -1)
	{
		if (curBoard->getBoard()[y][x - 1] == 3)
		if (curBoard->getBoard()[y][x - 2] == 3)
		if (curBoard->getBoard()[y][x - 3] == playerNum)
		{
			board[y][x - 1] += 1000;
			board[y][x - 2] += 1000;
			curBoard->setTile(y, x - 1, 0);	
			curBoard->setTile(y, x - 2, 0);	
		}
		if (isYDiagSizePos)
		{
			if (curBoard->getBoard()[y + 1][x - 1] == 3)
			if (curBoard->getBoard()[y + 2][x - 2] == 3)
			if (curBoard->getBoard()[y + 3][x - 3] == playerNum)
			{
				board[y + 1][x - 1] += 1000;
				board[y + 2][x - 2] += 1000;
				curBoard->setTile(y + 1, x - 1, 0);
				curBoard->setTile(y + 2, x - 2, 0);
			}
		}
		if (isYDiagSizeNeg)
		{
			if (curBoard->getBoard()[y - 1][x - 1] == 3)
			if (curBoard->getBoard()[y - 2][x - 2] == 3)
			if (curBoard->getBoard()[y - 3][x - 3] == playerNum)
			{
				board[y - 1][x - 1] += 1000;
				board[y - 2][x - 2] += 1000;
				curBoard->setTile(y - 1, x - 1, 0);
				curBoard->setTile(y - 2, x - 2, 0);
			}
		}
	}
}

void	ValBoard::markFlanks(int y, int x, int playerNum, int **curBoard)
{
	bool	isYDiagSizePos;
	bool	isYDiagSizeNeg;
	
	isYDiagSizePos = false;
	isYDiagSizeNeg = false;
	if (y + 3 < boardDim)
	{
		isYDiagSizePos = true;
		if (curBoard[y + 1][x] != 0 && curBoard[y + 1][x] != playerNum)
		if (curBoard[y + 2][x] != 0 && curBoard[y + 2][x] != playerNum)
		if (curBoard[y + 3][x] == 0)
		{
			board[y + 3][x] = 1000;
		}

		if (curBoard[y + 1][x] == playerNum)
		if (curBoard[y + 2][x] != 0 && curBoard[y + 2][x] != playerNum)
		if (y - 1 >= 0)
		{
			if (board[y - 1][x] >= 0)
				board[y - 1][x] = 1000;
		}
		if (y - 2 >= 0)
		{
			if (curBoard[y - 1][x] == playerNum)
			if (curBoard[y + 1][x] != 0 && curBoard[y + 1][x] != playerNum)
			{
				if (board[y - 2][x] >= 0)
					board[y - 2][x] = 1000;
			}
		}
	}
	if (y - 3 > -1)
	{
		isYDiagSizeNeg = true;		
		if (curBoard[y - 1][x] != 0 && curBoard[y - 1][x] != playerNum)
		if (curBoard[y - 2][x] != 0 && curBoard[y - 2][x] != playerNum)
		if (curBoard[y - 3][x] == 0)
		{
			board[y - 3][x] = 1000;
		}

		if (curBoard[y - 1][x] == playerNum)
		if (curBoard[y - 2][x] != 0 && curBoard[y - 2][x] != playerNum)
		if (y + 1 < boardDim)
		{
			if (board[y + 1][x] >= 0)
				board[y + 1][x] = 1000;
		}
		if (y + 2 < boardDim)
		{
			if (curBoard[y + 1][x] == playerNum)
			if (curBoard[y - 1][x] != 0 && curBoard[y - 1][x] != playerNum)
			{
				if (board[y + 2][x] >= 0)
					board[y + 2][x] = 1000;
			}
		}
	}
	if (x + 3 < boardDim)
	{
		if (curBoard[y][x + 1] != 0 && curBoard[y][x + 1] != playerNum)
		if (curBoard[y][x + 2] != 0 && curBoard[y][x + 2] != playerNum)
		if (curBoard[y][x + 3] == 0)
		{
			board[y][x + 3] = 1000;
		}

		if (curBoard[y][x + 1] == playerNum)
		if (curBoard[y][x + 2] != 0 && curBoard[y][x + 2] != playerNum)
		if (x - 1 >= 0)
		{
			if (board[y][x - 1] >= 0)
				board[y][x - 1] = 1000;
		}
		if (x - 2 >= 0)
		{
			if (curBoard[y][x - 1] == playerNum)
			if (curBoard[y][x + 1] != 0 && curBoard[y][x + 1] != playerNum)
			{
				if (board[y][x - 2] >= 0)
					board[y][x - 2] = 1000;
			}
		}

		if (isYDiagSizePos)
		{
			if (curBoard[y + 1][x + 1] != 0 && curBoard[y + 1][x + 1] != playerNum)
			if (curBoard[y + 2][x + 2] != 0 && curBoard[y + 2][x + 2] != playerNum)
			if (curBoard[y + 3][x + 3] == 0)
			{
				board[y + 3][x + 3] = 1000;
			}

			if (curBoard[y + 1][x + 1] == playerNum)
			if (curBoard[y + 2][x + 2] != 0 && curBoard[y + 2][x + 2] != playerNum)
			if (x - 1 >= 0)
			{
				if (board[y - 1][x - 1] >= 0)
					board[y - 1][x - 1] = 1000;
			}
			if (x - 2 >= 0)
			{
				if (curBoard[y - 1][x - 1] == playerNum)
				if (curBoard[y + 1][x + 1] != 0 && curBoard[y + 1][x + 1] != playerNum)
				{
					if (board[y - 2][x - 2] >= 0)
						board[y - 2][x - 2] = 1000;
				}
			}
		}
		if (isYDiagSizeNeg)
		{
			if (curBoard[y - 1][x + 1] != 0 && curBoard[y - 1][x + 1] != playerNum)
			if (curBoard[y - 2][x + 2] != 0 && curBoard[y - 2][x + 2] != playerNum)
			if (curBoard[y - 3][x + 3] == 0)
			{
				board[y - 3][x + 3] = 1000;
			}

			if (curBoard[y - 1][x + 1] == playerNum)
			if (curBoard[y - 2][x + 2] != 0 && curBoard[y - 2][x + 2] != playerNum)
			if (x - 1 >= 0)
			{
				if (board[y + 1][x - 1] >= 0)
					board[y + 1][x - 1] = 1000;
			}
			if (x - 2 >= 0)
			{
				if (curBoard[y + 1][x - 1] == playerNum)
				if (curBoard[y - 1][x + 1] != 0 && curBoard[y - 1][x + 1] != playerNum)
				{
					if (board[y + 2][x - 2] >= 0)
						board[y + 2][x - 2] = 1000;
				}
			}
		}
	}
	if (x - 3 > -1)
	{
		if (curBoard[y][x - 1] != 0 && curBoard[y][x - 1] != playerNum)
		if (curBoard[y][x - 2] != 0 && curBoard[y][x - 2] != playerNum)
		if (curBoard[y][x - 3] == 0)
		{
			board[y][x - 3] = 1000;
		}

		if (curBoard[y][x - 1] == playerNum)
		if (curBoard[y][x - 2] != 0 && curBoard[y][x - 2] != playerNum)
		if (x + 1 < boardDim)
		{
			if (board[y][x + 1] >= 0)
				board[y][x + 1] = 1000;
		}
		if (x + 2 < boardDim)
		{
			if (curBoard[y][x + 1] == playerNum)
			if (curBoard[y][x - 1] != 0 && curBoard[y][x - 1] != playerNum)
			{
				if (board[y][x + 2] >= 0)
					board[y][x + 2] = 1000;
			}
		}

		if (isYDiagSizePos)
		{
			if (curBoard[y + 1][x - 1] != 0 && curBoard[y + 1][x - 1] != playerNum)
			if (curBoard[y + 2][x - 2] != 0 && curBoard[y + 2][x - 2] != playerNum)
			if (curBoard[y + 3][x - 3] == 0)
			{
				board[y + 3][x - 3] = 1000;
			}

			if (curBoard[y - 1][x - 1] == playerNum)
			if (curBoard[y - 2][x - 2] != 0 && curBoard[y - 2][x - 2] != playerNum)
			if (x + 1 < boardDim)
			{
				if (board[y + 1][x + 1] >= 0)
					board[y + 1][x + 1] = 1000;
			}
			if (x + 2 < boardDim)
			{
				if (curBoard[y + 1][x + 1] == playerNum)
				if (curBoard[y - 1][x - 1] != 0 && curBoard[y - 1][x - 1] != playerNum)
				{
					if (board[y + 2][x + 2] >= 0)
						board[y + 2][x + 2] = 1000;
				}
			}
		}
		if (isYDiagSizeNeg)
		{
			if (curBoard[y - 1][x - 1] != 0 && curBoard[y - 1][x - 1] != playerNum)
			if (curBoard[y - 2][x - 2] != 0 && curBoard[y - 2][x - 2] != playerNum)
			if (curBoard[y - 3][x - 3] == 0)
			{
				board[y - 3][x - 3] = 1000;
			}

			if (curBoard[y + 1][x - 1] == playerNum)
			if (curBoard[y + 2][x - 2] != 0 && curBoard[y + 2][x - 2] != playerNum)
			if (x + 1 < boardDim)
			{
				if (board[y - 1][x + 1] >= 0)
					board[y - 1][x + 1] = 1000;
			}
			if (x + 2 < boardDim)
			{
				if (curBoard[y - 1][x + 1] == playerNum)
				if (curBoard[y + 1][x - 1] != 0 && curBoard[y + 1][x - 1] != playerNum)
				{
					if (board[y - 2][x + 2] >= 0)
						board[y - 2][x + 2] = 1000;
				}
			}
		}
	}
}