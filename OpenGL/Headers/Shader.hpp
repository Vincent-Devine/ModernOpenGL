#pragma once

#include "IResource.hpp"
#include "MyMaths.hpp"
#include "Light.hpp"

namespace Resources
{
	class Shader : public IResource
	{
		// Attribute
	private:
		int vertexShader;
		int fragmentShader;
		int shaderProgram;

		// Methodes
	public:
		Shader(const std::string& p_name, const unsigned int p_id);

		void Init(const std::string& p_pathVert, const std::string& p_pathFrag);
		void Draw(const Core::Maths::Mat4& p_transform, const Core::Maths::Mat4& p_mvp);

		const int GetShaderProgram() const { return shaderProgram; }

	private:
		bool SetVertexShader(const std::string& p_path);
		bool SetFragmentShader(const std::string& p_path);
		bool Link();

		void OpenShader(const std::string& p_path, std::ifstream& p_source);
		void CloseShader(const std::string& p_path, std::ifstream& p_source);
	};

}