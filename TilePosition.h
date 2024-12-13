#pragma once
class TilePosition {
public:
    int x;
    int y;

    TilePosition(int _x, int _y) {
        x = _x;
        y = _y;
    };
    ~TilePosition() {};

    TilePosition Clone() {
        return TilePosition(x, y);
    }
};