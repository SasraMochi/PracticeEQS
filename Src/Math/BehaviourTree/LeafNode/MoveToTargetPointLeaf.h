#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// �ڕW�n�_�ւƌ����킹��m�[�h
/// </summary>
class MoveToTargetPointLeaf : public LeafNodeBase {
public:
	explicit MoveToTargetPointLeaf(BlackBoard* black_board);

	~MoveToTargetPointLeaf();

	void tick() override;

	NodeResult get_node_result() const override;
};