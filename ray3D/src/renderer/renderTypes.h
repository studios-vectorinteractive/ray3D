#pragma once

namespace ray3D
{


	enum class rendererBackendType
	{
		openGL,
		vulkan,
		directX,
		none
	};

	enum class drawMode
	{
		index, 
		arrays
	};

}