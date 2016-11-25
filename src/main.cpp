#include <gomoku.h>

int	main()
{
	Board	*gameBoard;
	Player	*player1;
	Player	*player2;
	int		x;
	int		y;
	int		player;
	int		ret;

	gameBoard = new Board(BOARD_DIM);

	player1 = new Player(1);
	player2 = new Player(2);

	ret = 0;
	while (ret != 1)
	{
		gameBoard->printBoard();
		cout << "Make a move: [player num] [x coord] [y coord]" << endl;
		cin >> player >> x >> y;
		if (player == 1)
		{
			ret = gameBoard->placePiece(y - 1, x - 1, player1);
		}
		else
		{
			ret = gameBoard->placePiece(y - 1, x - 1, player2);
		}
		if (ret == -1)
			cout << "Invalid move" << endl;
		if (ret == 1)
			cout << "Player " << player << " wins!" << endl;
	}

}