#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// �~�`�U�����s���t�m�[�h
/// </summary>
class CircleAttackLeaf : public LeafNodeBase {
public:
	explicit CircleAttackLeaf(BlackBoard* black_board);
	~CircleAttackLeaf();

	void tick() override;

	NodeResult get_node_result() const override;
};