workspace "Hazel"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

output_dir   = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
bin_dir = "bin/" .. output_dir
bin_int_dir = "bin-int/" .. output_dir

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazel/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazel/vendor/Glad/include"

group "vendor"
    include "premake5_GLFW.lua"
    include "premake5_Glad.lua"

group ""
    include "premake5_Hazel.lua"
    include "premake5_Sandbox.lua"


