#include <iostream>
#include <memory>

#include "core/engineApp.h"
#include "core/core.h"

extern std::unique_ptr<ray3D::engineApp> createApplication(const ray3D::appConfig& config);

int main(int argc, const char* argv[])
{

	ray3D::appConfig config;
	config.width = 800;
	config.height = 600;
	config.title = std::string(argv[0]) + " - Ray3D";

	std::unique_ptr<ray3D::engineApp> app = createApplication(config);

	R3D_LOGI("Window width : {}", app->getWidth());
	R3D_LOGI("Window height : {}", app->getHeight());
	R3D_LOGI("Window Title : {}", app->getTitle().c_str());

	app->run();

	return EXIT_SUCCESS;
}