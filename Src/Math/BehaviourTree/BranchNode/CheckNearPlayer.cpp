#include "CheckNearPlayer.h"

#include "Math/Vector2.h"
#include "Actor/BlackBoard.h"
#include "Actor/IAgent.h"

CheckNearPlayer::CheckNearPlayer(BlackBoard* black_board, INode* true_node, INode* false_node, const float max_distance)
	: BranchNodeBase(black_board, true_node, false_node),
	mMaxDistance(max_distance) {
}

CheckNearPlayer::~CheckNearPlayer()
{
}

const bool CheckNearPlayer::is_condition()
{
	// �v���C���[�̈ʒu���擾
	auto player_pos = mpBlackBoard->get_value<Vector2>("PlayerPos");
	auto* agent = mpBlackBoard->get_value<IAgent*>("Agent");

	auto vector = player_pos - agent->get_position();

	// �߂����true��Ԃ�
	return vector.magnitude() < mMaxDistance;
}