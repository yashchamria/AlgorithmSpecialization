workspace "Course02"
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

project "Kosaraju"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"Kosaraju/**.h",
		"Kosaraju/**.cpp"
	}

project "TopologicalSort"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"TopologicalSort/**.h",
		"TopologicalSort/**.cpp"
	}

project "Dijkstra"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"Dijkstra/**.h",
		"Dijkstra/**.cpp"
	}

project "MedianMaintenance"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"MedianMaintenance/**.h",
		"MedianMaintenance/**.cpp"
	}

project "HeapSort"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"HeapSort/**.h",
		"HeapSort/**.cpp"
	}

project "TwoSum"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"TwoSum/**.h",
		"TwoSum/**.cpp"
	}