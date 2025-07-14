#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// �K��������Ԃ��t�m�[�h
/// </summary>
class AlwaysSuccessLeaf : public LeafNodeBase {
public:
	explicit AlwaysSuccessLeaf(BlackBoard* black_board) : LeafNodeBase(black_board) {}

	~AlwaysSuccessLeaf() override = default;

	NodeResult get_node_result() const override {
		return NodeResult::Success;
	}
};