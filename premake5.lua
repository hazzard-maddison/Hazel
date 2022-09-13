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
IncludeDir["glm"]  = "Hazel/vendor/glm"
IncludeDir["imgui"] = "Hazel/vendor/imgui"
IncludeDir["stb_image"] = "Hazel/vendor/stb_image"



group "vendor"
    include "premake5_GLFW.lua"
    include "premake5_Glad.lua"
	include "premake5_imgui.lua"

group ""
    include "premake5_Hazel.lua"
    include "premake5_Sandbox.lua"


