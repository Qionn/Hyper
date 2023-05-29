project "imgui"
    kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"
    
	files {
		"*.h",
		"*.cpp",
		"backends/imgui_impl_sdl2.h",
		"backends/imgui_impl_sdl2.cpp",
		"backends/imgui_impl_sdlrenderer.h",
		"backends/imgui_impl_sdlrenderer.cpp"
	}
	
	includedirs {
		VendorIncludes["imgui"],
		VendorIncludes["sdl2"]
	}
