#pragma once
//std includes
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "core/core.h"
#include "event/event.h"

namespace ray3D
{

	typedef struct appConfig
	{
		ui32 width;
		ui32 height;
		std::string title;
	}appConfig;

	class window
	{
	public:
		window(const appConfig& config);
		virtual ~window();

		//Getters
		auto getWidth() const -> ui32 { return mWidth; }
		auto getHeight() const -> ui32 { return mHeight; }

		auto getGLFWwindow() const -> GLFWwindow* { return mWindow; }
		auto getGLFWwindow() -> GLFWwindow* { return mWindow; }
		auto getTitle() const -> const std::string& { return mTitle; }
		auto getTime() const -> f64 { return glfwGetTime(); }

		//Events
		auto onWindowResize(const event& resizeEvent) -> void;
		auto onWindowClose(const event& closeEvent) -> void;

		//Application interface
		virtual auto onResize(const windowResizeEvent& resizeEvent) -> void = 0;
		virtual auto onDestroy() -> void = 0;

	protected:
		auto updateInput() -> void;
		auto swapBuffers() -> void;

	private:
		std::string mTitle = {};
		ui32 mWidth = {};
		ui32 mHeight = {};

		GLFWwindow* mWindow = {};
	};
}

/*

class engineApp : public window
{
public:
	engineApp(const config&):window(config){}

	void run()
	{
		postAppInitialize();

		while(mRunning)
		{
			
		}
	}


	//overrides
	virtual auto postAppInitialize() -> void = 0;
	virtual auto onResize(windowResizeEvent) void = 0;
	virtual auto onDestroy() -> void = 0;

private:
	bool mRunning = false;
	bool mSuspended = false;

}

*/