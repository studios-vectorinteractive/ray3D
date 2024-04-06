#pragma once
#include <vector>

namespace ray3D
{
	class buffer
	{
	public:
		virtual auto bind() -> void = 0;
	};

	class vertexBuffer : public buffer
	{
	public:
		vertexBuffer();

		virtual auto bind() -> void override;

	private:
		std::vector<float> mVertices = {};
		std::size_t mVertexCount = {};
	};

	class indexBuffer : public buffer
	{
	public:
		indexBuffer();

		virtual auto bind() -> void override;
	private:
		std::vector<float> mIndices = {};
		std::size_t mIndexCount = {};
	};
}