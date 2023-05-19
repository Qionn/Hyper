#include <hyper/core/application.h>

#if _DEBUG
#	if __has_include(<vld.h>)
#		include <vld.h>
#	endif
#endif

#include <memory>

using namespace hyper;

int main()
{
	auto pApp = std::make_unique<Application>("Burger Time");
	pApp->Start();
}
