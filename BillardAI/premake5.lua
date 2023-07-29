project "BillardAI"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"
    architecture "x64"

    IncludeDir = {}
    IncludeDir["spdlog"] = "../vendor/spdlog/include"
    IncludeDir["imgui"] = "../vendor/imgui"
    IncludeDir["SFML"] = "../vendor/SFML/include"
    IncludeDir["box2d"] = "../vendor/box2d/include"

    targetdir ("bin/" .. OutputDir)
    objdir ("bin-int/" .. OutputDir)    

    pchheader "bapch.h"
    pchsource "src/bapch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    includedirs
    {
        "src",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.SFML}",
        "%{IncludeDir.box2d}",
    }

    links
    {
        "ImGui",
        "SFML",
        "Box2D",
    }

	filter "configurations:Debug"
        defines "BA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
        defines "BA_RELEASE"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
        defines "BA_DIST"
		runtime "Release"
		optimize "speed"
        symbols "off"
