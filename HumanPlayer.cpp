#include "HumanPlayer.h"
#include <iostream>

using namespace std;

void HumanPlayer::MakeMove(GoBoard& goBoard) {

    int boardSize = goBoard.GetBoardSize();
    int xPos = -1, yPos = -1;

    bool repeated = false;

    do
    {
        if (repeated) {
            cout << "Invalid position!  Please input a value on the board, not occupied, and not in occupied territory.\n";
        }
        repeated = true;
        cout << "\nIt's your turn!\n Please input a valid coordinate on the grid to place your tile:\nX position:";
        cin >> xPos;
        cout << "\nY position:";
        cin >> yPos;
        cout << "\n";
    } while (xPos < 0 || xPos >= boardSize || yPos < 0 || yPos >= boardSize
        && goBoard.ValidMove(playerTile, xPos, yPos));

    goBoard.PlaceTile(playerTile, xPos, yPos);
}