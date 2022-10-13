#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Camera.hpp"

namespace Core
{
	class InputsManager
	{
		// Attribute
	private:
		double mouseX, mouseY;
		float mouseDeltaX, mouseDeltaY;
		bool mouseCaptured;
		unsigned int timeMouseCaptured;

		// Methode
	public:
		InputsManager();

		void Update(GLFWwindow* p_window, LowRenderer::CameraInputs& p_cameraInputs);
	};
}