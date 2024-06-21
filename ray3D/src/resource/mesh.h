#pragma once
#include "core/core.h"
#include "renderer/buffer.h"

namespace ray3D
{
	class mesh
	{
	public:
		mesh(std::shared_ptr<vertexBuffer>& vertBuffer, std::shared_ptr<indexBuffer>& indxBuffer);
		~mesh() = default;

		auto getVertexBuffer() -> std::shared_ptr<vertexBuffer>& { return mVertBuffer; }
		auto getIndexBuffer() -> std::shared_ptr<indexBuffer>& { return mIndexBuffer; }

		static auto create(std::shared_ptr<vertexBuffer>& vertBuffer, std::shared_ptr<indexBuffer>& indxBuffer) -> std::unique_ptr<mesh>
		{
			return std::make_unique<mesh>(vertBuffer, indxBuffer);
		}

	private:
		std::shared_ptr<vertexBuffer> mVertBuffer = {};
		std::shared_ptr<indexBuffer> mIndexBuffer = {};
	};
}