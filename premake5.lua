workspace "ray3D"

	architecture "x64"
	startproject "app"

	configurations
	{
		"Debug",
		"Release"
	}

include("thirdparty/glfw")

project "ray3D"
	location "ray3D"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. project().name .. "/%{cfg.buildcfg}")
	objdir ("bin-int/" .. project().name .. "/%{cfg.buildcfg}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"thirdparty/GLAD/src/**.c",
		"assets/shaders/**.glsl"
	}

	includedirs
	{
		"%{prj.name}/src/",
		"thirdparty/GLAD/include/",
		"thirdparty/glfw/include/",
		"thirdparty/glm/",
		"thirdparty/spdlog/include/",
		"thirdparty/stb/",
	}

	links
	{
		"glfw"
	}

	filter "configurations:Debug"
		symbols "On"
		optimize "Off"
		buildoptions "/MDd"

	filter "configurations:Release"
		optimize "On"
		buildoptions "/MD"

project "app"
	location "app"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. project().name .. "/%{cfg.buildcfg}")
	objdir("bin-int/" .. project().name .. "/%{cfg.buildcfg}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ray3D/src/",
		"%{prj.name}/src/",
		"thirdparty/GLAD/include/",
		"thirdparty/glfw/include/",
		"thirdparty/glm/",
		"thirdparty/spdlog/include/",
	}

	links
	{
		"ray3D"
	}

	filter "configurations:Debug"
		symbols "On"
		optimize "Off"
		buildoptions "/MDd"

	filter "configurations:Release"
		optimize "On"
		buildoptions "/MD"