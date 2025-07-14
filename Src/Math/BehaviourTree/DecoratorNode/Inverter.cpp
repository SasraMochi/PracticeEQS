#include "Inverter.h"

#include <assert.h>

Inverter::Inverter(BlackBoard* black_board, INode* child_node)
	: DecoratorNodeBase(black_board)
{
	set_node(child_node);
}

Inverter::~Inverter()
{
}

void Inverter::tick()
{
	// �q�m�[�h�����s
	mChildNode->tick();
	// �q�m�[�h�̌��ʂ��擾
	NodeResult result = mChildNode->get_node_result();
	// ���ʂ𔽓]������
	if (result == NodeResult::Success) {
		mNodeResult = NodeResult::Fail;
		return;
	}
	else if (result == NodeResult::Fail) {
		mNodeResult = NodeResult::Success;
		return;
	}

	// �q�m�[�h�����s���̏ꍇ�́AInverter�����s���ɂ���
	mNodeResult = NodeResult::Running;
}
