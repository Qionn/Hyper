#include <hyper/core/application.h>
#include <hyper/scene/scene_factory.h>

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <memory>

using namespace hyper;

namespace burger_time
{
	std::unique_ptr<Scene> LoadTestScene()
	{
		SceneFactory factory;

		factory.AddActor([](Actor&) {

		});

		return factory.CreateScene();
	}
}

int main()
{
	Application::Info appInfo{
		.name			= "Burger Time",
		.windowWidth	= 800,
		.windowHeight	= 600,
		.loadScene		= &burger_time::LoadTestScene
	};

	auto pApp = std::make_unique<Application>(appInfo);
	pApp->Start();
}
