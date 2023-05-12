project "Hyper"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	pchheader "pch.h"
	pchsource "source/pch.cpp"

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
		VendorIncludes["renderer"]
	}
	
	libdirs {
		VendorLibraries["renderer"]
	}
	
	filter { "options:renderer=vulkan" }
		files {
			"source/backend/vulkan/**.cpp",
			"source/backend/vulkan/**.h"
		}
		
		links "vulkan-1"
		defines "HYPER_BACKEND_VULKAN"
		
	filter { "system:windows" }
		files {
			"source/backend/win32/**.cpp",
			"source/backend/win32/**.h"
		}

		defines "HYPER_BACKEND_WIN32"

	filter {}
