workspace "Merlin"
	architecture "x64"
	startproject  "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

IncludeDir = {}
IncludeDir["GLFW"] = "Merlin/vendor/GLFW/include"
IncludeDir["GLAD"] = "Merlin/vendor/glad/include"
IncludeDir["GLM"] = "Merlin/vendor/glm"
IncludeDir["ImGUI"] = "Merlin/vendor/imgui"
IncludeDir["STB"] = "Merlin/vendor/stb_image"

include "Merlin/vendor/GLFW"
include "Merlin/vendor/ImGui"
	
project "Merlin"
	location "Merlin/src"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "mlpch.h"
	pchsource "mlpch.cpp"

	files
	{
		"Merlin/src/**.h",
		"Merlin/src/**.cpp",
		"Merlin/vendor/stb_image/**.h",
		"Merlin/vendor/stb_image/**.cpp",
		"Merlin/vendor/glad/**.c"
	}

	includedirs
	{
		"Merlin/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGUI}",
		"%{IncludeDir.STB}"
	}

	links
	{
		"GLFW",
		"ImGui",
		"opengl32.lib"
	}
	
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

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Sandbox/src/**.h",
		"Sandbox/src/**.cpp"
	}

	includedirs
	{
		"Merlin/src",
		"Sandbox/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.GLAD}"
	}

	links
	{
		"Merlin"
	}
	
	postbuildcommands
	{
		"{COPY} ../bin/" .. outputdir .. "/Merlin/*.dll ../bin/" .. outputdir .. "/Sandbox"
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