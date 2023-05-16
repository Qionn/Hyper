group "ThirdParty"
	include "glm"
group ""

VendorIncludes = {}
VendorIncludes["glm"] = "%{wks.location}/third_party/glm"
VendorIncludes["sdl2"] = "%{wks.location}/third_party/sdl2/include"

VendorLibraries = {}
VendorLibraries["sdl2"] = "%{wks.location}/third_party/sdl2/lib/%{cfg.platform}"
