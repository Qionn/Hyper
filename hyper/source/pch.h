#ifndef __HYPER_PCH_HPP__
#define __HYPER_PCH_HPP__

#if defined(HYPER_PLATFORM_VULKAN)
#	define NOMINMAX
#	if defined(HYPER_PLATFORM_WINDOWS)
#		define VK_USE_PLATFORM_WIN32_KHR
#	endif
#	include <vulkan/vulkan.hpp>
#	ifdef hyper
#		undef hyper
#	endif
#endif

#endif // !__HYPER_PCH_HPP__
