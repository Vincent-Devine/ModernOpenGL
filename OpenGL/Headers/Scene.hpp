#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Resources
#include "IResource.hpp"

// LowRenderer
#include "Camera.hpp"
#include "GameObject.hpp"
#include "LightManager.hpp"

// DataStructure
#include "Graph.hpp"

namespace Resources
{
	class Scene : public IResource
	{
		// Attribute
	private:
		LowRenderer::Camera camera;
		std::vector<LowRenderer::GameObject> gameObjects;
		LowRenderer::LightManager lightManager;
		Core::DataStructure::Graph graph;

		// Methode
	public:
		Scene(const std::string& p_name, const unsigned int p_id);
		~Scene();

		void Init(GLFWwindow* p_window, const std::string& p_path = "");
		void Update(const LowRenderer::CameraInputs& p_cameraInputs);
		void Draw();

		void AddGameObject(LowRenderer::GameObject& p_gameObject);
		void AddDirectionLight(const LowRenderer::DirectionLight& p_light);
		void AddPointLight(const LowRenderer::PointLight& p_light);
		void AddSpotLight(const LowRenderer::SpotLight& p_light);

		bool SetParent(const std::string& p_nameParent, const std::string& p_nameChild) { return graph.SetParent(p_nameParent, p_nameChild); };
	private:
		void InitImGui(GLFWwindow* p_window) const;
		void StartImGui() const;
		void EndImGui() const;
	};
}