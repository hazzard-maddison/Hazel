workspace "Hazel"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"

include "Hazel/vendor/GLFW"

project "Hazel"
	location "Hazel"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include/",
		"%{prj.name}/src/",
		"%{IncludeDir.GLFW}",
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "10.0.19041.0"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL"
		}

		postbuildcommands
		{
			"copy $(TargetDir)\\Hazel.dll $(SolutionDir)bin\\"..outputdir.."\\Sandbox\\"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src"
	}

	links
	{
		"Hazel"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "off"
		systemversion "10.0.19041.0"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "HZ_DIST"
		optimize "On"