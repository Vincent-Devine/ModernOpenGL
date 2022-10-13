#pragma once

#include <vector>

#include "MyMaths.hpp"
#include "Model.hpp"
#include "LightManager.hpp"
#include "Transform.hpp"

namespace LowRenderer
{
	class GameObject
	{
		// Attribute
	private:
		LowRenderer::Model model;
		Physics::Transform transform;
		std::string name;

		// Methode
	public:
		GameObject(const LowRenderer::Model& p_model, const Physics::Transform& p_transform = Physics::Transform(), const std::string& p_name = "Default name");

		void Draw(Core::Maths::Mat4& p_vp, Core::Maths::Vec3 p_camPos, LightManager& p_lightManager, Core::Maths::Mat4 p_transformParent = Core::Maths::Mat4::Identity());

		void Translate(const Core::Maths::Vec3& p_translation);
		void Scale(const Core::Maths::Vec3& p_scale);
		void Rotate(const Core::Maths::Vec3& p_rotation);

		// Get and Set
		const int GetShaderProgram() { return model.GetShaderProgram(); };
		Model GetModel() { return model; };
		std::string& GetName() { return name; };

		Core::Maths::Vec3& GetTranslation() { return transform.translation; };
		Core::Maths::Vec3& GetRotation() { return transform.rotation; };
		Core::Maths::Vec3& GetScale() { return transform.scale; };
		Core::Maths::Mat4& GetModelMatrix() { return transform.matrix; };

	private:
		const void DrawImGui();
	};
}
