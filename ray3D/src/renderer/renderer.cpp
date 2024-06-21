#include "renderer.h"
#include "openGL/openGLRenderer.h"

namespace ray3D
{
	auto renderer::init(const rendererBackendType backendType, ui32 width, ui32 height) -> bool
	{
		mRenderer = nullptr;
		switch (backendType)
		{
		case rendererBackendType::openGL:
			mRenderer = std::make_unique<openGLRenderer>();
			break;

		case rendererBackendType::vulkan:
		case rendererBackendType::directX:
			R3D_LOGW("Only OpenGL is support for now!");
			return false;
		}

		R_ASSERT_MSG(mRenderer, "Invalid reference to renderer backend");
		mRenderer->init(width, height);
		mInitialized = true;

		return true;
	}

	auto renderer::beginFrame() -> void
	{
		R_ASSERT(mRenderer);
		mRenderer->beginFrame();
	}

	auto renderer::endFrame() -> void
	{
		R_ASSERT(mRenderer);
		mRenderer->endFrame();
	}

	auto renderer::draw(f32 deltaTime) -> void
	{
		R_ASSERT(mRenderer);
		mRenderer->draw(deltaTime);
	}

	auto renderer::onResize(ui32 width, ui32 height) -> void
	{
		R_ASSERT(mRenderer);
		mRenderer->onResize(width, height);
	}
}