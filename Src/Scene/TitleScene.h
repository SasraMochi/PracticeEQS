#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

#include"IScene.h"

class TitleScene : public IScene {
public:
	//�J�n
	virtual void start() override;
	//�X�V
	virtual void update() override;
	//�`��
	virtual void draw() const override;
	//�f�o�b�O�`��
	virtual void draw_debug() override;

	//�I�����Ă��邩�H
	virtual bool is_end() const override;

	//�I��
	virtual void end() override;

private:
	// �V�[���؂�ւ��\��
	void change_scene_(std::string next_scene_name);

private:
	bool mIsEnd;
};

#endif // !TITLE_SCENE_H_