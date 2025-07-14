#pragma once

#include "Actor/Actor.h"
#include "UI/BarGauge.h"
#include "Math/MyTimer.h"
#include "Actor/ActorHealth.h"

class Player : public Actor{
const float cCoolTime = 60.f;

public:
	// �R���X�g���N�^
	Player();

	// �f�X�g���N�^
	~Player();

	// �X�V
	virtual void update(float delta_time);

	// �`��
	virtual void draw() const;

	//�������̕`��
	virtual void draw_transparent() const;

	//GUI�̕`��
	virtual void draw_gui() const;

	// �Փ˃��A�N�V����
	virtual void react(Actor& other) override;

private:
	float mSpeed = 4.f;

	BarGauge mHealthBar;
};