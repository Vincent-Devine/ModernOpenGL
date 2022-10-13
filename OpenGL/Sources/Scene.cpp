#include "Scene.hpp"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "Log.hpp"

namespace Resources
{
	Scene::Scene(const std::string& p_name, const unsigned int p_id)
		: camera		()
		, gameObjects	()
		, lightManager	()
		, graph			(gameObjects)
	{
		name = p_name;
		id = p_id;
	}

	Scene::~Scene()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Scene::Init(GLFWwindow* p_window, const std::string& p_path)
	{
		path = p_path;
		InitImGui(p_window);
	}

	void Scene::Update(const LowRenderer::CameraInputs& p_cameraInputs)
	{
		camera.Update(p_cameraInputs);
	}

	void Scene::Draw()
	{
		StartImGui();

		gameObjects[1].Rotate(Core::Maths::Vec3(0.f, 0.f, 1.f));
		gameObjects[2].Rotate(Core::Maths::Vec3(0.f, 1.f, 0.f));
		gameObjects[3].Rotate(Core::Maths::Vec3(1.f, 0.f, 0.f));
		gameObjects[4].Rotate(Core::Maths::Vec3(1.f, 0.f, 0.f));
		gameObjects[5].Rotate(Core::Maths::Vec3(1.f, 1.f, 0.f));
		gameObjects[8].Rotate(Core::Maths::Vec3(0.f, 1.f, 1.f));
		gameObjects[9].Rotate(Core::Maths::Vec3(1.f, 1.f, 0.f));
		gameObjects[10].Rotate(Core::Maths::Vec3(1.f, 1.f, 1.f));

		graph.Draw(camera, lightManager);
		lightManager.DrawImGui();

		EndImGui();
	}

	void Scene::AddGameObject(LowRenderer::GameObject& p_gameObject)
	{
		gameObjects.push_back(p_gameObject);
		graph.AddNode(gameObjects.size() - 1);
		Core::Debug::Log::Print("Add gameObject " + p_gameObject.GetName() + " in scene\n", Core::Debug::LogLevel::Notification);
	}

	void Scene::AddDirectionLight(const LowRenderer::DirectionLight& p_light)
	{
		lightManager.AddDirectionLight(p_light);
	}

	void Scene::AddPointLight(const LowRenderer::PointLight& p_light)
	{
		lightManager.AddPointLight(p_light);
	}

	void Scene::AddSpotLight(const LowRenderer::SpotLight& p_light)
	{
		lightManager.AddSpotLight(p_light);
	}

	void Scene::InitImGui(GLFWwindow* p_window) const
	{
		// Setup Dear ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		ImGui_ImplGlfw_InitForOpenGL(p_window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void Scene::StartImGui() const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Scene::EndImGui() const
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}