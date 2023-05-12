workspace "Hyper"
	startproject "BurgerTime"
	
    configurations { "Debug", "Release" }
    platforms { "x86", "x64" }
	
	warnings "Extra"
	
	flags { "FatalCompileWarnings" }

	targetdir "%{wks.location}/build/bin/%{cfg.buildcfg}-%{cfg.platform}/"
	objdir "%{wks.location}/build/int/%{prj.name}/%{cfg.buildcfg}-%{cfg.platform}/"

	debugdir "%{cfg.targetdir}"
	
    filter "configurations:Debug"
		runtime "Debug"
        optimize "Off"
		symbols "On"
		
    filter "configurations:Release"
        runtime "Release"
		optimize "Speed"
		symbols "Off"

	filter "system:windows"
		systemversion "latest"
		characterset "unicode"

	filter {}

include "options"
include "third_party"
include "hyper"
include "examples"
