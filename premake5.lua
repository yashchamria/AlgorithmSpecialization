workspace "Algorithms"
	language "C++"
	cppdialect "C++20"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Algorithms"

filter "configurations:Debug"
	defines "ALGO_DEBUG"
	runtime "Debug"
	symbols "on"

filter "configurations:Release"
	defines "ALGO_RELEASE"
	runtime "Release"
	optimize "on"

filter "system:windows"
	defines "PLATFORM_WINDOWS"
	systemversion "latest"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Algorithms"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"
	staticruntime "off"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"source/**.h",
		"source/**.cpp",
	}

	includedirs
	{
		"source/",
	}

	pchheader "PCH.h"
	pchsource "source/EntryPoint.cpp"