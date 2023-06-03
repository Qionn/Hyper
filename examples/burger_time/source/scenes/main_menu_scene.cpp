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

		{
			auto pCommand = std::make_unique<ChangeMenuCommand>(*pMenuStack, pMenuStack->GetOptionsMenuState());
			input.Bind(Key::eO, KeyState::ePressed, std::move(pCommand));
		}
		{
			auto pCommand = std::make_unique<ChangeMenuCommand>(*pMenuStack, pMenuStack->GetPlayMenuState());
			input.Bind(Key::eP, KeyState::ePressed, std::move(pCommand));
		}
		{
			auto pCommand = std::make_unique<ChangeMenuCommand>(*pMenuStack, nullptr);
			input.Bind(Key::eBackspace, KeyState::ePressed, std::move(pCommand));
		}
	}
}
