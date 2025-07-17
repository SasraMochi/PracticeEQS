#include "CheckIsReachedTargetPoint.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

CheckIsReachedTargetPoint::CheckIsReachedTargetPoint(BlackBoard* black_board, INode* true_node, INode* false_node)
	: BranchNodeBase(black_board, true_node, false_node)
{
}

CheckIsReachedTargetPoint::~CheckIsReachedTargetPoint()
{
}

void CheckIsReachedTargetPoint::init()
{
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");
	agent->set_target_position();

	BranchNodeBase::init();
}

const bool CheckIsReachedTargetPoint::is_condition()
{
	const float cMinDiff = 5.f;

	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");
	
	auto agent_pos = agent->get_position();
	auto target_pos = mpBlackBoard->get_value<Vector2>("TargetPos");

	// ·‚ªˆê’è‹——£‚Ü‚Åk‚Ü‚Á‚Ä‚¢‚½‚çtrue‚ğ•Ô‚·
	if (Vector2::distance(agent_pos, target_pos) <= cMinDiff)
	{
		return true;
	}

	return false;
}
