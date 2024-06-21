#pragma once
#include "core/core.h"
#include "keycodes.h"
#include <glm/glm.hpp>

struct GLFWwindow;

namespace ray3D
{
	class input
	{
	public:

		static auto init(GLFWwindow* windowHndl) -> void;
		static auto shutdown() -> void;
		
		static auto update(f32 deltaTime) -> void;

		static auto isKeyPressed(const keyCode key) -> bool;
		static auto isKeyReleased(const keyCode key) -> bool;
		static auto isButtonPressed(const mouseCode button) -> bool;
		static auto isButtonReleased(const mouseCode button) -> bool;

		static auto getMousePosition() -> glm::vec2;
		static auto getMouseDelta() -> glm::vec2;

		static auto setCursorVisible(bool state) -> void;

	private:
		input() = default;
		~input() = default;

	private:
		static inline bool mInitialized = false;
		static inline glm::vec2 mMouseDelta = {};
		static inline glm::vec2 mLastMousePosition = {};
	};
}