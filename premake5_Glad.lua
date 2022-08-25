project "Glad"
    location "Hazel/vendor/Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir (bin_dir .. "/%{prj.name}")
	objdir (bin_int_dir .. "/%{prj.name}")

    files
    {
        "Hazel/vendor/Glad/include/glad/glad.h",
        "Hazel/vendor/Glad/include/KHR/khrplatform.h",
        "Hazel/vendor/Glad/src/glad.c",
    }

    includedirs
    {
        "Hazel/vendor/Glad/include",
    }

    filter "system:windows"
        systemversion "10.0.19041.0"
        

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
