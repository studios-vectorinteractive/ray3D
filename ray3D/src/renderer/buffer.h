#pragma once
#include <memory>
#include <vector>

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

		static std::shared_ptr<vertexBuffer> create(std::vector<f32>& vertBuffer, const vertAttribLayoutType attribLayoutType)
		{
			return std::make_shared<vertexBuffer>(vertBuffer, attribLayoutType);
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