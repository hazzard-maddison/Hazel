project "Hazel"
	location "Hazel"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"

	targetdir (bin_dir .. "/%{prj.name}")
	objdir (bin_int_dir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "Hazel/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/**.hpp",
		"%{prj.name}/vendor/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include/",
		"%{prj.name}/src/",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}


	filter "system:windows"
		systemversion "10.0.19041.0"

		defines
		{
			"HZ_PLATFORM_WINDOWS",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}
		

		-- postbuildcommands
		-- {
		-- 	"copy $(TargetDir)\\Hazel.dll $(SolutionDir)bin\\"..output_dir.."\\Sandbox\\"
		-- }

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
