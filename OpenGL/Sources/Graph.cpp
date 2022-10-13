#include "Graph.hpp"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "Log.hpp"

namespace Core::DataStructure
{
	Graph::Graph(std::vector<LowRenderer::GameObject>& p_gameObject)
		: nodes()
		, gameObjects(&p_gameObject)
	{
	}

	Graph::~Graph()
	{
		nodes.clear();
	}

	void Graph::Draw(LowRenderer::Camera& p_camera, LowRenderer::LightManager& p_lightManager)
	{
		ImGui::Begin("GameObjects");

		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			if (ParentCheck(i))
				continue;
			
			GetGameObject(i).Draw(p_camera.GetViewProjection(), p_camera.GetPosition(), p_lightManager);
			DrawImGui(nodes[i]);

			for (unsigned int j = 0; j < GetNode(i).childsIndex.size(); j++)
				DrawChild(p_camera, p_lightManager, GetNode(GetNode(i).childsIndex[j]));
		}

		ImGui::End();
	}

	void Graph::AddNode(int p_index)
	{
		nodes.push_back(GraphNode{ p_index });
	}

	bool Graph::SetParent(const std::string& p_nameParent, const std::string& p_nameChild)
	{
		int parent = INVALID_INDEX;
		int child = INVALID_INDEX;

		for (unsigned int i = 0; i < nodes.size(); i++)
		{
			if (GetGameObject(i).GetName() == p_nameParent)
				parent = i;

			if (GetGameObject(i).GetName() == p_nameChild)
				child = i;
		}

		if (parent == INVALID_INDEX)
		{
			Core::Debug::Log::Print(p_nameParent + " not found\n", Core::Debug::LogLevel::Warning);
			return false;
		}

		if (child == INVALID_INDEX)
		{
			Core::Debug::Log::Print(p_nameChild + " not found\n", Core::Debug::LogLevel::Warning);
			return false;
		}

		GetNode(child).parentIndex = parent;
		GetNode(parent).childsIndex.push_back(child);
		Core::Debug::Log::Print("Set parent " + p_nameParent + " to " + p_nameChild + "\n", Core::Debug::LogLevel::Notification);

		return true;
	}

	void Graph::DrawImGui(const GraphNode& p_graphNode)
	{
		if (p_graphNode.parentIndex != INVALID_INDEX)
			ImGui::Text(("Parent  : " + GetGameObject(p_graphNode.parentIndex).GetName()).c_str());

		for (unsigned int i = 0; i < p_graphNode.childsIndex.size(); i++)
			ImGui::Text(("Child   : " + GetGameObject(p_graphNode.childsIndex[i]).GetName()).c_str());
	}

	void Graph::DrawChild(LowRenderer::Camera& p_camera, LowRenderer::LightManager& p_lightManager, const GraphNode& p_child)
	{
		GetGameObject(p_child.indexGameObject).Draw(p_camera.GetViewProjection(), p_camera.GetPosition(), p_lightManager, GetMatrixModelParent(p_child));
		DrawImGui(p_child);

		for (unsigned int i = 0; i < p_child.childsIndex.size(); i++)
			DrawChild(p_camera, p_lightManager, GetNode(p_child.childsIndex[i]));
	}

	bool Graph::ParentCheck(const unsigned int p_index) const
	{
		if (nodes[p_index].parentIndex == INVALID_INDEX)
			return false;
		return true;
	}

	Core::Maths::Mat4& Graph::GetMatrixModelParent(const GraphNode& p_childs)
	{
		return GetGameObject(GetNode(p_childs.parentIndex).indexGameObject).GetModelMatrix();
	}

	GraphNode& Graph::GetNode(const unsigned int p_index)
	{
		return nodes[p_index];
	}

	LowRenderer::GameObject& Graph::GetGameObject(const unsigned int p_index)
	{
		return (*gameObjects)[p_index];
	}
}