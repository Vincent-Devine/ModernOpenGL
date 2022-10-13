#pragma once

#include <string>

namespace Resources
{
	class IResource
	{
		// Attribute
	protected:
		std::string path;
		std::string name;
		unsigned int id;

		// Methode
	public:
		virtual ~IResource() {};

		virtual void SetPath(const std::string p_path) { path = p_path; };
		virtual void SetName(const std::string p_name) { name = p_name; };

		virtual std::string GetPath() const { return path; };
		virtual std::string GetName() const { return name; };
	};
}