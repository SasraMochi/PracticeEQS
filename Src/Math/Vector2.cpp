#include "Vector2.h"
#include "Mathf.h"
#include <cmath>
#include <limits>
#include <algorithm>

const float kEpsilon{ 1e-05f };

// �R���X�g���N�^
Vector2::Vector2(float x, float y) : x{ x }, y{ y } {
}

// Vector2(0, 0)�Ɠ����Ӗ�
Vector2 Vector2::zero() {
	return Vector2{ 0.0f, 0.0f };
}

// Vector2(1, 1)�Ɠ����Ӗ�
Vector2 Vector2::one() {
	return Vector2{ 1.0f, 1.0f };
}

// Vector2(0, -1)�Ɠ����Ӗ�
Vector2 Vector2::up() {
	return Vector2{ 0.0f, -1.0f };
}

// Vector2(0, 1)�Ɠ����Ӗ�
Vector2 Vector2::down() {
	return Vector2{ 0.0f, 1.0f };
}

// Vector2(-1, 0)�Ɠ����Ӗ�
Vector2 Vector2::left() {
	return Vector2{ -1.0f, 0.0f };
}

// Vector2(1, 0)�Ɠ����Ӗ�
Vector2 Vector2::right() {
	return Vector2{ 1.0f, 0.0f };
}

int Vector2::int_x() const
{
	return static_cast<int>(std::roundf(x));
}

int Vector2::int_y() const
{
	return static_cast<int>(std::roundf(y));
}

// �x�N�g���̒���
float Vector2::magnitude() const {
	return std::sqrt(sqr_magnitude());
}

// ���K�������x�N�g����Ԃ�
Vector2 Vector2::normalized() const {
	Vector2 v{ *this };
	v.normalize();
	return v;
}

// �x�N�g����2��̒���
float Vector2::sqr_magnitude() const {
	return (x * x) + (y * y);
}

// [0]��[1]���g�p���āAx��y�����ɃA�N�Z�X
float Vector2::operator [] (int index) const {
	return (index == 0) ? x : y;
}

// [0]��[1]���g�p���āAx��y�����ɃA�N�Z�X
float& Vector2::operator [] (int index) {
	return (index == 0) ? x : y;
}

// Returns true if the given vector is exactly equal to this vector.
bool Vector2::equals(const Vector2& other) {
	return x == other.x && y == other.y;
}

// ���K��
void Vector2::normalize() {
	float mag = magnitude();
	if (mag > kEpsilon) {
		*this /= mag;
	}
	else {
		*this = zero();
	}
}

// ������Vector2��x��y�̐�����ݒ�
void Vector2::set(float new_x, float new_y) {
	x = new_x;
	y = new_y;
}

// �x�N�g���̒l�����₷���t�H�[�}�b�g���ꂽ������
std::string Vector2::to_string() const {
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

// 2�̃x�N�g���̂Ȃ��p
float Vector2::angle(const Vector2& from, const Vector2& to) {
	float denominator = std::sqrt(from.sqr_magnitude() * to.sqr_magnitude());
	if (denominator < 0.0f) return 0.0f;
	float dot = Mathf::clamp(Vector2::dot(from, to) / denominator, -1.0f, 1.0f);
	return std::acos(dot) * Mathf::rad_to_deg();
}

// �傫����maxLength�܂łɐ�������vector�̃R�s�[
Vector2 Vector2::clamp_magnitude(const Vector2& vector, float max_length) {
	float sqr_mag = vector.sqr_magnitude();
	if (sqr_mag > max_length * max_length) {
		return (vector / std::sqrt(sqr_mag)) * max_length;
	}
	return vector;
}

// a-b�Ԃ̋���
float Vector2::distance(const Vector2& a, const Vector2& b) {
	return (a - b).magnitude();
}

// ����
float Vector2::dot(const Vector2& lhs, const Vector2& rhs) {
	return (lhs.x * rhs.x) + (lhs.y * rhs.y);
}

// 2�̃x�N�g���̐��`���
Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, float t) {
	return Vector2::lerp_unclamped(a, b, Mathf::clamp01(t));
}

// 2�̃x�N�g���̐��`���
Vector2 Vector2::lerp_unclamped(const Vector2& a, const Vector2& b, float t) {
	return a + (b - a) * t;
}

// 2�̃x�N�g���Ŋe�����̍ő�l���g�p���ăx�N�g�����쐬
Vector2 Vector2::max_value(const Vector2& lhs, const Vector2& rhs) {
	return Vector2{ std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y) };
}

// 2�̃x�N�g���Ŋe�����̍ŏ��l���g�p���ăx�N�g�����쐬
Vector2 Vector2::min_value(const Vector2& lhs, const Vector2& rhs) {
	return Vector2{ std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y) };
}

