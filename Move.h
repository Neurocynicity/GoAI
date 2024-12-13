#pragma once
#include "TileState.h"

class Move
{
public:
	TileState playerTile;
	int xPos, yPos;

	Move() {
		playerTile = NotOccupied;
		xPos = yPos = -1;
	}
	Move(TileState _playerTile, int _xPos, int _yPos) {
		playerTile = _playerTile;
		xPos = _xPos;
		yPos = _yPos;
	}
	~Move();
};

