#include <Player.class.h>

Player::Player(int playerNum)
{
	this->playerNum = playerNum;
	this->captures = 0;
}

int		*Player::getBestMove(Board *gameBoard, ValBoard *valBoard, int *curMove)
{
	int				*ret;
	int				*coord;
	vector<int*>	tiles;

	ret = (int *)malloc(sizeof(int) * 2);
	tiles = valBoard->fetchTiles();
	if (tiles.size() == 0 || *curMove >= tiles.size())
	{
		return (NULL);
	}
	coord = tiles[*curMove];
	*curMove = *curMove + 1;
	ret[0] = coord[1];
	ret[1] = coord[2];
	return (ret);
}
