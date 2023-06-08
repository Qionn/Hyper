#include "constants.h"
#include "main_menu_scene.h"

#include "commands/menu_command.h"
#include "components/menu_fsm_component.h"
#include "states/menu/main_menu_state.h"

#include <hyper/input/input.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	void LoadMainMenuScene(Scene& scene, Input& input)
	{
		Actor* pLogoActor = scene.CreateActor();
		pLogoActor->SetPosition(400.0f, 120.0f);
		pLogoActor->AddComponent<SpriteComponent>("assets/sprites/logo.png");

		Actor* pLogoDeActor = pLogoActor->CreateChild();
		pLogoDeActor->SetPosition(-150.0f, 100.0f);
		pLogoDeActor->AddComponent<SpriteComponent>("assets/sprites/logo_de.png");

		Actor* pDeActor = pLogoDeActor->CreateChild();
		pDeActor->SetPosition(200.0f, 0.0f);
		auto pText3 = pDeActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 34);
		pText3->SetText("Data East©");
		pText3->SetColor({ 1, 1, 1 });

		Actor* pMenuFSMActor = scene.CreateActor();
		pMenuFSMActor->SetPosition(400.0f, 400.0f);
		auto pMenuStack = pMenuFSMActor->AddComponent<MenuFSMComponent>(1);

		auto pDefaultState = pMenuStack->CreateState<MainMenuState>();
		pMenuStack->PushMenuState(pDefaultState);

		input.Bind(Key::eUp, KeyState::ePressed, std::make_unique<MenuCommand>(pMenuStack, MenuCommand::Action::eCursorUp));
		input.Bind(Key::eDown, KeyState::ePressed, std::make_unique<MenuCommand>(pMenuStack, MenuCommand::Action::eCursorDown));
		input.Bind(Key::eEnter, KeyState::ePressed, std::make_unique<MenuCommand>(pMenuStack, MenuCommand::Action::eSelect));
		input.Bind(Key::eEscape, KeyState::ePressed, std::make_unique<MenuCommand>(pMenuStack, MenuCommand::Action::eReturn));
	}
}
