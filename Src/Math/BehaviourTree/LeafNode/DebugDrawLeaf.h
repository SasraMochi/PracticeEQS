#pragma once

#include <string>
#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// �����̃f�o�b�O�`����s���t�m�[�h
/// </summary>
class DebugDrawLeaf : public LeafNodeBase {
public:
	explicit DebugDrawLeaf(BlackBoard* black_board, int text);

	~DebugDrawLeaf();

	void tick() override;

	NodeResult get_node_result() const override;

private:
	int mText;
};