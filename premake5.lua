workspace "BasicRayTracer"
	architecture "x86_64"
	startproject "BasicRayTracer"

	configurations
	{
		"Debug",
		"Release"
	}
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["glm"] = "BasicRayTracer/vendor/glm"
IncludeDir["stb_image"] = "BasicRayTracer/vendor/stb_image"



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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"

	}
	
	defines
	{	
		"_CRT_SECURE_NO_WARNINGS" 
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
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
		symbols "Off"
		optimize "Full"  
		flags { "NoBufferSecurityCheck" }  
		filter "toolset:gcc or clang"
			buildoptions { "-O3", "-march=native" }  -- GCC/Clang specific flags
		filter "toolset:msc*"  -- Visual Studio specific flags
			buildoptions { "/O2", "/arch:AVX2" }  -- Example: Use AVX2 instructions
	
	filter {}  

