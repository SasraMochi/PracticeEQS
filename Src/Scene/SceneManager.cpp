#include "SceneManager.h"
#include "SceneNull.h"

static SceneNull scene_null;	//null�V�[��

//�R���X�g���N�^
SceneManager::SceneManager() :
	current_scene_{ &scene_null } {
}

//�f�X�g���N�^
SceneManager::~SceneManager() {
	clear();
}

//�X�V
void SceneManager::update() {
	//�V�[���̍X�V
	current_scene_->update();
	//�V�[�����I�����Ă��邩�H
	if (current_scene_->is_end()) {
		//�V�[����ύX����
		change(current_scene_->next());
	}
}

//�`��
void SceneManager::draw() const {
	//���݂̃V�[����`��
	current_scene_->draw();
}

void SceneManager::draw_debug()
{
	//���݂̃V�[�����f�o�b�O�`��
	current_scene_->draw_debug();
}

//�I��
void SceneManager::end() {
	//���݂̃V�[�����I��
	current_scene_->end();
	//null�V�[���ɂ��Ă���
	current_scene_ = &scene_null;
}

//�V�[���̒ǉ�
void SceneManager::add(const std::string& name, IScene* scene) {
	scenes_[name] = scene;
}

//�V�[���̕ύX
void SceneManager::change(const std::string& name, const std::string& next) {
	//���݂̃V�[�����I��
	end();
	//���݂̃V�[����ύX
	current_scene_ = scenes_[name];
	//���݂̃V�[����nextScene��ݒ�
	current_scene_->set_next(next);
	//���݂̃V�[�����J�n
	current_scene_->start();
}

//�V�[���̏���
void SceneManager::clear() {
	//�O�̈׃V�[���̏I�����Ăяo��
	end();
	//unordered_map���̃V�[�������ׂč폜
	for (const auto& pair : scenes_) {
		delete pair.second;	//�V�[���̍폜
	}
	//unordered_map������
	scenes_.clear();
}