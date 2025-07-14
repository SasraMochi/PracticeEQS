#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// �K�����s��Ԃ��f�o�b�O�p�t�m�[�h
/// </summary>
class AlwaysFailLeaf : public LeafNodeBase {
public:
	explicit AlwaysFailLeaf(BlackBoard* black_board) : LeafNodeBase(black_board) {}

	~AlwaysFailLeaf() override = default;

	NodeResult get_node_result() const override {
		return NodeResult::Fail;
	}
};