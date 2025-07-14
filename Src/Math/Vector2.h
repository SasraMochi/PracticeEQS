#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <string>

// 2D�x�N�g���N���X
class Vector2 {
public:
    // ===== �����o�ϐ� =====
    float x{ 0.0f }; // x����
    float y{ 0.0f }; // y����

    // ===== �R���X�g���N�^ =====
    Vector2() = default; // �f�t�H���g�R���X�g���N�^
    Vector2(float x, float y); // x, y���w�肷��R���X�g���N�^

    // ===== �ÓI���\�b�h =====
    static Vector2 zero();       // (0, 0) �x�N�g��
    static Vector2 one();        // (1, 1) �x�N�g��
    static Vector2 up();         // (0, 1) �x�N�g��
    static Vector2 down();       // (0, -1) �x�N�g��
    static Vector2 left();       // (-1, 0) �x�N�g��
    static Vector2 right();      // (1, 0) �x�N�g��

    // ===== �C���X�^���X���\�b�h =====
    int int_x() const;           // x������int�^�Ŏ擾
    int int_y() const;           // y������int�^�Ŏ擾
    float magnitude() const;     // �x�N�g���̒���
    Vector2 normalized() const;  // ���K�����ꂽ�x�N�g��
    float sqr_magnitude() const; // �x�N�g���̒�����2��
    float operator[](int index) const; // �C���f�b�N�X�A�N�Z�X�i�ǂݎ��j
    float& operator[](int index);      // �C���f�b�N�X�A�N�Z�X�i�������݁j
    bool equals(const Vector2& other); // �x�N�g���̓�����r
    void normalize();                  // �x�N�g���𐳋K��
    void set(float x, float y);        // x, y������ݒ�
    std::string to_string() const;     // �x�N�g���𕶎���

    // ===== �ÓI���[�e�B���e�B���\�b�h =====
    static float angle(const Vector2& from, const Vector2& to);
    static Vector2 clamp_magnitude(const Vector2& vector, float max_length);
    static float distance(const Vector2& a, const Vector2& b);
    static float dot(const Vector2& lhs, const Vector2& rhs);
    static Vector2 lerp(const Vector2& a, const Vector2& b, float t);
    static Vector2 lerp_unclamped(const Vector2& a, const Vector2& b, float t);
    static Vector2 max_value(const Vector2& lhs, const Vector2& rhs);
    static Vector2 min_value(const Vector2& lhs, const Vector2& rhs);
    static Vector2 move_towards(const Vector2& current, const Vector2& target, float max_distance_delta);
    static Vector2 perpendicular(const Vector2& inDirection);
    static Vector2 reflect(const Vector2& inDirection, const Vector2& inNormal);
    static Vector2 scale(const Vector2& a, const Vector2& b);
    static float signed_angle(const Vector2& from, const Vector2& to);
    Vector2 smooth_damp(const Vector2& current, const Vector2& target, Vector2& currentVelocity, float smooth_time, float max_speed, float delta_time);

    // ===== ���Z�q�I�[�o�[���[�h =====
    friend Vector2 operator-(const Vector2& v);
    friend Vector2& operator+=(Vector2& lhs, const Vector2& rhs);
    friend Vector2& operator-=(Vector2& lhs, const Vector2& rhs);
    friend Vector2& operator*=(Vector2& lhs, float rhs);
    friend Vector2& operator/=(Vector2& lhs, float rhs);
    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator*(const Vector2& lhs, float rhs);
    friend Vector2 operator*(float lhs, const Vector2& rhs);
    friend Vector2 operator/(const Vector2& lhs, float rhs);
    friend bool operator==(const Vector2& lhs, const Vector2& rhs);
    friend bool operator!=(const Vector2& lhs, const Vector2& rhs);
};

#endif // VECTOR2_H_
