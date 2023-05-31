#include "scenes/test_scene.h"

#include <hyper/core/application.h>

#if _DEBUG
#	if __has_include(<vld.h>)
#		include <vld.h>
#	endif
#endif

#include <memory>

using namespace hyper;
using namespace burger_time;

int main()
{
	Application::Info appInfo{
		.name			= "Burger Time",
		.windowWidth	= 800,
		.windowHeight	= 800,
		.loadScene		= &LoadTestScene
	};

	auto pApp = std::make_unique<Application>(appInfo);
	pApp->Start();
}
