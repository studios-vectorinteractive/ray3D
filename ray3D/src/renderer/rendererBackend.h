#pragma once
#include "core/core.h"

namespace ray3D
{
	class rendererBackend
	{
	public:
		virtual auto init(ui32 width, ui32 height) -> bool = 0;
		virtual auto beginFrame() -> void = 0;
		virtual auto endFrame() -> void = 0;
		virtual auto draw(f32 deltaTime) -> void = 0;

		virtual auto onResize(ui32 width, ui32 height) -> void = 0;

	};
}