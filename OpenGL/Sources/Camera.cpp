#include "Camera.hpp"

namespace LowRenderer
{
	Camera::Camera(const int p_width, const int p_height)
		: position()
		, rotation()
		, far(100.f)
		, near(0.1f)
		, right(1.f)
		, left(-1.f)
		, top(1.f)
		, bottom(-1.f)
		, FOV(100.f)
		, speed(0.1f)
		, aspect((float)p_width / (float)p_height)
	{
		CalculateViewMatrix();
		CalculateProjectionMatrix();
	}

	void Camera::Update(const CameraInputs& p_inputs)
	{
		rotation.y -= p_inputs.deltaX / 6.f;
		rotation.x -= p_inputs.deltaY / 6.f;

		if (rotation.x < -90.f)
			rotation.x = -90.f;

		if (rotation.x > 90.f)
			rotation.x = 90.f;

		if (rotation.y < -360.f)
			rotation.y = 360.f;

		if (rotation.y > 360.f)
			rotation.y = -360.f;

		if (p_inputs.moveForward)
		{
			position.x += speed * cosf(Core::Maths::DEG2RAD * (rotation.y + 90.f));
			position.z -= speed * sinf(Core::Maths::DEG2RAD * (rotation.y + 90.f));
		}

		if (p_inputs.moveBackward)
		{
			position.x -= speed * cosf(Core::Maths::DEG2RAD * (rotation.y + 90.f));
			position.z += speed * sinf(Core::Maths::DEG2RAD * (rotation.y + 90.f));
		}

		if (p_inputs.moveLeft)
		{
			position.x -= speed * cosf(Core::Maths::DEG2RAD * (rotation.y));
			position.z += speed * sinf(Core::Maths::DEG2RAD * (rotation.y));
		}

		if (p_inputs.moveRight)
		{
			position.x += speed * cosf(Core::Maths::DEG2RAD * (rotation.y));
			position.z -= speed * sinf(Core::Maths::DEG2RAD * (rotation.y));
		}

		if (p_inputs.moveUp)
			position.y += speed;

		if (p_inputs.moveDown)
			position.y -= speed;

		CalculateViewMatrix();
	}

	Core::Maths::Mat4& Camera::GetViewProjection()
	{
		Core::Maths::Mat4 vp = projectionMatrix.matrix * viewMatrix.matrix;
		return vp;
	}

	void Camera::CalculateViewMatrix()
	{
		viewMatrix.matrix = Core::Maths::Mat4::CreateXRotationMatrix(-rotation.x)
						  * Core::Maths::Mat4::CreateYRotationMatrix(-rotation.y)
						  * Core::Maths::Mat4::CreateTranslationMatrix(-position);
	}

	void Camera::CalculateProjectionMatrix()
	{
		float a = 1.f / tanf(Core::Maths::DEG2RAD * FOV / 2.f);

		Core::Maths::Mat4 projection(
			a / aspect, 0.f, 0.f,						   0.f,
			0.f,		a,	 0.f,						   0.f,
			0.f,		0.f, -(far + near) / (far - near), -(2 * far * near) / (far - near),
			0.f,		0.f, -1.f,						   0.f
		);
		projectionMatrix.matrix = projection;
	}
}