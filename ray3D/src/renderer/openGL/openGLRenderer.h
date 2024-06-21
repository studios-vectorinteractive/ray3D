#pragma once
#include "core/core.h"
#include "renderer/rendererBackend.h"

namespace ray3D
{
	class openGLRenderer : public rendererBackend
	{
	public:

		virtual auto init(ui32 width, ui32 height) -> bool override;
		virtual auto beginFrame() -> void override;
		virtual auto endFrame() -> void override;
		virtual auto draw(f32 deltaTime) -> void override;
		virtual auto onResize(ui32 width, ui32 height) -> void override;

	private:
		ui32 mWidth = {};
		ui32 mHeight = {};
	};
}