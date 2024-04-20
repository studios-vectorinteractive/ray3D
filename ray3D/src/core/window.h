#pragma once
//std includes
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "core/core.h"
#include "event/event.h"

namespace ray3D
{
	class window
	{
	public:
		window(const ui32 Width, const ui32 Height, const std::string& Title);
		~window();

		auto run() -> void;

		//Getters
		auto getWidth() const -> ui32 { return mWidth; }
		auto getHeight() const -> ui32 { return mHeight; }

		auto getGLFWwindow() const -> GLFWwindow* { return mWindow; }
		auto getGLFWwindow() -> GLFWwindow* { return mWindow; }
		auto getTitle() const -> const std::string& { return mTitle; }

		//Events
		auto onWindowResize(const event* resizeEvent) -> void;
		auto onWindowClose(const event* closeEvent) -> void;

	private:
		std::string mTitle = {};
		ui32 mWidth = {};
		ui32 mHeight = {};
		bool mIsRunning = false;

		GLFWwindow* mWindow = {};
	};
}