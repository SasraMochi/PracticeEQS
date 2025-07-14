#include "Actor.h"

void Actor::update(float delta_time){}

void Actor::late_update(float delta_time){}

void Actor::draw() const{}

void Actor::draw_transparent() const{}

void Actor::draw_gui() const{}

void Actor::react(Actor& other){}

void Actor::handle_message(const std::string& message, void* param){}

void Actor::collide(Actor& other){
    //�ǂ���̃A�N�^�[���Փ˔��肪�L�����H
    if (mIsEnableCollider && other.mIsEnableCollider) {
        //�Փ˔��������
        if (is_collide(other)) {
            //�Փ˂����ꍇ�́A���݂��ɏՓ˃��A�N�V����������
            react(other);
            other.react(*this);
        }
    }
}

void Actor::die(){
    mIsDead = true;
}

bool Actor::is_dead() const{
    return mIsDead;
}

bool Actor::is_collide(const Actor& other) const
{
    return collider().intersects(other.collider());
}

const std::string& Actor::name() const{
    return mName;
}

const std::string& Actor::tag() const{
    return mTag;
}

const Vector2& Actor::position() const
{
    return mPosition;
}

//�U���͂��擾����
float Actor::attack_power() const{
    return mAttackPower;
}

MyRectangle Actor::collider() const
{
    return mCollider;
}

void Actor::damage(const float damage_value)
{
    // �Փ˔��肪�����̏ꍇ�̓X�L�b�v
    if (!mIsEnableCollider) return;

    mHealth.Damage(damage_value);

    mIsEnableCollider = false;
    mCoolTimer.reset();

    if (mHealth.GetIsDead()) {
        die();
    }
}
