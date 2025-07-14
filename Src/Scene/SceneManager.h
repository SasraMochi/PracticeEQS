#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <unordered_map>
#include <string>

class IScene;

//�V�[���Ǘ��N���X
class SceneManager {
public:
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//�X�V
	void update();
	//�`��
	void draw() const;
	//�f�o�b�O�`��
	void draw_debug();
	//�I��
	void end();
	//�V�[���̒ǉ�
	void add(const std::string& name, IScene* scene);
	//�V�[���̕ύX
	void change(const std::string& name, const std::string& next = "TitleScene");
	//�V�[���̏���
	void clear();
	//�R�s�[�֎~
	SceneManager(const SceneManager& other) = delete;
	SceneManager& operator = (const SceneManager& other) = delete;

private:
	//�V�[��
	std::unordered_map<std::string, IScene*> scenes_;
	//���݂̃V�[��
	IScene* current_scene_;
};

#endif // !SCENE_MANAGER_H_
