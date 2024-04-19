#include <iostream>
#include <memory>

#include "core/window.h"
#include "core/core.h"

int main()
{

	std::unique_ptr<ray3D::window> app = std::make_unique<ray3D::window>(800, 600, "Ray3D");

	R3D_LOGI("Window width : {}", app->getWidth());
	R3D_LOGI("Window height : {}", app->getHeight());
	R3D_LOGI("Window Title : {}", app->getTitle().c_str());

	app->run();

	return EXIT_SUCCESS;
}