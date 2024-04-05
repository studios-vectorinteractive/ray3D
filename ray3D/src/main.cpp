#include <iostream>
#include <memory>

#include "window.h"
#include "log.h"

int main()
{

	std::unique_ptr<ray3D::window> app = std::make_unique<ray3D::window>(800, 600, "Ray3D");

	LOG("Window width : %d", app->getWidth());
	LOG("Window height : %d", app->getHeight());
	LOG("Window Title : %s", app->getTitle().c_str());

	app->run();

	return EXIT_SUCCESS;
}