newoption {
   trigger = "projname",
   description = "VS Project Name"
}

newoption {
   trigger = "projdir",
   description = "VS Project Dir"
}

ProjectName = _OPTIONS["projname"] or "Default"
ProjectDir = _OPTIONS["projdir"] or ""
WyvernRootDir = os.getenv("WYVERN_DIR")

workspace "%{ProjectDir}/%{ProjectName}"
	targetdir "build"
	startproject "%{ProjectName}"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{WyvernRootDir}/WyvernEngine/Vendor/GLFW/include"
IncludeDir["GLAD"] = "%{WyvernRootDir}/WyvernEngine/Vendor/glad/include"
IncludeDir["GLM"] = "%{WyvernRootDir}/WyvernEngine/Vendor/glm"
IncludeDir["ImGUI"] = "%{WyvernRootDir}/WyvernEngine/Vendor/imgui"
IncludeDir["STB"] = "%{WyvernRootDir}/WyvernEngine/Vendor/stb_image"
IncludeDir["FreeType"] = "%{WyvernRootDir}/WyvernEngine/Vendor/freetype/include"
IncludeDir["FreeTypeSub"] = "%{WyvernRootDir}/WyvernEngine/Vendor/freetype/include/freetype"
IncludeDir["YamlCPP"] = "%{WyvernRootDir}/WyvernEngine/Vendor/yaml-cpp/include"
IncludeDir["ImGUIzmo"] = "%{WyvernRootDir}/WyvernEngine/Vendor/ImGuizmo"

project "%{ProjectName}"
	location "%{ProjectDir}/%{ProjectName}"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{ProjectDir}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{ProjectDir}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{ProjectDir}/%{ProjectName}/Source/**.h",
		"%{ProjectDir}/%{ProjectName}/Source/**.cpp"
	}

	includedirs
	{
		"%{ProjectDir}/%{ProjectName}/Source",
		"%{WyvernRootDir}/WyvernEngine/Source",
		"%{WyvernRootDir}/WyvernEditor/Source",
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
		"WyvernEngine",
		"WyvernEditor"
	}

	libdirs
	{
		"%{WyvernRootDir}/bin/" .. outputdir .. "/WyvernEngine",
		"%{WyvernRootDir}/bin/" .. outputdir .. "/WyvernEditor"
	}
	