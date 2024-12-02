#pragma once
#include "GoBoard.h"

class Player {
public:
    TileState playerTile;
    Player() {};
    ~Player() {};
    virtual void MakeMove(GoBoard& goBoard) = 0;
};