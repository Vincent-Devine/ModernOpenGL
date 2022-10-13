#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

namespace LowRenderer
{
	class Model
	{
		// Attribute
	private:
		Resources::Mesh* mesh;
		Resources::Shader* shader;
		Resources::Texture* texture;

		const int shaderProgram;

		// Methode
	public:
		Model(Resources::Mesh* p_mesh, Resources::Shader* p_shader, Resources::Texture* p_texture);

		void Draw(const Core::Maths::Mat4& p_transform, const Core::Maths::Mat4& p_mvp) const;
	
		// Get and Set
		const int GetShaderProgram() const { return shaderProgram; };
		const std::string GetTextureName() { return texture->GetName(); };
		const std::string GetShaderName()	{ return shader->GetName(); };
		const std::string GetMeshName()	{ return mesh->GetName(); };
	};
}