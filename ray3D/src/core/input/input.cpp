#include "input.h"
#include <GLFW/glfw3.h>

namespace ray3D
{
	static GLFWwindow* __internal_window_handle = nullptr;

	auto input::init(GLFWwindow* windowHndl) -> void
	{
		if (mInitialized)
		{
			R3D_LOGW("Input system already initialized");
			return;
		}

		if (!__internal_window_handle)
		{
			R_ASSERT(windowHndl);

			__internal_window_handle = windowHndl;
			mInitialized = true;

			R3D_LOGD("Input system initialized");
		}
	}

	auto input::shutdown() -> void
	{
		__internal_window_handle = nullptr;
		mInitialized = false;
		R3D_LOGD("Shutting down input system...");
	}

	auto input::update(f32 deltaTime) -> void
	{
		glm::vec2 mousePos = getMousePosition();
		mMouseDelta = mousePos - mLastMousePosition;
		mLastMousePosition = mousePos;
	}

	auto input::isKeyPressed(const keyCode key) -> bool
	{
		R_ASSERT(__internal_window_handle);
		int keyState = glfwGetKey(__internal_window_handle, _i32(key));
		return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
	}

	auto input::isKeyReleased(const keyCode key) -> bool
	{
		R_ASSERT(__internal_window_handle);
		int keyState = glfwGetKey(__internal_window_handle, _i32(key));
		return keyState == GLFW_RELEASE;
	}

	auto input::isButtonPressed(const mouseCode button) -> bool
	{
		R_ASSERT(__internal_window_handle);
		int buttonState = glfwGetMouseButton(__internal_window_handle, _i32(button));
		return buttonState == GLFW_PRESS || buttonState == GLFW_REPEAT;
	}

	auto input::isButtonReleased(const mouseCode button) -> bool
	{
		R_ASSERT(__internal_window_handle);
		int buttonState = glfwGetMouseButton(__internal_window_handle, _i32(button));
		return buttonState == GLFW_RELEASE;
	}

	auto input::getMousePosition() -> glm::vec2
	{
		R_ASSERT(__internal_window_handle);
		f64 xPos;
		f64 yPos;
		glfwGetCursorPos(__internal_window_handle, &xPos, &yPos);

		return glm::vec2(_f32(xPos), _f32(yPos));
	}

	auto input::getMouseDelta() -> glm::vec2
	{
		return mMouseDelta;
	}

	auto input::setCursorVisible(bool state) -> void
	{
		R_ASSERT(__internal_window_handle);
		glfwSetInputMode(__internal_window_handle, GLFW_CURSOR, state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
	}
}