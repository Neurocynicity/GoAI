#include "HumanPlayer.h"
#include "Move.h"
#include <iostream>
#include <string>

using namespace std;

bool HumanPlayer::MakeMove(GoBoard& goBoard) {

    int boardSize = goBoard.GetBoardSize();
    int xPos = -1, yPos = -1;
    string input;

    Move move;
    bool moveValid = true;
    bool repeated = false;
    string reason = "";

    do
    {
        if (repeated) {
            cout << "Invalid position: " + reason + "\nPlease input a value:\n-On the board\n-Not occupied by a stone\n-That doesn't repeat a board state\n-That doesn't result in immediate self-capture.\n";
        }
        repeated = true;
        cout << "\nIt's your turn!\n Please input a valid coordinate on the grid to place your tile or pass to pass your turn:\nX position:";
        cin >> input;
        try {
            xPos = stoi(input);
        }
        catch (invalid_argument x) { }

        if (input == "pass") {
            return false;
        }

        cout << "\nY position:";
        cin >> input;
        try {
            yPos = stoi(input);
        }
        catch (invalid_argument x) {}

        cout << "\n";

        move = Move(playerTile, xPos, yPos);
        moveValid = true;

        if (xPos < 0 || xPos >= boardSize || yPos < 0 || yPos >= boardSize) {
            moveValid = false;
            reason = "Position (" + to_string(xPos) + ", " + to_string(yPos) + ") is off the grid.";
        }
        else if (goBoard.PositionOccupied(xPos, yPos)) {
            moveValid = false;
            reason = "Position (" + to_string(xPos) + ", " + to_string(yPos) + ") is already occupied by a stone.";
        }
        else if (!goBoard.ValidMove(move)) {
            moveValid = false;
            reason = "Move would result in immediate self-capture";
        }
    } while (!moveValid);

    goBoard.MakeMove(move);
    return true;
}