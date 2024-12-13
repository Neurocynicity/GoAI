#pragma once
#include "GoBoard.h"

class Player {
public:
    TileState playerTile;
    Player() { playerTile = Black; };
    ~Player() {};
    virtual void MakeMove(GoBoard& goBoard) = 0;
};