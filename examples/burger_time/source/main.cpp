#include <hyper/core/application.h>

#include <memory>

#if _DEBUG
#	if __has_include(<vld.h>)
#		include <vld.h>
#	endif
#endif

using namespace hyper;

int main()
{
	auto pApp = std::make_unique<Application>("Burger Time");

	pApp->Start();
}
