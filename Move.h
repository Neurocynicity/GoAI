#pragma once
#include "TileState.h"

class Move
{
public:
	TileState playerTile;
	bool pass;
	int xPos, yPos;

	Move() {
		playerTile = NotOccupied;
		xPos = yPos = -1;
		pass = false;
	}
	Move(TileState _playerTile, int _xPos, int _yPos) {
		playerTile = _playerTile;
		xPos = _xPos;
		yPos = _yPos;
		pass = false;
	}
	Move(TileState _playerTile, bool _pass) {
		playerTile = _playerTile;
		xPos = yPos = -1;
		pass = _pass;
	}
	~Move() {};

	bool operator==(Move other) {

	}
};

