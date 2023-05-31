project "Hyper"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	files {
		"include/**.h",
		"include/**.inl",
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
		VendorIncludes["sdl2_mixer"],
		VendorIncludes["sdl2_image"],
		VendorIncludes["sdl2_ttf"]
	}
	
	libdirs {
		VendorLibraries["sdl2"],
		VendorLibraries["sdl2_mixer"],
		VendorLibraries["sdl2_image"],
		VendorLibraries["sdl2_ttf"]
	}
	
	links {
		"imgui",
		"SDL2",
		"SDL2_mixer",
		"SDL2_image",
		"SDL2_ttf"
	}
	
	files {
		"source/backend/sdl2/**.cpp",
		"source/backend/sdl2/**.h"
	}
	
	defines "HYPER_BACKEND_SDL2"
	
	filter { "system:windows" }
		files {
			"source/backend/win32/**.cpp",
			"source/backend/win32/**.h"
		}
	
		postbuildcommands {
			("{COPYFILE} " .. VendorLibraries["sdl2"] .. "/SDL2.dll %{cfg.buildtarget.directory}/SDL2.dll"),
			("{COPYFILE} " .. VendorLibraries["sdl2_mixer"] .. "/SDL2_mixer.dll %{cfg.buildtarget.directory}/SDL2_mixer.dll"),
			("{COPYFILE} " .. VendorLibraries["sdl2_image"] .. "/SDL2_image.dll %{cfg.buildtarget.directory}/SDL2_image.dll"),
			("{COPYFILE} " .. VendorLibraries["sdl2_ttf"] .. "/SDL2_ttf.dll %{cfg.buildtarget.directory}/SDL2_ttf.dll")
		}

		defines "HYPER_BACKEND_WIN32"
		
	filter { "action:vs*" }
		linkoptions { "/IGNORE:4006" }

	filter {}
