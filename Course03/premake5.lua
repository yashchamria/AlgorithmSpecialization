workspace "Course03"
	language "C++"
	cppdialect "C++20"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Course03"

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

project "JobScheduler"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"JobScheduler/**.h",
		"JobScheduler/**.cpp"
	}

project "PrimMST"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"PrimMST/**.h",
		"PrimMST/**.cpp"
	}

project "KruskalMST"
	kind "ConsoleApp"
	location "%{wks.location}/intermediate"

	targetdir ("%{wks.location}/binaries/" ..outputDir.. "/")
	objdir ("%{wks.location}/intermediate/" ..outputDir.. "/")

	files
	{
		"KruskalMST/**.h",
		"KruskalMST/**.cpp"
	}