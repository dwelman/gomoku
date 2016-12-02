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

void	ValBoard::placePiece(int y, int x, Board *curBoard)
{
	int		p_y;
	int		p_x;
	int		curPlayNum;
	bool	isYDiagSizePos;
	bool	isYDiagSizeNeg;

	board[y][x] = -1000;
	curPlayNum = curBoard->getBoard()[y][x];

	p_y = y - 1;
	p_x = x - 1;
	while ((p_y >= 0 && p_x >= 0) && (p_y > p_y - 5 && p_x > p_x - 5))
	{
		if (!(curBoard->getBoard()[p_y][p_x] == 0 || curBoard->getBoard()[p_y][p_x] == curPlayNum))
			break;
		if (board[p_y][p_x] != -1000)
			board[p_y][p_x]++;
		p_y--;
		p_x--;
	}

	p_y = y + 1;
	p_x = x + 1;
	while ((p_y < boardDim && p_x < boardDim) && (p_y < p_y + 5 && p_x < p_x + 5))
	{
		if (!(curBoard->getBoard()[p_y][p_x] == 0 || curBoard->getBoard()[p_y][p_x] == curPlayNum))
			break;
		if (board[p_y][p_x] != -1000)
			board[p_y][p_x]++;
		p_y++;
		p_x++;
	}

	p_y = y - 1;
	p_x = x + 1;
	while ((p_y >= 0 && p_x < boardDim) && (p_y > p_y - 5 && p_x < p_x + 5))
	{
		if (!(curBoard->getBoard()[p_y][p_x] == 0 || curBoard->getBoard()[p_y][p_x] == curPlayNum))
			break;
		if (board[p_y][p_x] != -1000)
			board[p_y][p_x]++;
		p_y--;
		p_x++;
	}

	p_y = y + 1;
	p_x = x - 1;
	while ((p_y < boardDim && p_x >= 0) && (p_y < p_y + 5 && p_x > p_x - 5))
	{
		if (!(curBoard->getBoard()[p_y][p_x] == 0 || curBoard->getBoard()[p_y][p_x] == curPlayNum))
			break;
		if (board[p_y][p_x] != -1000)
			board[p_y][p_x]++;
		p_y++;
		p_x--;
	}

	p_y = y + 1;
	while (p_y < boardDim && p_y < p_y + 5)
	{
		if (!(curBoard->getBoard()[p_y][x] == 0 || curBoard->getBoard()[p_y][x] == curPlayNum))
			break;
		if (board[p_y][x] != -1000)
			board[p_y][x]++;
		p_y++;
	}

	p_y = y - 1;
	while (p_y >= 0 && p_y > p_y - 5)
	{
		if (!(curBoard->getBoard()[p_y][x] == 0 || curBoard->getBoard()[p_y][x] == curPlayNum))
			break;
		if (board[p_y][x] != -1000)
			board[p_y][x]++;
		p_y--;
	}

	p_x = x + 1;
	while (p_x < boardDim && p_x < p_x + 5)
	{
		if (!(curBoard->getBoard()[y][p_x] == 0 || curBoard->getBoard()[y][p_x] == curPlayNum))
			break;
		if (board[y][p_x] != -1000)
			board[y][p_x]++;
		p_x++;
	}

	p_x = x - 1;
	while (p_x >= 0 && p_x > p_x - 5)
	{
		if (!(curBoard->getBoard()[y][p_x] == 0 || curBoard->getBoard()[y][p_x] == curPlayNum))
			break;
		if (board[y][p_x] != -1000)
			board[y][p_x]++;
		p_x--;
	}
	
	if (curBoard->checkFlanks(y, x, curPlayNum) > 0)
		board[y][x] = 1000;

	if (curBoard->checkVictory(y, x, curPlayNum) == true)
		board[y][x] = 2000;
}