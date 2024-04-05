#pragma once
//std includes
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace ray3D
{
	class window
	{
	public:
		window(const uint32_t Width, const uint32_t Height, const std::string& Title);
		~window();

		auto run() -> void;

		//Getters
		auto getWidth() const -> uint32_t{ return mWidth; }
		auto getHeight() const -> uint32_t{ return mHeight; }

		auto getGLFWwindow() const -> GLFWwindow* { return mWindow; }
		auto getGLFWwindow() -> GLFWwindow* { return mWindow; }
		auto getTitle() const -> const std::string& { return mTitle; }

	private:
		std::string mTitle = {};
		uint32_t mWidth = {};
		uint32_t mHeight = {};

		GLFWwindow* mWindow = {};
	};
}