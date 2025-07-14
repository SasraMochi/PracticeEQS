#pragma once

#include "World/IWorld.h"
#include "Scene/IScene.h"
#include "World/Field.h"
#include "Actor/ActorManager.h"

//���[���h�N���X
class World : public IWorld {
public:
	//�R���X�g���N�^
	World() = default;
	//�f�X�g���N�^
	~World();
	//�X�V
	void update(float delta_time);
	//�`��
	void draw() const;
	//����
	void clear();

	//���݂̃V�[���̓o�^
	void set_scene(IScene* scene);

	//���݂̃V�[���̎擾
	virtual IScene* scene() override;

	//�t�B�[���h�̓o�^
	void set_field(Field* field);

	//�A�N�^�[��ǉ�
	virtual void add_actor(Actor* actor) override;
	//�A�N�^�[�̌���
	virtual Actor* find_actor(const std::string& name) const override;
	//�w�肵���^�O�������A�N�^�[�̌���
	virtual std::vector<Actor*> find_actor_with_tag(const std::string& tag) const override;
	//�A�N�^�[����Ԃ�
	virtual int count_actor() const override;
	//�w�肵���^�O�������A�N�^�[����Ԃ�
	virtual int count_actor_with_tag(const std::string& tag) const override;
	//���b�Z�[�W�̑��M
	virtual void send_message(const std::string& message, void* param = nullptr) override;

	//�R�s�[�֎~
	World(const World& other) = delete;
	World& operator = (const World& other) = delete;

private:
	//�A�N�^�[�}�l�[�W���[
	ActorManager mActorManager;
	//�V�[��
	IScene* mpScene{ nullptr };
	//�t�B�[���h
	Field* mpField{ nullptr };
};