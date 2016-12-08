#include <gomoku.h>

int	minimax(Board *gameBoard, ValBoard *valBoard, Player *player, Player *otherPlayer, int beta, int alpha, int playerNum, int depth)
{
	int			*coord;
	int			placeRet;
	int			curCount;
	int			value;
	int			ret;
	bool		done;
	int			**valTemp;
	int			**boardTemp;
	int			tempCaps;
	vector<int *>	coords;

	valTemp = (int **)malloc(sizeof(int *) * BOARD_DIM);
	for (int y = 0; y < BOARD_DIM; y++)
	{
		valTemp[y] = (int *)malloc(sizeof(int) * BOARD_DIM);
		for (int x = 0; x < BOARD_DIM; x++)
		{
			valTemp[y][x] = 0;
		}
	}
	boardTemp = (int **)malloc(sizeof(int *) * BOARD_DIM);
	for (int y = 0; y < BOARD_DIM; y++)
	{
		boardTemp[y] = (int *)malloc(sizeof(int) * BOARD_DIM);
		for (int x = 0; x < BOARD_DIM; x++)
		{
			boardTemp[y][x] = 0;
		}
	}

	//cout << "DEPTH = " << depth << endl;
	curCount = 0;
	if (depth == 0)
	{
		placeRet = -1;
		valBoard->copyBoard(valTemp);
		gameBoard->copyBoard(boardTemp);
		tempCaps = player->getCaptures();
		while (placeRet == -1)
		{
			coord = player->getBestMove(gameBoard, valBoard, &curCount);
			if (coord == NULL)
				return (-2000);
			placeRet = gameBoard->placePiece(coord[0], coord[1], player);
		}
		if (placeRet == 1 && (player->getCaptures() >= 5 || otherPlayer->getCaptures() >= 5))
			return (2000);
		player->setCaptures(tempCaps);
		valBoard->setBoard(valTemp);
		gameBoard->setBoard(boardTemp);
		return (valBoard->getBoard()[coord[0]][coord[1]]);
	}
	if (playerNum == player->getPlayerNum()) //Max node
	{
		//cout << "IM HERE HOMIE!" << endl;
		ret = beta;
		coords = valBoard->fetchTiles();
		while (curCount < coords.size())
		{
			valBoard->copyBoard(valTemp);
			gameBoard->copyBoard(boardTemp);
			tempCaps = player->getCaptures();
			placeRet = gameBoard->placePiece(coords.at(curCount)[1], coords.at(curCount)[2], player);
			if (placeRet != -1)
			{
				if (placeRet == 1)
					valBoard->placePiece(coords.at(curCount)[1], coords.at(curCount)[2], gameBoard, true);
				else
					valBoard->placePiece(coords.at(curCount)[1], coords.at(curCount)[2], gameBoard, false);
				if (player->getCaptures() >= 5)
					return (2000);
				value = minimax(gameBoard, valBoard, player, otherPlayer, beta, alpha, (playerNum == 1 ? 2 : 1), depth - 1);
				//cout << value << endl;
				if (value > ret || ret == 3000)
					ret = value;
				if (ret > alpha || alpha == -3000)
					alpha = ret;
				player->setCaptures(tempCaps);
				valBoard->setBoard(valTemp);
				gameBoard->setBoard(boardTemp);
				if (beta <= alpha)
					return (alpha);
			}
			curCount++;
		}
		return (ret);
	}
	else
	{
		//cout << "IM HERE BRO!" << endl;
		ret = alpha;
		coords = valBoard->fetchTiles();
		while (curCount < coords.size())
		{
			valBoard->copyBoard(valTemp);
			gameBoard->copyBoard(boardTemp);
			tempCaps = otherPlayer->getCaptures();
			placeRet = gameBoard->placePiece(coords.at(curCount)[1], coords.at(curCount)[2], otherPlayer);
			if (placeRet != -1)
			{
				if (placeRet == 1)
					valBoard->placePiece(coords.at(curCount)[1], coords.at(curCount)[2], gameBoard, true);
				else
					valBoard->placePiece(coords.at(curCount)[1], coords.at(curCount)[2], gameBoard, false);
				if (otherPlayer->getCaptures() >= 5)
					return (2000);
				//cout << "I DIDNT BREAK IT!" << endl;
				value = minimax(gameBoard, valBoard, player, otherPlayer, beta, alpha, (playerNum == 1 ? 2 : 1), depth - 1);
				if (value < ret || ret == -3000)
					ret = value;
				if (ret < beta || beta == 3000)
					beta = ret;
				otherPlayer->setCaptures(tempCaps);
				valBoard->setBoard(valTemp);
				gameBoard->setBoard(boardTemp);
				if (beta <= alpha)
					return (beta);
			}
			curCount++;
		}
		return (ret);
	}
}