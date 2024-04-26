#pragma once
#include "core/core.h"

namespace ray3D
{
	class window;

	class time
	{
	public:
		static inline f64 startTime = 0.0f;
		static inline f64 elapsedTime = 0.0f;

	public:
		static auto init(window* windowHandl) -> void;
		static auto onUpdate() -> void;
		static auto shutdown() -> void;

	private:
		static inline window* mWindowHandl = nullptr;
	};
}