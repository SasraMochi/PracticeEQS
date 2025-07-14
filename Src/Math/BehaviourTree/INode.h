#pragma once
#include "NodeResult.h"

/// <summary>
/// �m�[�h�̃C���^�[�t�F�[�X
/// </summary>
class INode {
public:
	// ���z�f�X�g���N�^
	virtual ~INode() = default;
	// ������
	virtual void init() = 0;
	// ����
	virtual void tick() = 0;
	// �㏈��
	virtual void finalize() = 0;
	// �m�[�h�̏�Ԃ��擾
	virtual NodeResult get_node_result() const = 0;
	// �m�[�h��ID��ۑ�
	virtual void set_node_id(const int id) = 0;
	// ���ݓ��쒆�̃m�[�h��ID���擾
	virtual int get_running_node_id() const = 0;
};