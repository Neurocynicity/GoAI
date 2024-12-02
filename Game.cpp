#include "Game.h"
#include "GoBoard.h"
#include <iostream>

using namespace std;

void Game::PlayGame() {

    for (int turnNumber = 0; turnNumber < 100; turnNumber++)
    {
        cout << "Here's the state of the board:\n";
        goBoard.PrintBoard();

        if (turnNumber % 2 == 0) {
            cout << "It's Black's turn!";

            player1.MakeMove(goBoard);
        }
        else {
            cout << "It's White's turn!";

            player2.MakeMove(goBoard);
        }
    }
}