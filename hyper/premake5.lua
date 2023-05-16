project "Hyper"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	files {
		"include/**.h",
		"source/**.cpp",
		"source/**.h"
	}
	
	removefiles {
		"source/backend/**.cpp",
		"source/backend/**.h"
	}
	
	includedirs {
		"include",
		"source",
		VendorIncludes["glm"],
		VendorIncludes["sdl2"]
	}
	
	libdirs {
		VendorLibraries["sdl2"]
	}
	
	links {
		"SDL2"
	}
	
	files {
		"source/backend/sdl2/**.cpp",
		"source/backend/sdl2/**.h"
	}
	
	defines "HYPER_PLATFORM_SDL2"
	
	postbuildcommands {
		("{COPYFILE} " .. VendorLibraries["sdl2"] .. "/SDL2.dll %{cfg.buildtarget.directory}/SDL2.dll")
	}
	
	filter { "system:windows" }
		files {
			"source/backend/win32/**.cpp",
			"source/backend/win32/**.h"
		}

		defines "HYPER_BACKEND_WIN32"

	filter {}
