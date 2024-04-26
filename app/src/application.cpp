#include "application.h"

std::unique_ptr<ray3D::engineApp> createApplication(const ray3D::appConfig& config)
{
	return std::make_unique<ray3D::application>(config);
}

namespace ray3D
{
	application::application(const appConfig& config):engineApp(config)
	{
		R3D_LOGD("Application created");
	}

	auto application::postAppInitialize() -> void
	{

	}

	auto application::onUpdate(float deltaTime) -> void
	{

	}

	auto application::onResize(const windowResizeEvent& resizeEvent) -> void
	{
		engineApp::onResize(resizeEvent);
	}

	auto application::onDestroy() -> void
	{
		engineApp::onDestroy();
	}
}