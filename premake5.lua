workspace "WyvernEngine"
	architecture "x64"
	startproject  "WyvernEditor"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

IncludeDir = {}
IncludeDir["GLFW"] = "WyvernEngine/Vendor/GLFW/include"
IncludeDir["GLAD"] = "WyvernEngine/Vendor/glad/include"
IncludeDir["GLM"] = "WyvernEngine/Vendor/glm"
IncludeDir["ImGUI"] = "WyvernEngine/Vendor/imgui"
IncludeDir["STB"] = "WyvernEngine/Vendor/stb_image"
IncludeDir["FreeType"] = "WyvernEngine/Vendor/freetype/include"
IncludeDir["FreeTypeSub"] = "WyvernEngine/Vendor/freetype/include/freetype"
IncludeDir["YamlCPP"] = "WyvernEngine/Vendor/yaml-cpp/include"
IncludeDir["ImGUIzmo"] = "WyvernEngine/Vendor/ImGuizmo"

include "WyvernEngine/Vendor/GLFW"
include "WyvernEngine/Vendor/ImGui"
include "WyvernEngine/Vendor/FreeType"
include "WyvernEngine/Vendor/yaml-cpp"
	
project "WyvernEngine"
	location "WyvernEngine/Source"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "wvpch.h"
	pchsource "WyvernEngine/source/wvpch.cpp"

	files
	{
		"WyvernEngine/Source/**.h",
		"WyvernEngine/Source/**.cpp",
		"WyvernEngine/Vendor/stb_image/**.h",
		"WyvernEngine/Vendor/stb_image/**.cpp",
		"WyvernEngine/Vendor/glad/**.c",
		"WyvernEngine/Vendor/ImGuizmo/ImGuizmo.h",
		"WyvernEngine/Vendor/ImGuizmo/ImGuizmo.cpp"
	}

	includedirs
	{
		"WyvernEngine/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.FreeTypeSub}",
		"%{IncludeDir.YamlCPP}",
		"%{IncludeDir.ImGUIzmo}"
	}

	links
	{
		"GLFW",
		"ImGui",
		"FreeType",
		"yaml-cpp",
		"opengl32.lib"
	}
	
	filter "files:WyvernEngine/Vendor/**.c"
		flags { "NoPCH" }
	filter "files:WyvernEngine/Vendor/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WV_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "WV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "WV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "WV_DIST"
		optimize "On"

project "WyvernEditor"
	location "WyvernEditor/Source"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"WyvernEditor/Source/**.h",
		"WyvernEditor/Source/**.cpp"
	}

	includedirs
	{
		"WyvernEngine/Source",
		"WyvernEditor/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.FreeTypeSub}",
		"%{IncludeDir.YamlCPP}",
		"%{IncludeDir.ImGUIzmo}"
	}

	links
	{
		"WyvernEngine"
	}
	
	postbuildcommands
	{
		"{COPY} ../../bin/" .. outputdir .. "/WyvernEngine/*.dll ../../bin/" .. outputdir .. "/WyvernEditor"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WV_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "WV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "WV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "WV_DIST"
		optimize "On"
		
project "Sandbox"
	location "Sandbox/Source"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Sandbox/Source/**.h",
		"Sandbox/Source/**.cpp"
	}

	includedirs
	{
		"WyvernEngine/Source",
		"Sandbox/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.FreeTypeSub}"
	}

	links
	{
		"WyvernEngine"
	}
	
	postbuildcommands
	{
		"{COPY} ../../bin/" .. outputdir .. "/WyvernEngine/*.dll ../../bin/" .. outputdir .. "/Sandbox"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"WV_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "WV_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "WV_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "WV_DIST"
		optimize "On"