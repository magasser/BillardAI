project "ImGui"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "off"
	warnings "off"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

	includedirs
	{
		"imgui",
	}

	files
	{
		"imgui/imconfig.h",
		"imgui/imgui.h",
		"imgui/imgui.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_tables.cpp",
		"imgui/imgui_widgets.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h",
		"imgui/imgui_demo.cpp",
        -- "imgui/backends/imgui_impl_glfw.h",
        -- "imgui/backends/imgui_impl_glfw.cpp",
        -- "imgui/backends/imgui_impl_opengl3.h",
        -- "imgui/backends/imgui_impl_opengl3.cpp",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"

project "SFML"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
    staticruntime "off"
	warnings "off"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

	includedirs
	{
		"SFML/include",
		"SFML/src",

		"SFML/extlibs/headers/stb_image",
		"SFML/extlibs/headers/glad/include",
		"SFML/extlibs/headers/freetype2",
		"SFML/extlibs/headers/vulkan",
	}

	files
	{
		"SFML/src/SFML/Window/*.hpp",
		"SFML/src/SFML/Window/*.cpp",
		"SFML/src/SFML/Graphics/*.hpp",
		"SFML/src/SFML/Graphics/*.cpp",
	}

	defines "SFML_STATIC"

	filter "system:windows"
		systemversion "latest"

		files
		{
			"SFML/src/SFML/Main/MainWin32.cpp",
			"SFML/src/SFML/Window/Win32/*.hpp",
			"SFML/src/SFML/Window/Win32/*.cpp",
		}

		links
		{
			"SFML/extlibs/libs-msvc-universal/x64/*.lib",
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"

project "Box2D"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	warnings "off"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

	includedirs
	{
		"box2d/include",
		"box2d/src",
	}

	files
	{
		"box2d/src/**.h",
		"box2d/src/**.cpp",
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
		symbols "off"