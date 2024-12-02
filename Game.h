#pragma once
#include "Player.h"
#include "GoBoard.h"

class Game {

    Player& player1;
    Player& player2;

    GoBoard goBoard;

public:
    Game(Player& playerOne, Player& playerTwo, int boardSize = 9)
        : player1(playerOne), player2(playerTwo), goBoard(boardSize)
    {
        player1.playerTile = Black;
        player2.playerTile = White;
    };

    void PlayGame();
};

