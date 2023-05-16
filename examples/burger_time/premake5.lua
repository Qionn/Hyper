project "BurgerTime"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
	
	files {
		"source/**.cpp",
		"source/**.h"
	}
	
	includedirs {
		"source",
		"%{wks.location}/hyper/include",
		VendorIncludes["glm"]
	}
	
	postbuildcommands {
		"{COPYDIR} assets/ %{cfg.buildtarget.directory}/assets/"
	}
	
	links { "Hyper" }
