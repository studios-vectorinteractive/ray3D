#include "engineApp.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/event/eventManager.h"
#include "core/input/input.h"
#include "time.h"
#include "renderer/renderer.h"


namespace ray3D
{
	engineApp::engineApp(const appConfig& config):window(config)
	{
		//Renderer Initialize
		mRunning = true;
		input::init(getGLFWwindow());
		renderer::init(rendererBackendType::openGL, mWidth, mHeight);
	}

	auto engineApp::run() -> void
	{
		time::init(this);
		mLastTime = time::elapsedTime;
		postAppInitialize();

		while (mRunning)
		{
			time::onUpdate();

			f64 currentTime = getTime();
			f64 deltaTime = currentTime - mLastTime;
			f64 frameStartTime = currentTime;

			if (!mSuspended)
			{

				f32 deltaT = _f32(deltaTime);
				//appLayer Update
				onUpdate(deltaT);

				renderer::beginFrame();
				renderer::draw(deltaT);
				renderer::endFrame();

				//Input Update
				input::update(deltaT);

				swapBuffers();
			}
			mLastTime = currentTime;

			eventManager::dispatchEvents();
			updateInput();
		}
	}

	auto engineApp::onResize(const windowResizeEvent& resizeEvent) -> void
	{
		ui32 newWidth = resizeEvent.getWidth();
		ui32 newHeight = resizeEvent.getHeight();

		if (newWidth == 0 || newHeight == 0)
		{
			R3D_LOGD("Window minimized!, App suspended");
			mSuspended = true;
			return;
		}

		mSuspended = false;
		glViewport(0, 0, _ui64(newWidth), _ui64(newHeight));
		renderer::onResize(newWidth, newHeight);
		R3D_LOGD("Application resized to : [{}, {}]", newWidth, newHeight);
	}

	auto engineApp::onDestroy() -> void
	{
		input::shutdown();
		mRunning = false;
	}
}