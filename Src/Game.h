#pragma once
#include "DxLib.h"
#include "Scene/SceneManager.h"

class Game {
public:
	//�R���X�g���N�^
	Game(const int screenX, const int screenY);

	//�J�n
	void start();

	//�X�V
	void update();

	//�`��
	void draw();

	//�f�o�b�O�`��
	void draw_debug();

	//�I��
	void end();

private:
	//�V�[���}�l�[�W���[
	SceneManager scene_manager_;
};