workspace "Binviz"
	architecture "x64"
	startproject "Binviz"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}

project "Binviz"
	location "Binviz"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		
	}

	links
	{
		
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines { "DEBUG" }
		runtime "Debug"
		symbols "on"
		debugargs { 
			"C:\\dev\\Binviz\\data\\text.txt",
			"C:\\dev\\Binviz\\data\\image.png",
			"C:\\dev\\Binviz\\data\\image.png.raw",
			"C:\\dev\\Binviz\\data\\wav_audio.wav"
		}


	filter "configurations:Release"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		optimize "on"
