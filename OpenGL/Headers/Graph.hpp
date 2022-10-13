#pragma once

#include <vector>

#include "GameObject.hpp"
#include "Camera.hpp"
#include "LightManager.hpp"

namespace Core::DataStructure
{
	int constexpr INVALID_INDEX = -1;

	struct GraphNode
	{
		int indexGameObject = INVALID_INDEX; // Index in gameObjects
		int parentIndex		= INVALID_INDEX; // Index in nodes
		std::vector<int> childsIndex;		// Index in nodes
	};

	class Graph
	{
		// Attribure
	private:
		std::vector<GraphNode> nodes;
		std::vector<LowRenderer::GameObject>* gameObjects;

		// Methode
	public:
		Graph(std::vector<LowRenderer::GameObject>& p_gameObject);
		~Graph();

		void Draw(LowRenderer::Camera& p_camera, LowRenderer::LightManager& p_lightManager);

		void AddNode(int p_index);
		bool SetParent(const std::string& p_nameParent, const std::string& p_nameChild);

	private:
		void DrawImGui(const GraphNode& p_graphNode);
		void DrawChild(LowRenderer::Camera& p_camera, LowRenderer::LightManager& p_lightManager, const GraphNode& p_childs);
		
		bool ParentCheck(const unsigned int p_index) const;

		// Get and Set
		Core::Maths::Mat4& GetMatrixModelParent(const GraphNode& p_childs);
		GraphNode& GetNode(const unsigned int p_index);
		LowRenderer::GameObject& GetGameObject(const unsigned int p_index);
	};
}