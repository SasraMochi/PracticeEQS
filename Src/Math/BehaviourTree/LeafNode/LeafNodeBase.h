#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// �t�m�[�h�̊��N���X
/// </summary>
class LeafNodeBase : public NodeBase {
protected:
	explicit LeafNodeBase(BlackBoard* black_board) : NodeBase{ black_board } {}
	virtual ~LeafNodeBase() = default;
};