#include "GoBoard.h"
#include "TileState.h"
#include "Move.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

GoBoard::GoBoard(int size) {
	mSize = size;
	mBoardContents.assign(size, vector<TileState>(size, NotOccupied));
}

GoBoard::GoBoard(vector<vector<TileState>> contents, vector<vector<vector<TileState>>> previousBoardStates) {
	mBoardContents = contents;
	mPreviousBoardStates = previousBoardStates;
}

GoBoard GoBoard::Clone() {
	return GoBoard(mBoardContents, mPreviousBoardStates);
}

void GoBoard::PrintRow() {
	cout << "  ";

	for (int x = 0; x < mSize; x++)
	{
		cout << x << '-';
	}

	cout << "\n";
}

void GoBoard::PrintBoard() {

	PrintRow();

	cout << "  ";

	for (int x = 0; x < mSize; x++)
	{
		cout << '|' << ' ';
	}

	cout << '\n';

	for (int y = mSize - 1; y >= 0; y--)
	{
		cout << y << ' ';

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

			cout << '-';
		}

		cout << y << '\n';
	}

	cout << "  ";

	for (int x = 0; x < mSize; x++)
	{
		cout << '|' << ' ';
	}

	cout << '\n';

	PrintRow();
}

bool GoBoard::PositionOccupied(int xPos, int yPos) {
	return mBoardContents[xPos][yPos] != NotOccupied;
}

bool GoBoard::ValidMove(Move move)
{
	return !PositionOccupied(move.xPos, move.yPos)
		&& !MoveResultsInImmediateSelfCapture(move)
		&& !MoveResultsInPreviousBoardState(move);
}

bool GoBoard::MoveResultsInPreviousBoardState(Move move) {
	return false;
}

bool GoBoard::MoveResultsInImmediateSelfCapture(Move move) {
	GoBoard boardAfterMove = Clone();
	boardAfterMove.MakeMove(move);

	vector<vector<bool>> tilesCalculated(mSize, vector<bool>(mSize, false));
	return !EvaluateStringLiberties(move.xPos, move.yPos, move.playerTile, tilesCalculated);
}

void GoBoard::EvaluateTileTerritory(int depth, int xPos, int yPos,
	vector<vector<TileState>>& tileTerritories, vector<vector<bool>>& tileEvaluated,
	vector<TilePosition>& tilesInTerritory, TileState& foundWall, TileState& territoryOwner, bool& foundOwner)
{

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

			stack<TilePosition> tilesToEvaluate;

			while (tilesToEvaluate.size() > 0)
			{
				TilePosition position = tilesToEvaluate.top();
				tilesInTerritory.push_back(position.Clone());
				tilesToEvaluate.pop();

				for (int deltaX = -1; deltaX <= 1; deltaX++)
				{
					for (int deltaY = -1; deltaY <= 1; deltaY++)
					{
						// make sure we're only checking the orthoganal vectors
						// [(-1, 0), (0, -1), (0, 1), (1, 0)]
						if (abs(deltaX + deltaY) != 1) {
							continue;
						}

						int newXPos = position.x + deltaX;
						int newYPos = position.y + deltaY;

						// also skip evaluating tile if it's out of bounds
						if (newXPos < 0 || newXPos >= mSize ||
							newYPos < 0 || newYPos >= mSize) {
							continue;
						}

						// if it's empty, add tile to territory and check all their unchecked neighbours
						if (mBoardContents[newXPos][newYPos] == NotOccupied) {

							// skip if the tile has already been calculated
							if (tileCalculated[newXPos][newYPos]) {
								continue;
							}

							// mark this tile as evaluated to prevent infinate recursion
							tileCalculated[newXPos][newYPos] = true;

							tilesToEvaluate.push(TilePosition(newXPos, newYPos));
						}
						// if it's the first wall we've found, then we set the found wall to be this one
						else if (foundWall == NotOccupied) {
							foundWall = mBoardContents[newXPos][newYPos];
						}
						// if we've found another wall of a different player
						else if (mBoardContents[newXPos][newYPos] != foundWall) {
							// this territory is unclaimed land, as there are both white and black walls
							territoryOwner = NotOccupied;
							foundOwner = true;
						}
					}
				}
			}

			if (!foundOwner && foundWall != NotOccupied) {
				foundOwner = true;
				territoryOwner = foundWall;
			}

			if (territoryOwner != NotOccupied) {
				for (TilePosition tile : tilesInTerritory)
				{
					tileTerritory[tile.x][tile.y] = territoryOwner;
				}
			}
		}
	}

	return tileTerritory;
}

bool GoBoard::EvaluateStringLiberties(int xPos, int yPos, TileState stringState, vector<vector<bool>>& tilesCalculated) {

	bool foundLiberty = false;
	vector<TilePosition> tilesInString;
	stack<TilePosition> positionsToEvaluate;
	positionsToEvaluate.push(TilePosition(xPos, yPos));

	while (positionsToEvaluate.size() > 0)
	{
		TilePosition position = positionsToEvaluate.top();
		tilesInString.push_back(position.Clone());
		positionsToEvaluate.pop();

		tilesCalculated[position.x][position.y] = true;

		for (int deltaX = -1; deltaX <= 1; deltaX++)
		{
			for (int deltaY = -1; deltaY <= 1; deltaY++)
			{
				// make sure we're only checking the orthoganal vectors
				// [(-1, 0), (0, -1), (0, 1), (1, 0)]
				if (abs(deltaX + deltaY) != 1) {
					continue;
				}

				int newXPos = position.x + deltaX;
				int newYPos = position.y + deltaY;

				// also skip evaluating tile if it's out of bounds
				if (newXPos < 0 || newXPos >= mSize ||
					newYPos < 0 || newYPos >= mSize) {
					continue;
				}

				// if it's the save type as the string, then it's also part of the string
				if (mBoardContents[newXPos][newYPos] == stringState &&
					!tilesCalculated[newXPos][newYPos]) {
					positionsToEvaluate.push(TilePosition(newXPos, newYPos));
				}
				else if (mBoardContents[newXPos][newYPos] == NotOccupied) {
					foundLiberty = true;
				}
			}
		}
	}

	if (!foundLiberty) {
		for (TilePosition position : tilesInString) {
			mBoardContents[position.x][position.y] = NotOccupied;
		}
	}

	return foundLiberty;
}

void GoBoard::EvaluateLiberties()
{
	stack<TilePosition> tilesToEvaluate;
	vector<vector<bool>> tilesCalculated(mSize, vector<bool>(mSize, false));

	for (int x = 0; x < mSize; x++)
	{
		for (int y = 0; y < mSize; y++)
		{
			if (mBoardContents[x][y] == NotOccupied || tilesCalculated[x][y]) {
				continue;
			}

			EvaluateStringLiberties(x, y, mBoardContents[x][y], tilesCalculated);
		}
	}
}

void GoBoard::MakeMove(Move move)
{
	mBoardContents[move.xPos][move.yPos] = move.playerTile;
}

vector<Move> GoBoard::GetAllValidMoves(TileState colourToGetMovesFor) {
	vector<Move> validMoves;

	validMoves.push_back(Move(colourToGetMovesFor, true));

	for (int x = 0; x < mSize; x++)
	{
		for (int y = 0; y < mSize; y++)
		{
			Move move = Move(colourToGetMovesFor, x, y);
			if (ValidMove(move))
				validMoves.push_back(move);
		}
	}

	return validMoves;
}