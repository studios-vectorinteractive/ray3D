#include <fstream>
#include <sstream>
#include <vector>

#include <glad/glad.h>

#include "window.h"
#include "core/core.h"
#include "event/eventManager.h"

namespace ray3D
{
	window::window(const appConfig& config):
		mWidth(config.width), mHeight(config.height), mTitle(config.title)
	{
		logger::init();
		eventManager::init();

		if (!glfwInit())
		{
			R3D_LOGE("Failed to initalize GLFW");
			return;
		}
		R3D_LOGD("Successfully initalized GLFW!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Create Window
		mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			R3D_LOGE("Failed to create Window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(mWindow);

		//Load OpenGL functions
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			R3D_LOGE("Failed to initalize GLAD (OpenGL Loader)");
			glfwTerminate();
			return;
		}

		//glfw events
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) 
			{
				eventManager::pushEvent<windowResizeEvent>(_ui32(width), _ui32(height));
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) 
			{
				eventManager::pushEvent<windowCloseEvent>();
			});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				const char* keyName = nullptr;
				switch (action)
				{
				case GLFW_PRESS:
					keyName = glfwGetKeyName(key, scancode);
					eventManager::pushEvent<keyPressedEvent>(key, keyName);
					break;
				case GLFW_RELEASE:
					keyName = glfwGetKeyName(key, scancode);
					eventManager::pushEvent<keyReleasedEvent>(key, keyName);
					break;
				case GLFW_REPEAT:
					keyName = glfwGetKeyName(key, scancode);
					eventManager::pushEvent<keyPressedEvent>(key, keyName);
					break;
				}
			});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xpos, double ypos)
			{
				eventManager::pushEvent<mouseMovedEvent>(xpos, ypos);
			}
		);

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				eventManager::pushEvent<mouseScrollEvent>(xoffset, yoffset);
			}
		);

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					eventManager::pushEvent<mouseButtonPressedEvent>(button);
					break;
				case GLFW_RELEASE:
					eventManager::pushEvent<mouseButtonReleasedEvent>(button);
					break;
				}
			}
		);

		//Events callbacks
		BIND_EVENT(eventType::windowResizeEvent, &window::onWindowResize);
		BIND_EVENT(eventType::windowCloseEvent, &window::onWindowClose);
	}

	window::~window()
	{
		eventManager::shutdown();
		logger::shutdown();
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	auto window::updateInput() -> void
	{
		glfwPollEvents();
	}

	auto window::swapBuffers() -> void
	{
		glfwSwapBuffers(mWindow);
	}

	auto window::onWindowResize(const event& resizeEvent) -> void
	{
		const windowResizeEvent& incResizeEvent = getEventFromBase<windowResizeEvent>(resizeEvent);
		mWidth = incResizeEvent.getWidth();
		mHeight = incResizeEvent.getHeight();

		onResize(incResizeEvent);	//app level		
	}

	auto window::onWindowClose(const event& closeEvent) -> void
	{
		R3D_LOGD("onWindowClose invoked");
		onDestroy();
	}
}