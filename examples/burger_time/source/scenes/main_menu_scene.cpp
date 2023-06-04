#include "scenes/main_menu_scene.h"

#include <hyper/input/input.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	void LoadMainMenuScene(Scene& scene, Input& input)
	{
		Actor* pActor = scene.CreateActor();
		auto pMenuStack = pActor->AddComponent<MenuStackComponent>();

		input.Bind(Key::eUp, KeyState::ePressed, std::make_unique<MenuActionCommand>(pMenuStack, IMenuState::Action::eUp));
		input.Bind(Key::eDown, KeyState::ePressed, std::make_unique<MenuActionCommand>(pMenuStack, IMenuState::Action::eDown));
	}
}
