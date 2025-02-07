#include "Game.h"
#include "GoBoard.h"
#include <iostream>

using namespace std;

void Game::PlayGame() {

    int consecutivePasses = 0;

    for (int turnNumber = 0; turnNumber < 100; turnNumber++)
    {

        cout << "Here's the state of the board:\n";
        goBoard.PrintBoard();

        if (turnNumber % 2 == 0) {
            cout << "It's Black's turn!";

            if (player1.MakeMove(goBoard))
                consecutivePasses = 0;
            else
                consecutivePasses++;
        }
        else {
            cout << "It's White's turn!";

            if (player2.MakeMove(goBoard))
                consecutivePasses = 0;
            else
                consecutivePasses++;
        }

        // if both players have passed then end the game
        if (consecutivePasses >= 2) {
            cout << "Both players have passed!  The game is over!";
            break;
        }
    }
}