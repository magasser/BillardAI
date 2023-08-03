project "PoolAI"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"
    architecture "x64"

    DependenciesDir = "%{wks.location}/deps"

    IncludeDir = {}
    IncludeDir["spdlog"] = "%{DependenciesDir}/spdlog/include"
    IncludeDir["imgui"] = "%{DependenciesDir}/imgui"
    IncludeDir["imguiSFML"] = "%{DependenciesDir}/imgui-sfml"
    IncludeDir["SFML"] = "%{DependenciesDir}/SFML/include"
    IncludeDir["box2d"] = "%{DependenciesDir}/box2d/include"

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
        "%{IncludeDir.imguiSFML}",
        "%{IncludeDir.SFML}",
        "%{IncludeDir.box2d}",
    }

    defines
    {
        "SFML_STATIC"
    }

    links
    {
        "ImGuiSFML",
        "Box2D",
    }

	filter "configurations:Debug"
        defines "PA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
        defines "PA_RELEASE"
		runtime "Release"
		optimize "speed"

    filter "configurations:Dist"
        defines "PA_DIST"
		runtime "Release"
		optimize "speed"
        symbols "off"
