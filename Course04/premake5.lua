workspace "Course04"
	language "C++"
	cppdialect "C++20"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Course04"

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

project "BellmanFord"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"BellmanFord/**.h",
		"BellmanFord/**.cpp"
	}

project "FloydWarshall"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"FloydWarshall/**.h",
		"FloydWarshall/**.cpp"
	}