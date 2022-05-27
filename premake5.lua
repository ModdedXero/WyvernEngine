workspace "WyvernEngine"
	architecture "x64"
	startproject  "WyvernBuilder"
	
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
IncludeDir["AssImp"] = "WyvernEngine/Vendor/Assimp/inlcude"

include "WyvernEngine/Vendor/GLFW"
include "WyvernEngine/Vendor/ImGui"
include "WyvernEngine/Vendor/FreeType"
include "WyvernEngine/Vendor/yaml-cpp"
include "WyvernEngine/Vendor/Assimp"
	
project "WyvernEngine"
	location "WyvernEngine/Source"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "wvpch.h"
	pchsource "WyvernEngine/Source/wvpch.cpp"

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
		"%{IncludeDir.ImGUIzmo}",
		"%{IncludeDir.AssImp}"
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
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"WyvernEditor/Source/**.h",
		"WyvernEditor/Source/**.cpp"
	}
	
	includedirs
	{
		"WyvernEditor/Source",
		"WyvernEngine/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.STB}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.FreeTypeSub}",
		"%{IncludeDir.YamlCPP}",
		"%{IncludeDir.ImGUIzmo}",
		"%{IncludeDir.AssImp}"
	}
	
	links
	{
		"WyvernEngine"
	}
	
	filter "system:windows"
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

project "WyvernBuilder"
	location "WyvernBuilder"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"WyvernBuilder/**.h",
		"WyvernBuilder/**.cpp"
	}

	includedirs
	{
		"WyvernEngine/Source",
		"WyvernEditor/Source",
		"WyvernBuilder/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.FreeType}",
		"%{IncludeDir.FreeTypeSub}",
		"%{IncludeDir.YamlCPP}",
		"%{IncludeDir.ImGUIzmo}",
		"%{IncludeDir.AssImp}"
	}

	links
	{
		"WyvernEngine",
		"WyvernEditor"
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