#include "GameObject.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "Assertion.hpp"

namespace LowRenderer
{
	GameObject::GameObject(const LowRenderer::Model& p_model, const Physics::Transform& p_transform, const std::string& p_name)
		: model		(p_model)
		, transform (p_transform)
		, name		(p_name)
	{
	}

	void GameObject::Draw(Core::Maths::Mat4& p_vp, Core::Maths::Vec3 p_camPos, LightManager& p_lightManager, Core::Maths::Mat4 p_transformParent)
	{
		const int shaderProgram = GetShaderProgram();
		glUseProgram(shaderProgram);

		p_lightManager.Draw(shaderProgram, p_camPos);

		transform.matrix = p_transformParent * transform.GetLocalTransform();

		model.Draw(transform.matrix, (p_vp * transform.matrix));

		DrawImGui();
	}

	void GameObject::Translate(const Core::Maths::Vec3& p_translation)
	{
		transform.translation += p_translation;
	}

	void GameObject::Scale(const Core::Maths::Vec3& p_scale)
	{
		transform.scale += p_scale;
	}

	void GameObject::Rotate(const Core::Maths::Vec3& p_rotation)
	{
		transform.rotation += p_rotation;
		if (transform.rotation.x > 360)
			transform.rotation.x = 0;
		else if (transform.rotation.x < -360)
			transform.rotation.x = 0;

		if (transform.rotation.y > 360)
			transform.rotation.y = 0;
		else if (transform.rotation.y < -360)
			transform.rotation.y = 0;

		if (transform.rotation.z > 360)
			transform.rotation.z = 0;
		else if (transform.rotation.z < -360)
			transform.rotation.z = 0;
	}

	const void GameObject::DrawImGui()
	{
		if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::SliderFloat3(("Translation " + name).c_str(), &transform.translation.x, -10.f, 10.f, "%0.1f", 0);
			ImGui::SliderFloat3(("Rotation " + name).c_str(), &transform.rotation.x, 0.f, 360.f, "%0.1f", 0);
			ImGui::SliderFloat3(("Scale " + name).c_str(), &transform.scale.x, 0.001f, 10.f, "%0.1f", 0);
			ImGui::Text(("Texture : " + model.GetTextureName()).c_str());
			ImGui::Text(("Shader  : " + model.GetShaderName()).c_str());
			ImGui::Text(("Mesh    : " + model.GetMeshName()).c_str());
		}
	}
}