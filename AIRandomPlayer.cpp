#include "AIRandomPlayer.h"
#include <cstdlib>
#include <iostream>

bool AIRandomPlayer::MakeMove(GoBoard& goBoard) {
	
	vector<Move> allMoves = goBoard.GetAllValidMoves(playerTile);
	Move randomMove = allMoves[rand() % allMoves.size()];

	if (!randomMove.pass) {
		cout << "\nMaking Move: (" << randomMove.xPos << ", " << randomMove.yPos << ")\n";
		goBoard.MakeMove(randomMove);
		return true;
	}

	cout << "\nPassing turn...\n";
	return false;
}