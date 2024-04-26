#pragma once
#include "core/core.h"
#include "window.h"

namespace ray3D
{
	class engineApp : public window
	{
	public:
		engineApp(const appConfig& config);
		virtual ~engineApp() = default;

		auto run() -> void;

		//overrides
		virtual auto postAppInitialize() -> void = 0;
		virtual auto onUpdate(float deltaTime) -> void = 0;
		virtual auto onResize(const windowResizeEvent& resizeEvent) -> void override;
		virtual auto onDestroy() -> void override;

	private:
		bool mRunning = false;
		bool mSuspended = false;
		f64 mLastTime = 0.0f;
	};
}