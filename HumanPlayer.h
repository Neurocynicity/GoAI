#pragma once
#include "Player.h"
class HumanPlayer :
    public Player
{
public:
    bool MakeMove(GoBoard& goBoard);
};

