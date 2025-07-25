#pragma once

#include "Actor/Actor.h"

class AttackCollider : public Actor {
public:
	AttackCollider(IWorld* world, MyRectangle& collider,
		const std::string& owner_tag = "",
		float lifespan = 1.0f,
		float attack_power = 0.0f
	);

	~AttackCollider();

	void update(float delta_time) override;
	void draw() const override;
	void draw_gui() const override;
	void react(Actor& other) override;

private:
	// 親のタグ
	std::string mOwnerTag;

	// 生存時間
	float mLifeSpan;
};