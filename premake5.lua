workspace "Algorithms"
	language "C++"
	cppdialect "C++20"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Algorithms"

filter "configurations:Debug"
	defines "MS_DEBUG"
	runtime "Debug"
	symbols "on"

filter "configurations:Release"
	defines "MS_RELEASE"
	runtime "Release"
	optimize "on"

filter "system:windows"
	defines "PLATFORM_WINDOWS"
	systemversion "latest"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Algorithms"
	kind "ConsoleApp"
	location "%{wks.location}/Intermediate/%{prj.name}"
	staticruntime "off"

	targetdir ("%{wks.location}/Binaries/%{prj.name}/" ..outputDir.. "/")
	objdir ("%{wks.location}/Intermediate/%{prj.name}/" ..outputDir.. "/")

	files
	{
		"Source/**.h",
		"Source/**.cpp",
	}

	includedirs
	{
		"Source/",
	}

	pchheader "PCH.h"
	pchsource "Source/EntryPoint.cpp"