// ���݈ʒucurrent����target�Ɍ����Ĉړ�
Vector2 Vector2::move_towards(const Vector2& current, const Vector2& target, float max_distance_delta) {
	Vector2 to_vector = target - current;
	float sq_dist = to_vector.sqr_magnitude();
	if (sq_dist == 0.0f || (max_distance_delta >= 0.0f && sq_dist <= max_distance_delta * max_distance_delta))
		return target;
	float dist = std::sqrt(sq_dist);
	return current + (to_vector / dist) * max_distance_delta;
}

// Returns the 2D vector perpendicular to this 2D vector.
// The result is always rotated 90 - degrees in a counter - clockwise direction
// for a 2D coordinate system where the positive Y axis goes up.
Vector2 Vector2::perpendicular(const Vector2& inDirection) {
	return Vector2{ -inDirection.y, inDirection.x };
}

// �@������ɂ��ăx�N�g���̔��˂����x�N�g�����擾
Vector2 Vector2::reflect(const Vector2& inDirection, const Vector2& inNormal) {
	float factor = -2.0f * dot(inNormal, inDirection);
	return factor * inNormal + inDirection;
}

// 2�̃x�N�g���̊e��������Z
Vector2 Vector2::scale(const Vector2& a, const Vector2& b) {
	return Vector2{ a.x * b.x, a.y * b.y };
}

// Returns the signed angle in degrees between from and to.
float Vector2::signed_angle(const Vector2& from, const Vector2& to) {
	float unsigned_angle = angle(from, to);
	float sign = Mathf::sign(from.x * to.y - from.y * to.x);
	return unsigned_angle * sign;
}

// �ړI�n�Ɍ������Ď��Ԃ̌o�߂Ƌ��ɏ��X�Ƀx�N�g����ω�������
Vector2 Vector2::smooth_damp(const Vector2& current, const Vector2& target, Vector2& current_velocity, float smooth_time, float max_speed, float delta_time) {
	smooth_time = std::max(0.0001f, smooth_time);
	float omega = 2.0f / smooth_time;

	float x = omega * delta_time;
	float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);

	Vector2 change = current - target;
	Vector2 original_to = target;

	// Clamp maximum speed
	float max_change = max_speed * smooth_time;

	float max_change_sq = max_change * max_change;
	float sq_dist = change.sqr_magnitude();
	if (sq_dist > max_change_sq) {
		float mag = std::sqrt(sq_dist);
		change = change / mag * max_change;
	}

	Vector2 temp = (current_velocity + omega * change) * delta_time;
	current_velocity = (current_velocity - omega * temp) * exp;
	Vector2 output = (current - change) + (change + temp) * exp;

	// Prevent overshooting
	Vector2 orig_minus_current = original_to - current;
	Vector2 out_minus_orig = output - original_to;

	if (orig_minus_current.sqr_magnitude() > 0.0f) {
		output = original_to;
		current_velocity = (output - original_to) / delta_time;
	}
	return output;
}


// �P�����Z�q�I�[�o�[���[�h
Vector2 operator - (const Vector2& v) {
	return Vector2{ -v.x ,-v.y };
}

// ������Z�q�I�[�o�[���[�h
Vector2& operator += (Vector2& lhs, const Vector2& rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

// ������Z�q�I�[�o�[���[�h
Vector2& operator -= (Vector2& lhs, const Vector2& rhs) {
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

// ������Z�q�I�[�o�[���[�h
Vector2& operator *= (Vector2& lhs, float rhs) {
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}

// ������Z�q�I�[�o�[���[�h
Vector2& operator /= (Vector2& lhs, float rhs) {
	lhs.x /= rhs;
	lhs.y /= rhs;
	return lhs;
}

// 2�����Z�q�I�[�o�[���[�h
Vector2 operator + (const Vector2& lhs, const Vector2& rhs) {
	return Vector2{ lhs.x + rhs.x,lhs.y + rhs.y };
}

// 2�����Z�q�I�[�o�[���[�h
Vector2 operator - (const Vector2& lhs, const Vector2& rhs) {
	return Vector2{ lhs.x - rhs.x,lhs.y - rhs.y };
}

// 2�����Z�q�I�[�o�[���[�h
Vector2 operator * (const Vector2& lhs, float rhs) {
	return Vector2{ lhs.x * rhs,lhs.y * rhs };
}

// 2�����Z�q�I�[�o�[���[�h
Vector2 operator * (float lhs, const Vector2& rhs) {
	return rhs * lhs;
}

// 2�����Z�q�I�[�o�[���[�h
Vector2 operator / (const Vector2& lhs, float rhs) {
	return Vector2{ lhs.x / rhs,lhs.y / rhs };
}

bool operator == (const Vector2& lhs, const Vector2& rhs) {
	// Returns false in the presence of NaN values.
	Vector2 diff = lhs - rhs;
	return diff.sqr_magnitude() < (kEpsilon * kEpsilon);
}

bool operator != (const Vector2& lhs, const Vector2& rhs) {
	// Returns true in the presence of NaN values.
	return !(lhs == rhs);
}