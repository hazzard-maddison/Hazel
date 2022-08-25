project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"
	


	targetdir (bin_dir .. "/%{prj.name}")
	objdir (bin_int_dir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Hazel/vendor/spdlog/include",
		"Hazel/src",
		"Hazel/vendor",
		"%{IncludeDir.glm}",
	}

	links
	{
		"Hazel"
	}

	filter "system:windows"
		systemversion "10.0.19041.0"

		defines
		{
			"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"