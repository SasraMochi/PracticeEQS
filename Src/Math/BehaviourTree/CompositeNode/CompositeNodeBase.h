#pragma once

#include <vector>
#include "Math/BehaviourTree/NodeBase.h"

/// <summary>
/// �R���|�W�b�g�m�[�h�̊��N���X
/// </summary>
class CompositeNodeBase : public NodeBase {
public:
	explicit CompositeNodeBase(BlackBoard* black_board) : NodeBase(black_board) {
	};

	virtual ~CompositeNodeBase();

	virtual void init() override;
	virtual void finalize() override;

	void add_node(INode* node);

	int get_running_node_id() const override;

protected:
	// �h���N���X�Ŏ���
	virtual const int get_next_index() const = 0;
	virtual void node_increment() = 0;

protected:
	// �q�m�[�h�Q
	std::vector<INode*> mChildNodes;
	// ���ݓ������Ă���m�[�h�̃C���f�b�N�X
	int mRunningNodeIndex{ 0 };
};