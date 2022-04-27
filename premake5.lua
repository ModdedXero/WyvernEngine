workspace "Merlin"
	architecture "x64"
	startproject  "Excalibur"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

IncludeDir = {}
IncludeDir["GLFW"] = "Merlin/Vendor/GLFW/include"
IncludeDir["GLAD"] = "Merlin/Vendor/glad/include"
IncludeDir["GLM"] = "Merlin/Vendor/glm"
IncludeDir["ImGUI"] = "Merlin/Vendor/imgui"
IncludeDir["STB"] = "Merlin/Vendor/stb_image"
IncludeDir["FreeType"] = "Merlin/Vendor/freetype/include"
IncludeDir["FreeTypeSub"] = "Merlin/Vendor/freetype/include/freetype"
IncludeDir["YamlCPP"] = "Merlin/Vendor/yaml-cpp/include"
IncludeDir["ImGUIzmo"] = "Merlin/Vendor/ImGuizmo"

include "Merlin/Vendor/GLFW"
include "Merlin/Vendor/ImGui"
include "Merlin/Vendor/FreeType"
include "Merlin/Vendor/yaml-cpp"
	
project "Merlin"
	location "Merlin/Source"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "mlpch.h"
	pchsource "merlin/source/mlpch.cpp"

	files
	{
		"Merlin/Source/**.h",
		"Merlin/Source/**.cpp",
		"Merlin/Vendor/stb_image/**.h",
		"Merlin/Vendor/stb_image/**.cpp",
		"Merlin/Vendor/glad/**.c",
		"Merlin/Vendor/ImGuizmo/ImGuizmo.h",
		"Merlin/Vendor/ImGuizmo/ImGuizmo.cpp"
	}

	includedirs
	{
		"Merlin/Source",
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
	
	filter "files:Merlin/Vendor/**.c"
		flags { "NoPCH" }
	filter "files:Merlin/Vendor/**.cpp"
		flags { "NoPCH" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ML_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ML_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ML_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ML_DIST"
		optimize "On"

project "Excalibur"
	location "Excalibur/Source"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Excalibur/Source/**.h",
		"Excalibur/Source/**.cpp"
	}

	includedirs
	{
		"Merlin/Source",
		"Excalibur/Source",
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
		"Merlin"
	}
	
	postbuildcommands
	{
		"{COPY} ../../bin/" .. outputdir .. "/Merlin/*.dll ../../bin/" .. outputdir .. "/Excalibur"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ML_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ML_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ML_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ML_DIST"
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
		"Merlin/Source",
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
		"Merlin"
	}
	
	postbuildcommands
	{
		"{COPY} ../../bin/" .. outputdir .. "/Merlin/*.dll ../../bin/" .. outputdir .. "/Sandbox"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ML_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ML_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ML_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ML_DIST"
		optimize "On"