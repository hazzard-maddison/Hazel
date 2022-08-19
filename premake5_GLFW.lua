project "GLFW"
    location "Hazel/vendor/GLFW"
    kind "StaticLib"
    language "C"

    targetdir (bin_dir .. "/%{prj.name}")
	objdir (bin_int_dir .. "/%{prj.name}")

    files
    {
        "Hazel/vendor/GLFW/include/GLFW/glfw3.h",
        "Hazel/vendor/GLFW/include/GLFW/glfw3native.h",
        "Hazel/vendor/GLFW/src/glfw_config.h",
        "Hazel/vendor/GLFW/src/context.c",
        "Hazel/vendor/GLFW/src/init.c",
        "Hazel/vendor/GLFW/src/input.c",
        "Hazel/vendor/GLFW/src/monitor.c",

        "Hazel/vendor/GLFW/src/null_init.c",
        "Hazel/vendor/GLFW/src/null_joystick.c",
        "Hazel/vendor/GLFW/src/null_monitor.c",
        "Hazel/vendor/GLFW/src/null_window.c",

        "Hazel/vendor/GLFW/src/platform.c",
        "Hazel/vendor/GLFW/src/vulkan.c",
        "Hazel/vendor/GLFW/src/window.c",
    }

    -- future
        -- Linux support in future
        -- filter "system:linux"
        --     pic "On"

        --     systemversion "latest"

        --     files
        --     {
        --         "src/x11_init.c",
        --         "src/x11_monitor.c",
        --         "src/x11_window.c",
        --         "src/xkb_unicode.c",
        --         "src/posix_time.c",
        --         "src/posix_thread.c",
        --         "src/glx_context.c",
        --         "src/egl_context.c",
        --         "src/osmesa_context.c",
        --         "src/linux_joystick.c"
        --     }

        --     defines
        --     {
        --         "_GLFW_X11"
        --     }
    --end future       
    
    
    filter "system:windows"
        systemversion "10.0.19041.0"
        staticruntime "on"

        files
        {
            "Hazel/vendor/GLFW/src/win32_init.c",
            "Hazel/vendor/GLFW/src/win32_joystick.c",
            "Hazel/vendor/GLFW/src/win32_module.c",
            "Hazel/vendor/GLFW/src/win32_monitor.c",
            "Hazel/vendor/GLFW/src/win32_time.c",
            "Hazel/vendor/GLFW/src/win32_thread.c",
            "Hazel/vendor/GLFW/src/win32_window.c",
            "Hazel/vendor/GLFW/src/wgl_context.c",
            "Hazel/vendor/GLFW/src/egl_context.c",
            "Hazel/vendor/GLFW/src/osmesa_context.c"
        }

        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        links
        {
            "Dwmapi.lib"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        symbols "on"
    
    filter "configurations:Dist"
        runtime "Release"
        symbols "on"

    symbols "off"

    
