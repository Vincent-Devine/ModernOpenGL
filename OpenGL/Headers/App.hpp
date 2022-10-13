#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Resources
#include "ResourcesManager.hpp"
#include "Scene.hpp"
// LowRenderer
#include "Camera.hpp"
#include "GameObject.hpp"
#include "LightManager.hpp"
// Core
#include "InputsManager.hpp"


namespace Core
{
	struct AppInit
	{
		unsigned int width;
		unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* name;
		void (*framebuffer_size_callback) (GLFWwindow* window, int width, int height);
		void (*glDebugOutput) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam);
	};

	class App
	{
		// Attribute
	private:

		GLFWwindow* window;
		unsigned int width;
		unsigned int height;

		Resources::ResourceManager resources;
		InputsManager inputsManager;
		Resources::Scene* currentScene;

		// Methode
	public:
		App();
		~App();

		bool Init(const AppInit& p_appInit);
		void Update();

		// Get and Set
		GLFWwindow* GetWindow() { return window; };

	private:
		void InitResource();
		void InitScene1();
	};
}