#pragma once
#include "GoBoard.h"

class Player {
public:
    TileState playerTile;
    Player() { playerTile = Black; };
    ~Player() {};
    virtual bool MakeMove(GoBoard& goBoard) = 0;
};