#include "engineApp.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/event/eventManager.h"
#include "time.h"
#include "renderer/buffer.h"
#include "renderer/shader.h"

namespace ray3D
{
	engineApp::engineApp(const appConfig& config):window(config)
	{
		//Renderer Initialize
		mRunning = true;
	}

	auto engineApp::run() -> void
	{
		time::init(this);
		mLastTime = time::elapsedTime;
		postAppInitialize();

		//Read and Create Shaders
		shader testShader(R"(E:\Live Tutorial\ray3D\ray3D\src\shaders\vert.glsl)", R"(E:\Live Tutorial\ray3D\ray3D\src\shaders\frag.glsl)");

		//Vertex
		std::vector<f32> vertices =
		{
			//Position			//Color
		-0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,		//0
		0.5f, 0.5f, 0.0f,   0.0f, 0.2f, 0.0f,		//1
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,		//2
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,		//3
		};

		std::vector<ui32> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		std::shared_ptr<vertexBuffer> vertBuffer = vertexBuffer::create(vertices, vertAttribLayoutType::pos_col);
		std::shared_ptr<indexBuffer> idxBuffer = indexBuffer::create(indices);

		while (mRunning)
		{
			time::onUpdate();

			f64 currentTime = getTime();
			f64 deltaTime = currentTime - mLastTime;
			f64 frameStartTime = currentTime;

			if (!mSuspended)
			{
				//appLayer Update
				onUpdate(_f32(deltaTime));

				glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				testShader.bind();
				vertBuffer->bind();
				idxBuffer->bind();

				glDrawElements(GL_TRIANGLES, idxBuffer->getCount(), GL_UNSIGNED_INT, 0);

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
		R3D_LOGD("Application resized to : [{}, {}]", newWidth, newHeight);
	}

	auto engineApp::onDestroy() -> void
	{
		mRunning = false;
	}
}