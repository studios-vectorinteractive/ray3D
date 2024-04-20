#pragma once

#include <initializer_list>
#include <vector>

#include <glm/glm.hpp>
#include "shader.h"
#include "core/core.h"

namespace ray3D
{
	class vertAttribsLayout;

	enum class vertAttribLayoutType
	{
		pos,
		pos_col,
		pos_col_tex,
		pos_col_nor,
		tex_pos_nor_col,
		none
	};

	enum class vertAttribType
	{
		position,
		color,
		texcoord,
		normal,
		tangant,

		maxAttributes
	};

	struct vertAttribElement
	{
		std::string elementName = {};
		shaderDataType shaderType = shaderDataType::none;
		ui32 offset = 0;
		ui64 elementSize = 0;
		bool normalized = false;

		vertAttribElement() = default;
		vertAttribElement(shaderDataType dataType, const std::string& name, bool isNormalized = false):
			shaderType(dataType), offset(0), elementSize(getShaderDataTypeSize(dataType)), elementName(name), normalized(isNormalized)	{}

		auto getElementCount() const -> ui64
		{
			switch (shaderType)
			{
			case shaderDataType::none:			return 0;
			case shaderDataType::float1:
			case shaderDataType::int1:
			case shaderDataType::bool1:			return 1;
			case shaderDataType::float2:
			case shaderDataType::int2:			return 2;
			case shaderDataType::float3:
			case shaderDataType::int3:			return 3;
			case shaderDataType::float4:
			case shaderDataType::int4:			return 4;
			case shaderDataType::fMat3:
			case shaderDataType::iMat3:
			case shaderDataType::uiMat3:		return 9;
			case shaderDataType::fMat4:			
			case shaderDataType::uiMat4:		
			case shaderDataType::iMat4:			return 16;
			}

			R3D_LOGE("Invalid shader data type!");
			return 0;
		}
	};

	class vertAttribsLayout
	{
	public:
		vertAttribsLayout() = default;
		vertAttribsLayout(const std::initializer_list<vertAttribElement>& elements) :
			mBufferElements(elements)
		{
			//Calculate stride and offset
			if (mBufferElements.empty())
			{
				R3D_LOGW("Buffer Layout initialized with no elements");
				return;
			}
			calculateStrideAndOffsets();
		}

		inline auto getStride() const -> ui32 { return mStride; }
		inline auto getElements() const -> const std::vector<vertAttribElement>& { return mBufferElements; }

		static auto getLayout(const vertAttribLayoutType vertAttributeType) -> vertAttribsLayout
		{
			switch (vertAttributeType)
			{
			case vertAttribLayoutType::pos:
			{
				return
				{
					{shaderDataType::float3, "Position"}
				};
			}
			case vertAttribLayoutType::pos_col:
			{
				return
				{
					{shaderDataType::float3, "Position"},
					{shaderDataType::float3, "Color"}
				};
			}
			case vertAttribLayoutType::pos_col_tex:
			{
				return
				{
					{shaderDataType::float3, "Position"},
					{shaderDataType::float3, "Color"},
					{shaderDataType::float2, "TexCoord"}
				};
			}
			case vertAttribLayoutType::pos_col_nor:
			{
				return
				{
					{shaderDataType::float3, "Position"},
					{shaderDataType::float3, "Color"},
					{shaderDataType::float3, "Normal"}
				};
			}
			case vertAttribLayoutType::tex_pos_nor_col:
			{
				return
				{
					{shaderDataType::float2, "TexCoord"},
					{shaderDataType::float3, "Position"},
					{shaderDataType::float3, "Normal"},
					{shaderDataType::float3, "Color"}
				};
			}
			}

			return vertAttribsLayout();
		}

	private:
		inline auto calculateStrideAndOffsets() -> void
		{
			ui32 offset = 0;
			mStride = 0;

			for (auto& element : mBufferElements)
			{
				element.offset = offset;
				offset += _ui32(element.elementSize);
				mStride += _ui32(element.elementSize);
			}
		}

	private:
		ui32 mStride = 0;
		std::vector<vertAttribElement> mBufferElements = {};
	};

	//Vertices
	struct posVert
	{
		glm::vec3 position;
		inline static auto getSize() -> ui64
		{
			return sizeof(posVert);
		}
	};

	struct posColVert
	{
		glm::vec3 position;
		glm::vec3 color;

		inline static auto getSize() -> ui64
		{
			return sizeof(posColVert);
		}
	};

	struct posColTexVert
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texCoord;

		inline static auto getSize() -> ui64
		{
			return sizeof(posColTexVert);
		}
	};

	struct posColNorVert
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;

		inline static auto getSize() -> ui64
		{
			return sizeof(posColNorVert);
		}
	};

	struct texPosNorColVert
	{
		glm::vec2 tex;
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 color;

		inline static auto getSize() -> ui64
		{
			return sizeof(texPosNorColVert);
		}
	};

	inline auto getVertexSize(const vertAttribLayoutType vertAttributeType) -> ui64
	{
		switch (vertAttributeType)
		{
		case vertAttribLayoutType::pos: return posVert::getSize();
		case vertAttribLayoutType::pos_col: return posColVert::getSize();
		case vertAttribLayoutType::pos_col_tex: return posColTexVert::getSize();
		case vertAttribLayoutType::pos_col_nor: return posColNorVert::getSize();
		case vertAttribLayoutType::tex_pos_nor_col: return texPosNorColVert::getSize();
		}

		R3D_LOGE("Invalid vertAttribLayoutType!");
		return 0;
	}
}