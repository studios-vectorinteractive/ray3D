#pragma once
#include "core/core.h"
#include "renderTypes.h"
#include "rendererBackend.h"

namespace ray3D
{
	class renderer
	{
	public:

		static auto init(const rendererBackendType backendType, ui32 width, ui32 height) -> bool;
		static auto beginFrame() -> void;
		static auto endFrame() -> void;
		static auto draw(f32 deltaTime) -> void;

		static auto onResize(ui32 width, ui32 height) -> void;

		static auto setDrawMode(const drawMode mode) -> void
		{
			mDrawMode = mode;
		}

		static auto getBackendType() -> rendererBackendType
		{
			return mBackendType;
		}

		static auto getDrawMode() -> drawMode
		{
			return mDrawMode;
		}

	private:
		renderer() = default;
		~renderer() = default;

	private:
		static inline bool mInitialized = false;
		static inline rendererBackendType mBackendType = rendererBackendType::none;
		static inline drawMode mDrawMode = drawMode::index;
		static inline std::unique_ptr<rendererBackend> mRenderer = {};
	};
}