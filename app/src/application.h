#pragma once
#include <entry.h>

namespace ray3D
{
	class application : public engineApp
	{
	public:
		application(const appConfig& config);
		virtual ~application() = default;

		// Inherited via engineApp
		virtual auto postAppInitialize() -> void override;
		virtual auto onUpdate(float deltaTime) -> void override;
		virtual auto onResize(const windowResizeEvent& resizeEvent) -> void override;
		virtual auto onDestroy() -> void override;

	private:

	};
}