#include "GoBoard.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

GoBoard::GoBoard(int size) {
    mSize = size;
    mBoardContents.assign(size, vector<TileState>(size, NotOccupied));
}

GoBoard::~GoBoard() {

}

void GoBoard::PrintRow() {
    cout << ' ';

    for (int x = 0; x < mSize; x++)
    {
        cout << x;
    }

    cout << '\n';
}

void GoBoard::PrintBoard() {

    PrintRow();

    for (int y = mSize - 1; y >= 0; y--)
    {
        cout << y;

        for (int x = 0; x < mSize; x++)
        {
            if (mBoardContents[x][y] == Black) {
                cout << "B";
            }
            else if (mBoardContents[x][y] == White) {
                cout << "W";
            }
            else {
                cout << "+";
            }
        }

        cout << y << '\n';
    }

    PrintRow();
}

bool GoBoard::ValidMove(TileState playerTile, int xPos, int yPos)
{
    return true;
}

void GoBoard::EvaluateTileTerritory(int depth, int xPos, int yPos,
    vector<vector<TileState>>& tileTerritories, vector<vector<bool>>& tileEvaluated,
    vector<TilePosition>& tilesInTerritory, TileState& foundWall, TileState& territoryOwner, bool& foundOwner)
{
    for (int deltaX = -1; deltaX <= 1; deltaX++)
    {
        for (int deltaY = -1; deltaY <= 1; deltaY++)
        {
            // make sure we're only checking the orthoganal vectors
            // [(-1, 0), (0, -1), (0, 1), (1, 0)]
            if (abs(deltaX + deltaY) != 1) {
                continue;
            }

            int newXPos = xPos + deltaX;
            int newYPos = yPos + deltaY;

            // also skip evaluating tile if it's out of bounds
            if (newXPos < 0 || newXPos >= mSize ||
                newYPos < 0 || newYPos >= mSize) {
                continue;
            }

            // mark this tile as evaluated to prevent infinate recursion
            tileEvaluated[newXPos][newYPos] = true;

            // if it's empty, add tile to territory and check all their unchecked neighbours
            if (mBoardContents[newXPos][newYPos] == NotOccupied) {

                // skip if the tile has already been calculated
                if (tileEvaluated[newXPos][newYPos]) {
                    continue;
                }

                tilesInTerritory.push_back(TilePosition(newXPos, newYPos));
                EvaluateTileTerritory(depth + 1, newXPos, newYPos, tileTerritories, tileEvaluated, tilesInTerritory, foundWall, territoryOwner, foundOwner);
            }
            // if it's the first wall we've found, then we set the found wall to be this one
            else if (foundWall == NotOccupied) {
                foundWall = mBoardContents[newXPos][newYPos];
            }
            // if we've found another wall of a different player
            else if (tileEvaluated[newXPos][newYPos] != foundWall) {
                // this territory is unclaimed land, as there are both white and black walls
                territoryOwner = NotOccupied;
                foundOwner = true;
            }
        }
    }

    // only once we've fully explored the territory of the area, we mark who owns it
    if (depth == 0) {
        if (!foundOwner && foundWall != NotOccupied) {
            foundOwner = true;
            territoryOwner = foundWall;
        }
        else {
            cout << "ERROR: No owner found for territory!\n";
        }
    }
}

vector<vector<TileState>> GoBoard::EvaluateTileTerritories()
{
    vector<vector<TileState>> tileTerritory(mSize, vector<TileState>(mSize, NotOccupied));
    vector<vector<bool>> tileCalculated(mSize, vector<bool>(mSize, false));

    for (int x = 0; x < mSize; x++)
    {
        for (int y = 0; y < mSize; y++)
        {
            if (mBoardContents[x][y] != NotOccupied || tileCalculated[x][y]) {
                continue;
            }

            vector<TilePosition> tilesInTerritory = vector<TilePosition>();
            TileState foundWall = NotOccupied;
            TileState territoryOwner = NotOccupied;
            bool foundOwner = false;

            EvaluateTileTerritory(0, x, y, tileTerritory, tileCalculated, tilesInTerritory, foundWall, territoryOwner, foundOwner);
        }
    }

    return tileTerritory;
}

void GoBoard::EvaluatePossibleCaptures()
{
    auto tileTerritory = EvaluateTileTerritories();

    cout << "Tile Territories:\n";

    PrintRow();

    for (int y = mSize - 1; y >= 0; y--)
    {
        cout << y;

        for (int x = 0; x < mSize; x++)
        {
            if (tileTerritory[x][y] == Black) {
                cout << "B";
            }
            else if (tileTerritory[x][y] == White) {
                cout << "W";
            }
            else {
                cout << "+";
            }
        }

        cout << y << '\n';
    }

    PrintRow();
}

void GoBoard::PlaceTile(TileState playerTile, int xPos, int yPos)
{
    mBoardContents[xPos][yPos] = playerTile;
    EvaluatePossibleCaptures();
}