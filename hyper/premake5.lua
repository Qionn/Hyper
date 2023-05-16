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
		VendorIncludes["imgui"],
		VendorIncludes["sdl2"],
		VendorIncludes["sdl2_mixer"]
	}
	
	libdirs {
		VendorLibraries["sdl2"],
		VendorLibraries["sdl2_mixer"]
	}
	
	links {
		"ImGui",
		"SDL2",
		"SDL2_mixer"
	}
	
	files {
		"source/backend/sdl2/**.cpp",
		"source/backend/sdl2/**.h"
	}
	
	defines "HYPER_PLATFORM_SDL2"
	
	postbuildcommands {
		("{COPYFILE} " .. VendorLibraries["sdl2"] .. "/SDL2.dll %{cfg.buildtarget.directory}/SDL2.dll"),
		("{COPYFILE} " .. VendorLibraries["sdl2_mixer"] .. "/SDL2_mixer.dll %{cfg.buildtarget.directory}/SDL2_mixer.dll")
	}
	
	filter { "system:windows" }
		files {
			"source/backend/win32/**.cpp",
			"source/backend/win32/**.h"
		}

		defines "HYPER_BACKEND_WIN32"

	filter {}
