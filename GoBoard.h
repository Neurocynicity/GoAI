#pragma once
#include "TileState.h"
#include "Move.h"
#include <vector>

using namespace std;

class TilePosition {
public:
    int x;
    int y;

    TilePosition(int _x, int _y) {
        x = _x;
        y = _y;
    };
    ~TilePosition() {};
};

class GoBoard {

    int mSize;
    vector<vector<TileState>> mBoardContents;
    vector<vector<vector<TileState>>> mPreviousBoardStates;

public:
    GoBoard(int size);
    GoBoard(vector<vector<TileState>> contents, vector<vector<vector<TileState>>> previousBoardStates);
    ~GoBoard();
    GoBoard Clone();
    void PrintBoard();
    void PrintRow();
    int GetBoardSize() { return mSize; };
    bool PositionOccupied(int xPos, int yPos);
    bool MoveResultsInImmediateSelfCapture(Move move);
    bool MoveResultsInPreviousBoardState(Move move);

    bool ValidMove(Move move);
    void MakeMove(Move move);

    void EvaluateTileTerritory(int depth, int xPos, int yPos,
        vector<vector<TileState>>& tileTerritories, vector<vector<bool>>& tileEvaluated,
        vector<TilePosition>& tilesInTerritory,
        TileState& foundWall, TileState& territoryOwner, bool& foundOwner);

    vector<vector<TileState>> EvaluateTileTerritories();

    bool EvaluateStringLiberties(int xPos, int yPos, TileState stringState, vector<vector<bool>>& tileCalculated, int depth);
    void EvaluateLiberties();
    void EvaluatePossibleCaptures();
};