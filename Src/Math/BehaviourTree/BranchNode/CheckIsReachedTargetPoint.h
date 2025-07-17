#pragma once

#include "Math/BehaviourTree/BranchNode/BranchNodeBase.h"

class CheckIsReachedTargetPoint : public BranchNodeBase {
public:
	explicit CheckIsReachedTargetPoint(BlackBoard* black_board, INode* true_node, INode* false_node);

	~CheckIsReachedTargetPoint();

	void init() override final;

private:
	const bool is_condition() override;
};