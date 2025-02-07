#pragma once
#include "Player.h"
class AIRandomPlayer :
    public Player
{
public:
    bool MakeMove(GoBoard& goBoard);
};

