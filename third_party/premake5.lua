group "ThirdParty"
	include "glm"
group ""

VendorIncludes = {}
VendorIncludes["glm"] = "%{wks.location}/third_party/glm"

VendorLibraries = {}

if (_OPTIONS["renderer"] == "vulkan") then
	local vulkanSDKPath = os.getenv("VULKAN_SDK")
	
	if (vulkanSDKPath == nil) then
		print("No Vulkan SDK was found")
		os.exit(1)
	end
	
	VendorIncludes["renderer"] = (vulkanSDKPath .. "/Include")
	VendorLibraries["renderer"] = (vulkanSDKPath .. "/Lib%{cfg.platform:gsub('x86', '32'):gsub('x64', '')}")
end
