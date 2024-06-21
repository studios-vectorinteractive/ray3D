#pragma once
#include <memory>
#include <vector>
#include <type_traits>

#include "core/core.h"
#include "renderer/vertAttribs.h"

namespace ray3D
{
	class buffer
	{
	public:
		buffer() = default;
		virtual ~buffer() = default;
		virtual auto bind() -> void = 0;
	};

	class vertexBuffer : public buffer
	{
	public:
		vertexBuffer(std::vector<f32>& vertBuffer, const vertAttribLayoutType attribLayoutType);
		virtual ~vertexBuffer();

		virtual auto bind() -> void override;
		
		inline auto getCount() -> ui64 { return mVertexCount; }
		inline auto getBufferID() -> ui32 { return mVertBufferID; }

		template<typename t_vert, typename = std::enable_if<std::is_same<t_vert, posVert>::value || std::is_same<t_vert, posColVert>::value || 
			std::is_same<t_vert, posColTexVert>::value || std::is_same<t_vert, posColNorVert>::value || std::is_same<t_vert, texPosNorColVert>::value >>
		static std::shared_ptr<vertexBuffer> create(std::vector<t_vert>& vertBuffer, const vertAttribLayoutType attribLayoutType)
		{
			f32* data = reinterpret_cast<f32*>(vertBuffer.data());
			size_t size = (vertBuffer.size() * sizeof(t_vert)) / sizeof(f32);

			std::vector<f32> vertexData(data, data + size);
			//vertBuffer.clear();

			return std::make_shared<vertexBuffer>(vertexData, attribLayoutType);
		}

	private:
		std::vector<f32> mVertices = {};
		ui64 mVertexCount = {};
		vertAttribsLayout mAttribLayout = {};
		ui32 mVertBufferID = {};
		ui32 mVertAttribArrayID = {};
	};

	class indexBuffer : public buffer
	{
	public:
		indexBuffer(std::vector<ui32>& indexBuffer);
		virtual ~indexBuffer();

		virtual auto bind() -> void override;

		inline auto getCount() -> ui64 { return mIndexCount; }
		inline auto getBufferID() -> ui32 { return mIndexBufferID; }

		static std::shared_ptr<indexBuffer> create(std::vector<ui32>& idxBuffer)
		{
			return std::make_shared<indexBuffer>(idxBuffer);
		}

	private:
		std::vector<ui32> mIndices = {};
		ui64 mIndexCount = {};
		ui32 mIndexBufferID = {};
	};
}