#pragma once
#pragma warning (disable: 4172)


#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>

#include <numbers>
#include <cmath>


struct view_matrix_t {
	float* operator[ ](int index) {
		return matrix[index];
	}
	float matrix[4][4];
};


struct Vector2 {
	float x, y;
};


struct Vector3 {
	constexpr Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) { }

	constexpr const Vector3& operator-(const Vector3& other) const noexcept
	{
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}

	constexpr const Vector3& operator+(const Vector3& other) const noexcept
	{
		return Vector3{ x + other.x, y + other.y, z + other.z };
	}

	constexpr const Vector3& operator/(const float factor) const noexcept
	{
		return Vector3{ x / factor, y / factor, z / factor };
	}

	constexpr const Vector3& operator*(const float factor) const noexcept
	{
		return Vector3{ x * factor, y * factor, z * factor };
	}

	constexpr const Vector3& ToAngle() const noexcept
	{
		return Vector3{
			std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
			std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
			0.0f 
		};
	}


	Vector3 worldToScreen(view_matrix_t matrix) {
		float _x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
		float _y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];

		float w = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3];

		float inv_w = 1.f / w;
		_x *= inv_w;
		_y *= inv_w;

		float screen_x = GetSystemMetrics(SM_CXSCREEN) * 0.5f;
		float screen_y = GetSystemMetrics(SM_CYSCREEN) * 0.5f;

		screen_x += 0.5f * _x * GetSystemMetrics(SM_CXSCREEN) + 0.5f;
		screen_y -= 0.5f * _y * GetSystemMetrics(SM_CYSCREEN) + 0.5f;

		return { screen_x, screen_y, w };
	}

	constexpr const bool IsZero() const noexcept
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	float x, y, z;
};


inline constexpr Vector3 CalculateAngle(
	const Vector3& localPosition,
	const Vector3& enemyPosition,
	const Vector3& viewAngles) noexcept
{
	return (enemyPosition - localPosition).ToAngle() - viewAngles;
};


inline Vector3 clampAngles(Vector3 angles) {
	if (angles.x > 89.0f && angles.x <= 180.0f){
		angles.x = 89.0f;
	}

	if (angles.x > 180.0f){
		angles.x -= 360.0f;
	}

	if (angles.x < -89.0f){
		angles.x = -89.0f;
	}

	if (angles.y > 180.0f){
		angles.y -= 360.0f;
	}

	if (angles.y < -180.0f){
		angles.y += 360.0f;
	}
	angles.z = 0;

	return angles;
};


inline Vector3 normalizeAngles(Vector3 angle) {
	while (angle.x > 180.f)
		angle.x -= 360.0f;

	while (angle.x < -180.0f)
		angle.x += 360.0f;

	while (angle.y > 180.0f)
		angle.y -= 360.0f;

	while (angle.y < -180.0f)
		angle.y += 360.0f;

	return angle;
};



inline Vector3 calculateBestAngle(Vector3 angle,float configFov) {
	Vector3 newAngle;

	float calcFov = std::hypot(angle.x, angle.y);
	float fov = configFov;

	if (calcFov < fov) {
		calcFov = fov;
		newAngle = angle;
	}
	return newAngle;
}