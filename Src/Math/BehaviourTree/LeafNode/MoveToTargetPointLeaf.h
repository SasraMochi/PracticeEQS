#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// 目標地点へと向かわせるノード
/// </summary>
class MoveToTargetPointLeaf : public LeafNodeBase {
public:
	explicit MoveToTargetPointLeaf(BlackBoard* black_board);

	~MoveToTargetPointLeaf();

	void tick() override;

	NodeResult get_node_result() const override;
};