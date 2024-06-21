#include "mesh.h"

namespace ray3D
{
	mesh::mesh(std::shared_ptr<vertexBuffer>& vertBuffer, std::shared_ptr<indexBuffer>& indxBuffer)
	{
		mVertBuffer = std::move(vertBuffer);
		mIndexBuffer = std::move(indxBuffer);
	}
}