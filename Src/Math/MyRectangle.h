#pragma once

#include "Math/Vector2.h"

#include <DxLib.h>

class MyRectangle {
public:
	// �f�t�H���g�R���X�g���N�^(Actor�̐錾�ɕK�v?)
	MyRectangle();

	// �R���X�g���N�^
	explicit MyRectangle(float left, float top, float right, float bottom);
	explicit MyRectangle(const Vector2& min, const Vector2& max);

	// �_����`�̓����ɓ����Ă��邩���肷��
	bool contains(const Vector2& position) const;

	// ��`���d�Ȃ��Ă��邩���肷��
	bool intersects(const MyRectangle& other) const;

	// ���s�ړ�
	MyRectangle translate(const Vector2& position) const;

	// �g������
	MyRectangle expand(const Vector2& size) const;

	// �����擾
	float width() const;

	// �������擾
	float height() const;

	// ����̍��W���擾
	const Vector2& get_min() const;

	// �E���̍��W���擾
	const Vector2& get_max() const;

	// �f�o�b�O�`��
	void draw_debug(int is_fill = 0, unsigned int color = GetColor(0, 0, 255)) const;

private:
	Vector2 mMin; // ��`�̍���
	Vector2 mMax; // ��`�̉E��
};