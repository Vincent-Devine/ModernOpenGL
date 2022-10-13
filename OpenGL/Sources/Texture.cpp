#include "Texture.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_Image/stb_image.h>
#include <iostream>

namespace Resources
{
	Texture::Texture(const std::string& p_name, const unsigned int p_id)
		: texture(0)
		, sampler(0)
	{
		name = p_name;
		id = p_id;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &texture);
		glDeleteSamplers(1, &sampler);
	}

	void Texture::Init(const std::string& p_path)
	{
		path = p_path;

		bool isPng = true;
		if (p_path.find(".jpg") != std::string::npos)
			isPng = false;

		// generate the texture data
		int width, height, nrChannels;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(p_path.c_str(), &width, &height, &nrChannels, 0);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		if(isPng)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		// create a sampler and parameterize it
		glGenSamplers(1, &sampler);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);

		GLint max = 0;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

		glBindTextureUnit(id, texture);
		glBindSampler(id, sampler);
	}

	void Texture::Draw(const unsigned int p_shaderProgram)
	{
		glUniform1i(glGetUniformLocation(p_shaderProgram, "texture1"), id);
	}
}