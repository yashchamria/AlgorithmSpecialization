workspace "Algorithms"
	language "C++"
	cppdialect "C++20"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Course02"

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

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{prj.location}"

project "Course01"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"
	staticruntime "off"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"source/Course01/**.h",
		"source/Course01/**.cpp"
	}

	includedirs
	{
		"source/Course01/",
		"source/"
	}

	pchheader "PCH.h"
	pchsource "source/Course01/EntryPoint.cpp"

project "Course02"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"
	staticruntime "off"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"source/Course02/**.h",
		"source/Course02/**.cpp"
	}

	includedirs
	{
		"source/Course02/",
		"source/"
	}

	pchheader "PCH.h"
	pchsource "source/Course02/EntryPoint.cpp"