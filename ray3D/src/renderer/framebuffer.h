#pragma once
#include "core/core.h"
#include <memory>

namespace ray3D
{
	class texture;
	class vertexBuffer;
	class indexBuffer;

	class frameBuffer
	{
	public:
		frameBuffer(const ui32 width, const ui32 height);
		~frameBuffer();

		auto bind() -> void;
		auto unBind() -> void;
		auto draw() -> void;

		auto onResize(const ui32 newWidth, const ui32 newHeight);

		static auto create(const ui32 width, const ui32 height) -> std::unique_ptr<frameBuffer>;

	private:
		auto reCreateFramebuffer(bool invalidate) -> void;

	private:
		ui32 mFramebufferID = {};
		ui32 mWidth = {};
		ui32 mHeight = {};

		std::shared_ptr<vertexBuffer> mQuadVertBuffer;
		std::shared_ptr<indexBuffer> mQuadIndexBuffer;

		std::unique_ptr<texture> mColorAttachment = {};
		std::unique_ptr<texture> mDepthStencilAttachment = {};
		
	};
}