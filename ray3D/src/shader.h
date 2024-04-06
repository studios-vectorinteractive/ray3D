#pragma once
#include <string>
#include <stdint.h>

namespace ray3D
{
	enum class ShaderType;

	class shader
	{
	public:
		shader(const std::string& vertShaderPath, const std::string& fragShaderPath);
		~shader();

		auto getShaderProgramID() const ->uint32_t { return mShaderID; }
		auto bind() -> void;

	private:

		uint32_t compileShader(const std::string& shaderFilePath, const ShaderType shaderType);

	private:
		uint32_t mShaderID = {};
	};
}