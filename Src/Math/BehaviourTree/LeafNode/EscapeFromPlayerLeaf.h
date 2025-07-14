#pragma once

#include "Math/BehaviourTree/LeafNode/LeafNodeBase.h"

/// <summary>
/// �v���C���[���瓦����t�m�[�h
/// </summary>
class EscapeFromPlayerLeaf : public LeafNodeBase {
public:
	explicit EscapeFromPlayerLeaf(BlackBoard* black_board);

	~EscapeFromPlayerLeaf();

	void tick() override;

	NodeResult get_node_result() const override;
};