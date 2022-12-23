workspace "BasicRayTracer"
	architecture "x86_64"
	startproject "BasicRayTracer"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["glm"] = "BasicRayTracer/vendor/glm"


project "BasicRayTracer"
    location "BasicRayTracer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"


	targetdir("bin/" .. outputdir ..  "/%{prj.name}")
	objdir("bin-int/" .. outputdir ..  "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	defines
	{	
		"_CRT_SECURE_NO_WARNINGS" 
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.glm}"
	}



	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "BRT_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "BRT_REALESE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "BRT_DIST"
		runtime "Release"
		optimize "on"

