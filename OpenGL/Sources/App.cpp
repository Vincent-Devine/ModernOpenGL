#include "App.hpp"

#include <iostream>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "Log.hpp"

namespace Core
{
	App::App()
		: window(nullptr)
		, width(0)
		, height(0)
		, resources()
		, inputsManager()
		, currentScene(nullptr)
	{
	}

	App::~App()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		glfwTerminate();
	}

	bool App::Init(const AppInit& p_appInit)
	{
		width = p_appInit.width;
		height = p_appInit.height;

		// glfw: initialize and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, p_appInit.major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, p_appInit.minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		// glfw window creation
		window = glfwCreateWindow(p_appInit.width, p_appInit.height, p_appInit.name, NULL, NULL);
		if (window == NULL)
		{
			DEBUG_LOG("Failed to create GLFW window");
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, p_appInit.framebuffer_size_callback);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			DEBUG_LOG("Failed to initialize GLAD");
			return false;
		}

		GLint flags = 0;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(p_appInit.glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		InitResource();

		currentScene = resources.GetResource<Resources::Scene>("Scene1");
		InitScene1();

		return true;
	}

	void App::Update()
	{
		LowRenderer::CameraInputs cameraInputs;

		while (!glfwWindowShouldClose(window))
		{
			// input
			glfwPollEvents();
			inputsManager.Update(window, cameraInputs);

			// render
			glClearColor(0.3f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);

			currentScene->Update(cameraInputs);
			currentScene->Draw();

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwSwapBuffers(window);
		}
	}

	void App::InitResource()
	{
		Core::Debug::Log::Print("---------\n", Core::Debug::LogLevel::None);
		Core::Debug::Log::Print("Init resource\n", Core::Debug::LogLevel::Notification);

		std::string name = "Cube";
		std::string path = "Resources/Obj/cube.obj";
		resources.Create<Resources::Mesh>(name)->Init(path);

		name = "BasicShader";
		std::string pathVert = "Resources/Shaders/VertexShaderSource.vert";
		std::string pathFrag = "Resources/Shaders/FragmentShaderSource.frag";
		resources.Create<Resources::Shader>(name)->Init(pathVert, pathFrag);

		name = "Wall";
		path = "Resources/Textures/wall.jpg";
		resources.Create<Resources::Texture>(name)->Init(path);

		name = "Sample";
		path = "Resources/Textures/sample.png";
		resources.Create<Resources::Texture>(name)->Init(path);

		// Slime
		name = "Slime";
		path = "Resources/Obj/Slime.obj";
		resources.Create<Resources::Mesh>(name)->Init(path);

		name = "SlimeText";
		path = "Resources/Textures/Slime.png";
		resources.Create<Resources::Texture>(name)->Init(path);

		// Frying_pan
		name = "FryingPan";
		path = "Resources/Obj/frying_pan.obj";
		resources.Create<Resources::Mesh>(name)->Init(path);

		name = "FryingPanText";
		path = "Resources/Textures/frying_pan.png";
		resources.Create<Resources::Texture>(name)->Init(path);

		// Pistol
		name = "Pistol";
		path = "Resources/Obj/c_pistol.obj";
		resources.Create<Resources::Mesh>(name)->Init(path);

		name = "PistolText";
		path = "Resources/Textures/c_pistol.png";
		resources.Create<Resources::Texture>(name)->Init(path);

		// Scene1
		name = "Scene1";
		resources.Create<Resources::Scene>(name)->Init(window);
	}

	void App::InitScene1()
	{
		Core::Debug::Log::Print("---------\n", Core::Debug::LogLevel::None);
		Core::Debug::Log::Print("Init scene 1\n", Core::Debug::LogLevel::Notification);

		LowRenderer::Model basicBox = LowRenderer::Model(
			resources.GetResource<Resources::Mesh>("Cube"),
			resources.GetResource<Resources::Shader>("BasicShader"),
			resources.GetResource<Resources::Texture>("Wall"));

		LowRenderer::GameObject box1(basicBox, Physics::Transform(
			Core::Maths::Vec3(0.f, -5.f, 0.f),
			Core::Maths::Vec3(10.f, 1.f, 10.f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Box1");

		currentScene->AddGameObject(box1);

		LowRenderer::GameObject defaultGameObject(basicBox);

		currentScene->AddGameObject(defaultGameObject);

		LowRenderer::GameObject box3(basicBox, Physics::Transform(
			Core::Maths::Vec3(4.f, 2.f, 0.f),
			Core::Maths::Vec3(1.f, 1.f, 1.f),
			Core::Maths::Vec3(0.f, 45.f, 45.f)), "Box3");

		currentScene->AddGameObject(box3);

		LowRenderer::GameObject box4(basicBox, Physics::Transform(
			Core::Maths::Vec3(-4.f, 2.f, 0.f),
			Core::Maths::Vec3(1.f, 1.f, 1.f),
			Core::Maths::Vec3(45.f, 0.f, 45.f)), "Box4");

		currentScene->AddGameObject(box4);

		LowRenderer::GameObject box5(basicBox, Physics::Transform(
			Core::Maths::Vec3(3.f, 1.f, 3.f),
			Core::Maths::Vec3(1.f, 1.f, 1.f),
			Core::Maths::Vec3(0.f, 45.f, 45.f)), "Box5");
		
		currentScene->AddGameObject(box5);

		LowRenderer::GameObject box6(basicBox, Physics::Transform(
			Core::Maths::Vec3(-3.f, 1.f, -2.f),
			Core::Maths::Vec3(.75f, .75f, .75f),
			Core::Maths::Vec3(0.f, 45.f, 45.f)), "Box6");

		currentScene->AddGameObject(box6);

		// Point Light
		LowRenderer::GameObject PointLight(basicBox, Physics::Transform(
			Core::Maths::Vec3(2.f, 1.f, 0.f),
			Core::Maths::Vec3(.5f, .5f, .5f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Point Light");

		currentScene->AddGameObject(PointLight);

		// Spot Light
		LowRenderer::GameObject spotLight(basicBox, Physics::Transform(
			Core::Maths::Vec3(-2.f, 8.f, 0.f),
			Core::Maths::Vec3(.5f, .5f, .5f),
			Core::Maths::Vec3(0.f, 0.f, 0.f)), "Spot Light");

		currentScene->AddGameObject(spotLight);

		// Slime
		LowRenderer::GameObject slime(LowRenderer::Model(
				resources.GetResource<Resources::Mesh>("Slime"),
				resources.GetResource<Resources::Shader>("BasicShader"),
				resources.GetResource<Resources::Texture>("SlimeText")),
			Physics::Transform(
				Core::Maths::Vec3(3.f, -1.5f, 5.f),
				Core::Maths::Vec3(.25f, .25f, .25f),
				Core::Maths::Vec3(0.f, -90.f, 0.f)), "Slime");

		currentScene->AddGameObject(slime);

		// FryingPan
		LowRenderer::GameObject fryingPan(LowRenderer::Model(
				resources.GetResource<Resources::Mesh>("FryingPan"),
				resources.GetResource<Resources::Shader>("BasicShader"),
				resources.GetResource<Resources::Texture>("FryingPanText")),
			Physics::Transform(
				Core::Maths::Vec3(-3.f, -1.5f, 5.f),
				Core::Maths::Vec3(.1f, .1f, .1f),
				Core::Maths::Vec3(0.f, -45.f, 45.f)), "Frying Pan");

		currentScene->AddGameObject(fryingPan);

		// Pistol	
		LowRenderer::GameObject pistol(LowRenderer::Model(
				resources.GetResource<Resources::Mesh>("Pistol"),
				resources.GetResource<Resources::Shader>("BasicShader"),
				resources.GetResource<Resources::Texture>("PistolText")),
			Physics::Transform(
				Core::Maths::Vec3(0.f, -1.5f, 5.f),
				Core::Maths::Vec3(.1f, .1f, .1f),
				Core::Maths::Vec3(0.f, 0.f, 0.f)), "Pistol");

		currentScene->AddGameObject(pistol);

		Assertion(currentScene->SetParent("Default name", "Slime"), "Fail to set parent");
		Assertion(currentScene->SetParent("Default name", "Pistol"), "Fail to set parent");
		Assertion(currentScene->SetParent("Pistol", "Frying Pan"), "Fail to set parent");

		LowRenderer::InitLight initLight
		{
			Core::Maths::Vec3(2.f, 1.f, 0.f),	   // position
			Core::Maths::Vec4(.3f, .3f, .3f, 1.f), // ambientColor
			Core::Maths::Vec4(.6f, .6f, .6f, 1.f), // diffuseColor
			Core::Maths::Vec4(.9f, .9f, .9f, 1.f)  // specularColor 
		};

		currentScene->AddDirectionLight(LowRenderer::DirectionLight(initLight, Core::Maths::Vec3(0.f, 0.f, 1.f)));

		currentScene->AddPointLight(LowRenderer::PointLight(initLight, 1.f, 0.09f, 0.032f));

		initLight.position = Core::Maths::Vec3(-2.f, 8.f, 0.f);
		currentScene->AddSpotLight(LowRenderer::SpotLight(initLight, Core::Maths::Vec3(0.f, -1.f, 0.f), 12.5f, 0.82f));
	}
}