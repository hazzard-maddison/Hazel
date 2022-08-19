function script_path()
   local str = debug.getinfo(2, "S").source:sub(2)
   return str:match("(.*/)")
end

workspace "Hazel"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

solution_dir = script_path() -- the location of main.lua breaks if moved from solution dir
output_dir   = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
bin_dir = solution_dir .. "/bin/" .. output_dir
bin_int_dir = solution_dir .. "/bin-int/" .. output_dir

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


