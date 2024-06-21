#pragma once
#include <string>
#include <stdint.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "core/core.h"

namespace ray3D
{
	enum class shaderType;

	enum class shaderDataType
	{
		none = 0,
		float1,
		float2,
		float3,
		float4,
		fMat3,
		fMat4,
		iMat3,
		iMat4,
		uiMat3,
		uiMat4,
		int1,
		int2,
		int3,
		int4,
		bool1
	};

	inline auto getShaderDataTypeSize(shaderDataType dataType) -> ui64
	{
		switch (dataType)
		{
		case shaderDataType::none:			return 0;
		case shaderDataType::float1:			return sizeof(f32);
		case shaderDataType::float2:			return sizeof(f32) * 2;
		case shaderDataType::float3:			return sizeof(f32) * 3;
		case shaderDataType::float4:			return sizeof(f32) * 4;
		case shaderDataType::fMat3:			return sizeof(f32) * 9;
		case shaderDataType::fMat4:			return sizeof(f32) * 16;
		case shaderDataType::iMat3:			return sizeof(i32) * 9;
		case shaderDataType::iMat4:			return sizeof(i32) * 16;
		case shaderDataType::uiMat3:			return sizeof(ui32) * 9;
		case shaderDataType::uiMat4:			return sizeof(ui32) * 16;
		case shaderDataType::int1:			return sizeof(i32);
		case shaderDataType::int2:			return sizeof(i32) * 2;
		case shaderDataType::int3:			return sizeof(i32) * 3;
		case shaderDataType::int4:			return sizeof(i32) * 4;
		case shaderDataType::bool1:			return sizeof(bool);
		}

		R3D_LOGE("Invalid shader data type!");
		return 0;
	}

	inline auto getGLShaderDataType(shaderDataType dataType) -> GLenum
	{
		switch (dataType)
		{
		case shaderDataType::none:			return GL_NONE;
		case shaderDataType::float1:			
		case shaderDataType::float2:			
		case shaderDataType::float3:			
		case shaderDataType::float4:			
		case shaderDataType::fMat3:			
		case shaderDataType::fMat4:			return GL_FLOAT;
		case shaderDataType::uiMat3:			
		case shaderDataType::uiMat4:			return GL_UNSIGNED_INT;
		case shaderDataType::int1:			
		case shaderDataType::int2:			
		case shaderDataType::int3:			
		case shaderDataType::int4:			
		case shaderDataType::iMat3:			
		case shaderDataType::iMat4:			return GL_INT;
		case shaderDataType::bool1:			return GL_BOOL;
		}

		R3D_LOGE("Invalid shader data type!");
		return GL_NONE;
	}

	class shader
	{
	public:
		shader(const std::string& vertShaderPath, const std::string& fragShaderPath);
		~shader();

		auto getShaderProgramID() const ->ui32 { return mShaderID; }
		auto bind() -> void;

		auto setUniformFloat(const char* name, f32 val) -> void;
		auto setUniformInt(const char* name, i32 val) -> void;
		auto setUniformMat4(const char* name, glm::mat4& val) -> void;
		auto setUniformVec3(const char* name, glm::vec3& val) -> void;
		auto setUniformVec4(const char* name, glm::vec4 val) -> void;
		auto setTexture(const char* name, const ui32 textureID, const ui32 texSlot) -> void;

		static std::unique_ptr<shader> create(const std::string& vertShaderPath, const std::string& fragShaderPath)
		{
			//TODO: handle graphics API based shaders
			return std::make_unique<shader>(vertShaderPath, fragShaderPath);
		}

	private:

		uint32_t compileShader(const std::string& shaderFilePath, const shaderType shaderType);

	private:
		uint32_t mShaderID = {};
	};
}