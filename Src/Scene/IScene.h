#ifndef ISCENE_H_
#define ISCENE_H_

#include <string>

//�V�[�����ۃC���^�[�t�F�[�X
class IScene {
public:
	//���z�f�X�g���N�^
	virtual ~IScene() = default;
	//�J�n
	virtual void start() = 0;
	//�X�V
	virtual void update() = 0;
	//�`��
	virtual void draw() const = 0;
	//�f�o�b�O�`��
	virtual void draw_debug() = 0;
	//�I�����Ă��邩�H
	virtual bool is_end() const = 0;
	//�I��
	virtual void end() = 0;
	//���̃V�[����ݒ�
	void set_next(const std::string& next_scene);

	//�Q�[���X�s�[�h��ݒ�
	void set_game_speed(const float game_speed);
	//�Q�[���X�s�[�h���擾
	float game_speed() const;

	//���̃V�[������Ԃ�
	std::string next() const;

protected:
	//�Q�[���X�s�[�h
	float game_speed_{ 1.0f };
	//���̃V�[��
	std::string next_scene_;
};

#endif // !ISCENE_H_
