#pragma once
#include <vector>

using namespace std;

enum TileState {
    NotOccupied,
    Black,
    White
};

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

public:
    GoBoard(int size);
    ~GoBoard();
    void PrintBoard();
    void PrintRow();
    int GetBoardSize() { return mSize; };

    bool ValidMove(TileState playerTile, int xPos, int yPos);
    void PlaceTile(TileState playerTile, int xPos, int yPos);

    void EvaluateTileTerritory(int depth, int xPos, int yPos,
        vector<vector<TileState>>& tileTerritories, vector<vector<bool>>& tileEvaluated,
        vector<TilePosition>& tilesInTerritory,
        TileState& foundWall, TileState& territoryOwner, bool& foundOwner);

    vector<vector<TileState>> EvaluateTileTerritories();
    void EvaluatePossibleCaptures();
};