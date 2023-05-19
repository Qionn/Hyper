#ifndef __HYPER_ASSERT_H__
#define __HYPER_ASSERT_H__

#include <string_view>

#include "hyper/utils/logging.h"

#if _DEBUG
#	ifdef _MSC_VER
#		define HyperDebugBreak() __debugbreak()
#	else
#		include <csignal>
#		ifdef SIGTRAP
#			define HyperDebugBreak() std::raise(SIGTRAP)
#		else
#			define HyperDebugBreak() std::raise(SIGABRT)
#		endif
#	endif

#define HyperAssert(cond, msg)														\
	while (!(cond)) {																\
		constexpr std::string_view file = __FILE__;									\
		constexpr size_t lastSlash = file.find_last_of("/\\");						\
		constexpr std::string_view fileName = file.substr(lastSlash + 1);			\
		LogError("Assertion failed: \"{}\" ({}:{})", msg, fileName, __LINE__);		\
		HyperDebugBreak();															\
	}
#else
#	define HyperAssert(cond, msg)
#	define HyperDebugBreak()
#endif

#endif // !__HYPER_ASSERT_H__
