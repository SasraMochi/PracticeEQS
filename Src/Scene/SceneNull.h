#ifndef SCENE_NULL_H_
#define SCENE_NULL_H_

#include "IScene.h"

//�k���V�[��
class SceneNull : public IScene {
public:
	//�J�n
	virtual void start() override {}
	//�X�V
	virtual void update() override {}
	//�`��
	virtual void draw() const override {}
	//�f�o�b�O�`��
	virtual void draw_debug() override {}
	//�I�����Ă��邩�H
	virtual bool is_end() const override {
		return false;
	}

	//�I��
	virtual void end() override {}
};

#endif // !SCENE_NULL_H_

