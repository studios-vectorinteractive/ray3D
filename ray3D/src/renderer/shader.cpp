#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "core/core.h"

namespace ray3D
{
	enum class shaderType
	{
		Vertex,
		Fragment
	};

	shader::shader(const std::string& vertShaderPath, const std::string& fragShaderPath)
	{
		if (!std::filesystem::exists(vertShaderPath) || !std::filesystem::exists(fragShaderPath))
		{
			R3D_LOGE("Invalid vertex or fragment shader file path!");
			return;
		}

		GLuint fragShaderID, vertShaderID;

		vertShaderID = compileShader(vertShaderPath, shaderType::Vertex);
		fragShaderID = compileShader(fragShaderPath, shaderType::Fragment);

		if (!vertShaderID || !fragShaderID)
		{
			R3D_LOGE("Failed to compile shaders!");
			return;
		}

		//Shader Program
		mShaderID = glCreateProgram();
		glAttachShader(mShaderID, vertShaderID);
		glAttachShader(mShaderID, fragShaderID);
		glLinkProgram(mShaderID);

		i32 status = 0;
		std::vector<char> programLinkLog(512, 0);

		glGetProgramiv(mShaderID, GL_LINK_STATUS, &status);
		if (!status)
		{
			glGetProgramInfoLog(mShaderID, programLinkLog.size(), nullptr, programLinkLog.data());
			R3D_LOGE("Program Linking Error : %s", programLinkLog.data());
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

	auto shader::setUniformFloat(const char* name, f32 val) -> void
	{
		glUniform1f(glGetUniformLocation(mShaderID, name), val);
	}

	auto shader::setUniformInt(const char* name, i32 val) -> void
	{
		glUniform1i(glGetUniformLocation(mShaderID, name), val);
	}

	auto shader::setUniformMat4(const char* name, glm::mat4& val) -> void
	{
		glUniformMatrix4fv(glGetUniformLocation(mShaderID, name), 1, GL_FALSE, glm::value_ptr(val));
	}

	auto shader::setUniformVec3(const char* name, glm::vec3& val) -> void
	{
		glUniform3f(glGetUniformLocation(mShaderID, name), val.x, val.y, val.z);
	}

	auto shader::setUniformVec4(const char* name, glm::vec4 val) -> void
	{
		glUniform4f(glGetUniformLocation(mShaderID, name), val.x, val.y, val.z, val.w);
	}

	auto shader::setTexture(const char* name, const ui32 textureID, const ui32 texSlot) -> void
	{
		glActiveTexture(GL_TEXTURE0 + texSlot);
		glBindTexture(GL_TEXTURE_2D, textureID);
		setUniformInt(name, GL_TEXTURE0 + texSlot);
	}

	uint32_t shader::compileShader(const std::string& shaderFilePath, const shaderType shaderType)
	{
		GLuint ShaderID = {};
		std::ifstream shaderFileStream(shaderFilePath, std::ios::binary);
		std::stringstream stringStream;

		if (!shaderFileStream.is_open())
		{
			R3D_LOGE("Failed to open shader file! : %s", shaderFilePath.c_str());
			return 0;
		}

		GLuint glShaderType = 0;
		std::string shderDebugName = "Null";
		switch (shaderType)
		{
		case shaderType::Vertex: glShaderType = GL_VERTEX_SHADER; shderDebugName = "Vertex"; break;
		case shaderType::Fragment: glShaderType = GL_FRAGMENT_SHADER; shderDebugName = "Fragment"; break;
		default:
			break;
		}

		if (glShaderType == 0)
		{
			R3D_LOGE("Invalid Shader Type");
			return 0;
		}

		std::string shaderSrouce;
		stringStream << shaderFileStream.rdbuf();
		shaderSrouce = stringStream.str();

		const char* shaderSourceChar = shaderSrouce.c_str();
		ShaderID = glCreateShader(glShaderType);
		glShaderSource(ShaderID, 1, &shaderSourceChar, nullptr);
		glCompileShader(ShaderID);

		i32 status = 0;
		std::vector<char> shaderCompilationLog(512, 0);

		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			glGetShaderInfoLog(ShaderID, shaderCompilationLog.size(), nullptr, shaderCompilationLog.data());
			R3D_LOGE("{} Shader Compilation Error : {}", shderDebugName, shaderCompilationLog.data());
			return 0;
		}

		return ShaderID;
	}
}