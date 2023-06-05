#include "constants.h"
#include "highscores_menu_state.h"

#include "components/rainbow_color_component.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>
#include <hyper/utils/logging.h>

#include <algorithm>
#include <fstream>
#include <sstream>

using namespace hyper;

namespace burger_time
{
	HighscoresMenuState::HighscoresMenuState(Scene& scene)
	{
		m_pRootActor = scene.CreateActor();
		m_pRootActor->SetEnabled(false);

		m_pPlayers = scene.CreateActor();
		m_pPlayers->SetParent(m_pRootActor, false);
		m_pPlayers->SetPosition(400.0f, 280.0f);

		SetupTitleActors(scene);
	}

	void HighscoresMenuState::OnEnter()
	{
		ParseHighScores();
		m_pRootActor->SetEnabled(true);
	}

	void HighscoresMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
	}

	void HighscoresMenuState::PerformAction(Action)
	{

	}

	void HighscoresMenuState::SetupTitleActors(Scene& scene)
	{
		Actor* pActor1 = scene.CreateActor();
		pActor1->SetParent(m_pRootActor, false);
		pActor1->SetPosition(400.0f, 80.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
		pText1->SetText("Highscores");
		pText1->SetColor({ 1, 0, 0 });

		Actor* pActor2 = scene.CreateActor();
		pActor2->SetParent(pActor1, false);
		pActor2->SetPosition(0.0f, 40.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
		pText2->SetText("The top 5 players");
		pText2->SetColor({ 1, 1, 1 });
	}

	void HighscoresMenuState::ParseHighScores()
	{
		std::ifstream file("assets/local/highscores.txt");
		if (!file.is_open())
		{
			LogWarn("Could not find highscores.txt");
			return;
		}

		std::vector<Player> players;

		std::string line;
		while (std::getline(file, line))
		{
			auto idx = line.find(':');
			if (idx == std::string::npos)
			{
				LogWarn("Invalid highscore line '{}'", line);
				continue;
			}

			std::string strScore = line.substr(idx + 1);

			Player player = {
				.name = line.substr(0, idx),
				.score = std::stoul(strScore.data())
			};
			
			players.push_back(std::move(player));
		}

		std::sort(players.begin(), players.end(), [](const Player& p1, const Player& p2) {
			return p1.score > p2.score;
		});

		m_pPlayers->ForEachChild([](Actor& child) {
			child.Destroy();
		});

		float ypos = 0.0f;

		for (size_t i = 0; i < players.size() && i < 5; ++i)
		{
			std::stringstream ss;
			ss << players[i].name << ' ' << players[i].score;

			Actor* pActor = m_pPlayers->CreateChild(false);
			pActor->SetPosition(0.0f, ypos);
			auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
			pText->SetText(ss.str());

			switch (i)
			{
				case 0:
					pActor->AddComponent<RainbowColorComponent>(800.0f);
					break;

				case 1:
					pText->SetColor({ 0.753f, 0.753f, 0.753f });
					break;

				case 2:
					pText->SetColor({ 0.800f, 0.498f, 0.196f });
					break;

				default:
					pText->SetColor({ 0.3f, 0.3f, 0.3f });
					break;
			}

			ypos += 90.0f;
		}
	}
}
