#include "CircleAttackLeaf.h"

#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

#include "DxLib.h"
CircleAttackLeaf::CircleAttackLeaf(BlackBoard* black_board)
	: LeafNodeBase(black_board)
{
}

CircleAttackLeaf::~CircleAttackLeaf()
{
}

void CircleAttackLeaf::tick()
{
	// �U��
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");
	agent->attack();
}

NodeResult CircleAttackLeaf::get_node_result() const
{
	// �K��������Ԃ�
	return NodeResult::Success;
}
