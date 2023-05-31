VendorIncludes = {}
VendorIncludes["glm"]			= "%{wks.location}/third_party/glm"
VendorIncludes["imgui"]			= "%{wks.location}/third_party/imgui"
VendorIncludes["sdl2"]			= "%{wks.location}/third_party/sdl2/include"
VendorIncludes["sdl2_mixer"]	= "%{wks.location}/third_party/sdl2_mixer/include"
VendorIncludes["sdl2_image"]	= "%{wks.location}/third_party/sdl2_image/include"
VendorIncludes["sdl2_ttf"]		= "%{wks.location}/third_party/sdl2_ttf/include"

VendorLibraries = {}
VendorLibraries["sdl2"]			= "%{wks.location}/third_party/sdl2/lib/%{cfg.platform}"
VendorLibraries["sdl2_mixer"]	= "%{wks.location}/third_party/sdl2_mixer/lib/%{cfg.platform}"
VendorLibraries["sdl2_image"]	= "%{wks.location}/third_party/sdl2_image/lib/%{cfg.platform}"
VendorLibraries["sdl2_ttf"]		= "%{wks.location}/third_party/sdl2_ttf/lib/%{cfg.platform}"

group "ThirdParty"
	include "glm"
	include "imgui"
group ""
