#pragma once
#include <vector>
#include "GoBoard.h"

class AIMonteCarloTreeNode
{
	GoBoard boardState;
	AIMonteCarloTreeNode* parent;
	std::vector<AIMonteCarloTreeNode&> children;
	int turnNumber;
	int visitCount;
	float value;
public:
	Move moveFromParent;
	vector<Move> untriedActions;
	vector<Move> validActions;

	AIMonteCarloTreeNode(GoBoard& _boardState, int _turnNumber)
		: boardState(_boardState) {
		boardState = _boardState;
		turnNumber = _turnNumber;
		parent = nullptr;
		visitCount = value = 0;
		CalculateActions();
	}
	AIMonteCarloTreeNode(GoBoard& _boardState, int _turnNumber, AIMonteCarloTreeNode* _parent, Move _move)
		: boardState(_boardState) {
		boardState = _boardState;
		turnNumber = _turnNumber;
		parent = _parent;
		moveFromParent = _move;
		visitCount = value = 0;
		CalculateActions();
	}

	void CalculateActions() {
		validActions = untriedActions = boardState.GetAllValidMoves(turnNumber % 2 == 0 ? Black : White);
	}

	int Value() { return value; }
	int VisitCount() { return visitCount; }

	bool IsFullyExpanded() { return untriedActions.size() == 0; }

	bool IsTerminalNode();

	AIMonteCarloTreeNode& Expand();
	AIMonteCarloTreeNode& Rollout();
	void Backpropagate(float result);

	Move RolloutPolicy() { return validActions[rand() % validActions.size()]; }
	AIMonteCarloTreeNode& TreePolicy();

	Move GetBestMove(int simulationIterations = 100);
};

