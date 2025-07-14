#pragma once

#include <string>
#include <vector>
#include "Math/Vector2.h"
#include "Math/MyRectangle.h"
#include "Math/MyTimer.h"
#include "Actor/ActorHealth.h"

class IWorld;	//���[���h���ۃC���^�[�t�F�[�X�̑O���錾
class BlackBoard;

//�A�N�^�[�N���X
class Actor {
public:
	//�R���X�g���N�^
	Actor() = default;
	//���z�f�X�g���N�^
	virtual ~Actor() = default;
	//�X�V
	virtual void update(float delta_time);
	//�x���X�V
	virtual void late_update(float delta_time);
	//�`��
	virtual void draw() const;
	//�������̕`��
	virtual void draw_transparent() const;
	//GUI�̕`��
	virtual void draw_gui() const;
	//�Փ˃��A�N�V����
	virtual void react(Actor& other);
	//���b�Z�[�W����
	virtual void handle_message(const std::string& message, void* param);
	//�Փ˔���
	void collide(Actor& other);
	//���S����
	void die();
	//���S���Ă��邩�H
	bool is_dead() const;
	//�Փ˂��Ă��邩�H
	bool is_collide(const Actor& other) const;
	//���O���擾
	const std::string& name() const;
	//�^�O�����擾
	const std::string& tag() const;
	//���݈ʒu���擾
	const Vector2& position() const;

	//�U���͂��擾
	float attack_power() const;

	//�Փ˔���f�[�^���擾
	MyRectangle collider() const;

	virtual void damage(const float damage_value);

	//�R�s�[�֎~
	Actor(const Actor& other) = delete;
	Actor& operator = (const Actor& other) = delete;

protected:
	//���[���h
	IWorld* mpWorld{ nullptr };
	//�u���b�N�{�[�h
	BlackBoard* mpBlackBoard{ nullptr };
	//�^�O��
	std::string mTag;
	//���O
	std::string mName;
	//�g�����X�t�H�[��
	Vector2 mPosition;
	//�ړ���
	Vector2 mVelocity{ 0.0f,0.0f };
	// �����蔻��
	MyRectangle mCollider;
	//�Փ˔��肪�L�����H
	bool mIsEnableCollider{ true };
	//���S�t���O
	bool mIsDead{ false };
	//�U����
	float mAttackPower{ 0.0f };
	// �̗�
	ActorHealth mHealth{ 100 };
	// �_���[�W�N�[���^�C��
	MyTimer mCoolTimer;
};