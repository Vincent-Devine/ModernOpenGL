#include "InputsManager.hpp"

namespace Core
{
	InputsManager::InputsManager()
		: mouseX(0.0)
		, mouseY(0.0)
		, mouseDeltaX(0.f)
		, mouseDeltaY(0.f)
		, mouseCaptured(false)
		, timeMouseCaptured(0)
	{
	}

	void InputsManager::Update(GLFWwindow* p_window, LowRenderer::CameraInputs& p_cameraInputs)
	{
		if (glfwGetKey(p_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(p_window, true);

		// Camera inputs (keyboard)
		if (glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
			p_cameraInputs.moveForward = true;
		else
			p_cameraInputs.moveForward = false;

		if (glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
			p_cameraInputs.moveBackward = true;
		else
			p_cameraInputs.moveBackward = false;

		if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
			p_cameraInputs.moveLeft = true;
		else
			p_cameraInputs.moveLeft = false;

		if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
			p_cameraInputs.moveRight = true;
		else
			p_cameraInputs.moveRight = false;

		if (glfwGetKey(p_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			p_cameraInputs.moveDown = true;
		else
			p_cameraInputs.moveDown = false;

		if (glfwGetKey(p_window, GLFW_KEY_SPACE) == GLFW_PRESS)
			p_cameraInputs.moveUp = true;
		else
			p_cameraInputs.moveUp = false;

		// Camera inputs (mouse)
		if (glfwGetKey(p_window, GLFW_KEY_M) == GLFW_PRESS)
			mouseCaptured = false;

		if (glfwGetMouseButton(p_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			mouseCaptured = true;
			//glfwSetCursorPos(window, (width / 2), (height / 2));
			glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			timeMouseCaptured++;
		}
		else
		{
			mouseCaptured = false;
			timeMouseCaptured = 0;
			glfwSetInputMode(p_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		if (mouseCaptured)
		{
			double newMouseX, newMouseY;
			glfwGetCursorPos(p_window, &newMouseX, &newMouseY);
			mouseDeltaX = (float)(newMouseX - mouseX);
			mouseDeltaY = (float)(newMouseY - mouseY);
			mouseX = newMouseX;
			mouseY = newMouseY;

			if (timeMouseCaptured == 1) // firstFrame
			{
				p_cameraInputs.deltaX = 0.f;
				p_cameraInputs.deltaY = 0.f;
			}
			else
			{
				p_cameraInputs.deltaX = mouseDeltaX;
				p_cameraInputs.deltaY = mouseDeltaY;
			}
		}
		else
		{
			p_cameraInputs.deltaX = 0.f;
			p_cameraInputs.deltaY = 0.f;
		}
	}
}