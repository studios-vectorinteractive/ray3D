#include "window.h"
#include "log.h"

#include <glad/glad.h>

namespace ray3D
{
	window::window(const uint32_t Width, const uint32_t Height, const std::string& Title):
		mWidth(Width), mHeight(Height), mTitle(Title)
	{
		if (!glfwInit())
		{
			LOG("Failed to initalize GLFW");
			return;
		}
		LOG("Successfully initalized GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Create Window
		mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			LOG("Failed to create Window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(mWindow);

		//Load OpenGL functions
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG("Failed to initalize GLAD (OpenGL Loader)");
			glfwTerminate();
			return;
		}
	}

	window::~window()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	auto window::run() -> void
	{
		glViewport(0, 0, mWidth, mHeight);

		while (!glfwWindowShouldClose(mWindow))
		{
			glClearColor(0.5f, 0.0f, 0.5f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(mWindow);
			glfwPollEvents();
		}
	}
}