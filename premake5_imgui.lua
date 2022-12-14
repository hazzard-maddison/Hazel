project "imgui"
    location "Hazel/vendor/imgui"
    kind "StaticLib"
    staticruntime "on"
    language "C++"
    cppdialect "C++20"
    

    targetdir (bin_dir .. "/%{prj.name}")
	objdir (bin_int_dir .. "/%{prj.name}")

    files
    {
        "Hazel/vendor/imgui/imconfig.h",
        "Hazel/vendor/imgui/imgui_demo.cpp",
        "Hazel/vendor/imgui/imgui_draw.cpp",
        "Hazel/vendor/imgui/imgui_internal.h",
        "Hazel/vendor/imgui/imgui_tables.cpp",
        "Hazel/vendor/imgui/imgui_widgets.cpp",
        "Hazel/vendor/imgui/imgui.cpp",
        "Hazel/vendor/imgui/imgui.h",
        "Hazel/vendor/imgui/imstb_rectpack.h",
        "Hazel/vendor/imgui/imstb_textedit.h",
        "Hazel/vendor/imgui/imstb_truetype.h",

        -- "Hazel/vendor/imgui/backends/imgui_impl_opengl3_loader.h",
        -- "Hazel/vendor/imgui/backends/imgui_impl_opengl3.cpp",
        -- "Hazel/vendor/imgui/backends/imgui_impl_opengl3.h",

        -- "Hazel/vendor/imgui/backends/imgui_impl_glfw.cpp",
        -- "Hazel/vendor/imgui/backends/imgui_impl_glfw.h",
    }

    includedirs
    {
        -- "%{IncludeDir['GLFW']}",
        -- "Hazel/vendor/imgui"
    }


    filter "system:windows"
        systemversion "10.0.19041.0"
        
    
   filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
    