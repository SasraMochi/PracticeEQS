#pragma once

#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// �u�����`�m�[�h�̊��N���X
/// </summary>
class BranchNodeBase : public NodeBase {
public:
	explicit BranchNodeBase(BlackBoard* black_board, INode* true_node, INode* false_node);
	virtual ~BranchNodeBase();

	virtual void init() override;
	virtual void tick() override;
	virtual void finalize() override;

	int get_running_node_id() const override;

protected:
	// �����𖞂����Ă��邩   
	virtual const bool is_condition() = 0;
	
protected:
	INode* mpBranchNodes[2] = { nullptr, nullptr }; // �u�����`�m�[�h�̔z��
	int mSatisfyIndex = -1; // �����𖞂����Ă���m�[�h�̃C���f�b�N�X
};
