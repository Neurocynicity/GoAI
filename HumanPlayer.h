#pragma once
#include "Player.h"
class HumanPlayer :
    public Player
{
public:
    void MakeMove(GoBoard& goBoard);
};

