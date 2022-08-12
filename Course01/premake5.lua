workspace "Course01"
	language "C++"
	cppdialect "C++20"
	architecture "x64"
	configurations { "Debug", "Release" }

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

project "KaratsubaMultiplication"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"KaratsubaMultiplication/**.h",
		"KaratsubaMultiplication/**.cpp"
	}

project "MergeSort"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"MergeSort/**.h",
		"MergeSort/**.cpp"
	}

project "QuickSort"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"QuickSort/**.h",
		"QuickSort/**.cpp"
	}

project "QuickSelect"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"QuickSelect/**.h",
		"QuickSelect/**.cpp"
	}

project "KargerMinCut"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"KargerMinCut/**.h",
		"KargerMinCut/**.cpp"
	}

project "ClosestPair"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"ClosestPair/**.h",
		"ClosestPair/**.cpp"
	}