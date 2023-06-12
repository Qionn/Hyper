#include "constants.h"
#include "options.h"
#include "end_scene.h"

#include "commands/menu_command.h"
#include "components/menu_fsm_component.h"
#include "states/menu/end_menu_state.h"

#include <hyper/input/input.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

#include <format>
#include <fstream>
#include <filesystem>

using namespace hyper;

namespace burger_time
{
	void LoadEndScene(Scene& scene, Input& input, int score, bool playerDied)
	{
		int highScore = GetLocalHighScore();
		if (!playerDied && score > highScore)
		{
			SaveLocalHighScore(score);
		}

		{ // title
			Actor* pActor = scene.CreateActor();
			pActor->SetPosition(400.0f, 100.0f);
			auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 64);
			pText->SetColor({ 1, 0, 0 });
			pText->SetText(playerDied ? "You died" : "You won");
		}

		{ // score
			Actor* pActor1 = scene.CreateActor();
			pActor1->SetPosition(400.0f, 200.0f);
			auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 42);
			pText1->SetColor({ 1, 1, 1 });
			pText1->SetText("Your score");

			Actor* pActor2 = pActor1->CreateChild();
			pActor2->SetPosition(0.0f, 50.0f);
			auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 42);
			pText2->SetColor({ 1, 1, 1 });
			pText2->SetText(std::format("{:06}", score));
		}

		{ // high score
			Actor* pActor1 = scene.CreateActor();
			pActor1->SetPosition(400.0f, 350.0f);
			auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 42);
			pText1->SetColor({ 1, 1, 1 });
			pText1->SetText("Highscore");

			Actor* pActor2 = pActor1->CreateChild();
			pActor2->SetPosition(0.0f, 50.0f);
			auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 42);
			pText2->SetColor({ 1, 1, 1 });
			pText2->SetText(std::format("{:06}", highScore));
		}

		Actor* pMenuFSMActor = scene.CreateActor();
		pMenuFSMActor->SetPosition(400.0f, 500.0f);
		auto pMenuFSM = pMenuFSMActor->AddComponent<MenuFSMComponent>(1);

		auto pEndMenuState = pMenuFSM->CreateState<EndMenuState>();
		pMenuFSM->PushMenuState(pEndMenuState);

		input.Bind(Options::keys.menuUp, KeyState::ePressed, std::make_unique<MenuCommand>(pMenuFSM, MenuCommand::Action::eCursorUp));
		input.Bind(Options::keys.menuDown, KeyState::ePressed, std::make_unique<MenuCommand>(pMenuFSM, MenuCommand::Action::eCursorDown));
		input.Bind(Options::keys.menuSelect, KeyState::ePressed, std::make_unique<MenuCommand>(pMenuFSM, MenuCommand::Action::eSelect));

		input.Bind(Options::buttons.menuUp, ButtonState::ePressed, 0, std::make_unique<MenuCommand>(pMenuFSM, MenuCommand::Action::eCursorUp));
		input.Bind(Options::buttons.menuDown, ButtonState::ePressed, 0, std::make_unique<MenuCommand>(pMenuFSM, MenuCommand::Action::eCursorDown));
		input.Bind(Options::buttons.menuSelect, ButtonState::ePressed, 0, std::make_unique<MenuCommand>(pMenuFSM, MenuCommand::Action::eSelect));
	}

	void SaveLocalHighScore(int score)
	{
		if (!std::filesystem::exists("assets/local/"))
		{
			std::filesystem::create_directories("assets/local/");
		}

		std::ofstream file("assets/local/highscore", std::ios::binary | std::ios::out);
		if (file.is_open())
		{
			file.write(reinterpret_cast<const char*>(&score), sizeof(int));
		}
	}

	int GetLocalHighScore()
	{
		std::ifstream file("assets/local/highscore", std::ios::binary);
		if (!file.is_open())
		{
			return 0;
		}

		int score = 0;
		file.read(reinterpret_cast<char*>(&score), sizeof(int));

		return score;
	}
}
