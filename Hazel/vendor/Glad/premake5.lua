project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin/"..outputdir.."/%prj.name")

    files
    {
        "include/glad/glad.h",
        "include/KHR/khrplatform.h",
        "src/glad.c",
    }

    includedirs
    {
        "include",
    }

    filter "system:windows"
        systemversion "10.0.19041.0"
        staticruntime "on"

    filter {"system:windows", "configurations:Release"}
        buildoptions "/MT"

    