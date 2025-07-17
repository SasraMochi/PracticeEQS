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
	// プレイヤーの位置を取得
	auto target_pos = mpBlackBoard->get_value<Vector2>("TargetPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = target_pos - agent->get_position();

	agent->move_towards(vector.normalized(), 3.25f);
}

NodeResult MoveToTargetPointLeaf::get_node_result() const
{
	// 必ず成功を返す
	return NodeResult::Success;
}
