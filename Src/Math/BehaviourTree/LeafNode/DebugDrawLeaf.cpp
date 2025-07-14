#include "DebugDrawLeaf.h"

#include "DxLib.h"

DebugDrawLeaf::DebugDrawLeaf(BlackBoard* black_board, int text)
	: LeafNodeBase(black_board),
	mText(text)
{

}

DebugDrawLeaf::~DebugDrawLeaf()
{
}

void DebugDrawLeaf::tick()
{
	printfDx("%i\n", mText);
}

NodeResult DebugDrawLeaf::get_node_result() const
{
	// �K��������Ԃ�
	return NodeResult::Success;
}