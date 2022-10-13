#pragma once

#include "Transform.hpp"

namespace LowRenderer
{
	struct CameraInputs
	{
		float deltaX	  = 0.f;
		float deltaY	  = 0.f;
		bool moveForward  = true;
		bool moveBackward = true;
		bool moveRight	  = true;
		bool moveLeft	  = true;
		bool moveUp		  = true;
		bool moveDown	  = true;
	};

	class Camera
	{
		// Attribute
	private:
		Core::Maths::Vec3 position;
		Core::Maths::Vec3 rotation;
		float far;
		float near;
		float right;
		float left;
		float top;
		float bottom;

		float FOV;
		float speed;
		float aspect;

		Physics::Transform viewMatrix;
		Physics::Transform projectionMatrix;

		// Methode
	public:
		Camera(const int p_width = 1, const int p_height = 1);

		void Update(const CameraInputs& p_inputs);

		// Get and Set
		Core::Maths::Mat4& GetViewProjection();
		Core::Maths::Vec3& GetPosition() { return position; };

	private:
		void CalculateViewMatrix();
		void CalculateProjectionMatrix();
	};
}