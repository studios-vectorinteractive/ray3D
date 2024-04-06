#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

#include <glad/glad.h>

#include "shader.h"
#include "log.h"

namespace ray3D
{
	enum class ShaderType
	{
		Vertex,
		Fragment
	};

	shader::shader(const std::string& vertShaderPath, const std::string& fragShaderPath)
	{
		if (!std::filesystem::exists(vertShaderPath) || !std::filesystem::exists(fragShaderPath))
		{
			LOG("Invalid vertex or fragment shader file path!");
			return;
		}

		GLuint fragShaderID, vertShaderID;

		vertShaderID = compileShader(vertShaderPath, ShaderType::Vertex);
		fragShaderID = compileShader(fragShaderPath, ShaderType::Fragment);

		if (!vertShaderID || !fragShaderID)
		{
			LOG("Failed to compile shaders!");
			return;
		}

		//Shader Program
		mShaderID = glCreateProgram();
		glAttachShader(mShaderID, vertShaderID);
		glAttachShader(mShaderID, fragShaderID);
		glLinkProgram(mShaderID);

		int status = 0;
		std::vector<char> programLinkLog(512, 0);

		glGetProgramiv(mShaderID, GL_LINK_STATUS, &status);
		if (!status)
		{
			glGetProgramInfoLog(mShaderID, programLinkLog.size(), nullptr, programLinkLog.data());
			LOG("Program Linking Error : %s", programLinkLog.data());
			return;
		}

		glDeleteShader(vertShaderID);
		glDeleteShader(fragShaderID);
	}

	shader::~shader()
	{
		glDeleteProgram(mShaderID);
	}

	auto shader::bind() -> void
	{
		glUseProgram(mShaderID);
	}

	uint32_t shader::compileShader(const std::string& shaderFilePath, const ShaderType shaderType)
	{
		GLuint ShaderID = {};
		std::ifstream shaderFileStream(shaderFilePath, std::ios::binary);
		std::stringstream stringStream;

		if (!shaderFileStream.is_open())
		{
			LOG("Failed to open shader file! : %s", shaderFilePath.c_str());
			return 0;
		}

		GLuint glShaderType = 0;
		switch (shaderType)
		{
		case ShaderType::Vertex: glShaderType = GL_VERTEX_SHADER; break;
		case ShaderType::Fragment: glShaderType = GL_FRAGMENT_SHADER; break;
		default:
			break;
		}

		if (glShaderType == 0)
		{
			LOG("Invalid Shader Type");
			return 0;
		}

		std::string shaderSrouce;
		stringStream << shaderFileStream.rdbuf();
		shaderSrouce = stringStream.str();

		const char* shaderSourceChar = shaderSrouce.c_str();
		ShaderID = glCreateShader(glShaderType);
		glShaderSource(ShaderID, 1, &shaderSourceChar, nullptr);
		glCompileShader(ShaderID);

		int status = 0;
		std::vector<char> shaderCompilationLog(512, 0);

		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			glGetShaderInfoLog(ShaderID, shaderCompilationLog.size(), nullptr, shaderCompilationLog.data());
			LOG("Vertex Shader Compilation Error : %s", shaderCompilationLog.data());
			return 0;
		}

		return ShaderID;
	}
}