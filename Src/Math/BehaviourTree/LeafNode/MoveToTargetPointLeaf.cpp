#include "MoveToTargetPointLeaf.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

MoveToTargetPointLeaf::MoveToTargetPointLeaf(BlackBoard* black_board)
	: LeafNodeBase(black_board)
{
}

MoveToTargetPointLeaf::~MoveToTargetPointLeaf()
{
}

void MoveToTargetPointLeaf::tick()
{
	// �v���C���[�̈ʒu���擾
	auto target_pos = mpBlackBoard->get_value<Vector2>("TargetPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = target_pos - agent->get_position();

	agent->move_towards(vector.normalized(), 3.25f);
}

NodeResult MoveToTargetPointLeaf::get_node_result() const
{
	// �K��������Ԃ�
	return NodeResult::Success;
}
