#include "time.h"
#include "core/window.h"

namespace ray3D
{
	auto time::init(window* windowHandl) -> void
	{
		if (!windowHandl)
		{
			R3D_LOGE("Invalid reference to window handle, failed to initialize timer");
			return;
		}

		mWindowHandl = windowHandl;
		startTime = mWindowHandl->getTime();
		elapsedTime = 0.0f;
	}

	auto time::onUpdate() -> void
	{
		elapsedTime = mWindowHandl->getTime() - startTime;
	}

	auto time::shutdown() -> void
	{
		startTime = elapsedTime = 0.0f;
	}
}