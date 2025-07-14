#include "IScene.h"

//���̃V�[����ݒ�
void IScene::set_next(const std::string& next_scene) {
	next_scene_ = next_scene;
}

//�Q�[���X�s�[�h��ݒ�
void IScene::set_game_speed(const float game_speed) {
	game_speed_ = game_speed;
}

//�Q�[���X�s�[�h���擾
float IScene::game_speed() const {
	return game_speed_;
}

//���̃V�[����Ԃ�
std::string IScene::next() const {
	return next_scene_;
}