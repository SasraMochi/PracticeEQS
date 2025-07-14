#ifndef EDIT_BEHAVIOR_TREE_SCENE_H_
#define EDIT_BEHAVIOR_TREE_SCENE_H_

#include"IScene.h"
#include"Math/BehaviourTree/BehaviorTreeUtility.h"

class EditBehaviorTreeScene : public IScene {
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
	bool mIsEnd;
	BehaviorTreeGraph* mpBehaviorTree;
};
#endif // !EDIT_BEHAVIOR_TREE_SCENE_H_