#include "World/World.h"
#include "Scene/IScene.h"
#include "Actor/Actor.h"

//�f�X�g���N�^
World::~World() {
	clear();
}

//�X�V
void World::update(float delta_time) {
	//�A�N�^�[�̍X�V
	mActorManager.update(delta_time);
	//�A�N�^�[�̏Փ�
	mActorManager.collide();
	//�A�N�^�[�̒x���X�V
	mActorManager.late_update(delta_time);
	//�A�N�^�[�̏���
	mActorManager.remove();
}

//�`��
void World::draw() const {
	//�t�B�[���h�`��
	mpField->draw();
	//�A�N�^�[�̕`��
	mActorManager.draw();
	//�������A�N�^�[�̕`��
	mActorManager.draw_transparent();
	//GUI�̕`��
	mActorManager.draw_gui();
}

//����
void World::clear() {
	//�A�N�^�[�̏���
	mActorManager.clear();
}

//�V�[���̓o�^
void World::set_scene(IScene* scene) {
	mpScene = scene;
}

//�V�[���̎擾
IScene* World::scene() {
	return mpScene;
}

void World::set_field(Field* field)
{
	mpField = field;
}

//�A�N�^�[�̒ǉ�
void World::add_actor(Actor* actor) {
	mActorManager.add(actor);
}

//�A�N�^�[�̌���
Actor* World::find_actor(const std::string& name) const {
	return mActorManager.find(name);
}

//�w�肵���^�O�������A�N�^�[�̌���
std::vector<Actor*> World::find_actor_with_tag(const std::string& tag) const {
	return mActorManager.find_with_tag(tag);
}

//�A�N�^�[����Ԃ�
int World::count_actor() const {
	return mActorManager.count();
}

//�w�肵���^�O�������A�N�^�[����Ԃ�
int World::count_actor_with_tag(const std::string& tag) const {
	return mActorManager.count_with_tag(tag);
}

//���b�Z�[�W���M
void World::send_message(const std::string& message, void* param) {
	mActorManager.send_message(message, param);
}