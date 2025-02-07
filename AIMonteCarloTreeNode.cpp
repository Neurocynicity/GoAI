#include "AIMonteCarloTreeNode.h"

bool AIMonteCarloTreeNode::IsTerminalNode() {

}

AIMonteCarloTreeNode& AIMonteCarloTreeNode::Expand() {
	Move moveToTry = untriedActions.back();
	untriedActions.pop_back();

	GoBoard newBoardState = GoBoard(boardState);
	newBoardState.MakeMove(moveToTry);

	AIMonteCarloTreeNode newChildNode = AIMonteCarloTreeNode(newBoardState, turnNumber + 1, this, moveToTry);

	children.push_back(newChildNode);
	return newChildNode;
}
AIMonteCarloTreeNode& AIMonteCarloTreeNode::Rollout() {
	if (IsTerminalNode())
		return *this;

	Move randomlyChosenMove = RolloutPolicy();

	AIMonteCarloTreeNode* childNode;

	if (children.size() > 0) {
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i].moveFromParent == randomlyChosenMove)
			{
				childNode = &children[i];
				break;
			}
		}
	}

	if (childNode == )

}
void AIMonteCarloTreeNode::Backpropagate(float result) {

}

AIMonteCarloTreeNode& AIMonteCarloTreeNode::TreePolicy() {

}

Move AIMonteCarloTreeNode::GetBestMove(int simulationIterations = 100) {

}