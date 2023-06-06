#include "constants.h"
#include "highscores_menu_state.h"

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

		m_pPlayers = m_pRootActor->CreateChild();
		m_pPlayers->SetPosition(400.0f, 300.0f);

		SetupTitleActors();
	}

	void HighscoresMenuState::OnEnter()
	{
		SetupHighScoreActors();
		m_pRootActor->SetEnabled(true);
	}

	void HighscoresMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
	}

	void HighscoresMenuState::PerformAction(Action)
	{

	}

	void HighscoresMenuState::SetupTitleActors()
	{
		Actor* pActor1 = m_pRootActor->CreateChild();
		pActor1->SetPosition(400.0f, 80.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
		pText1->SetText("Highscores");
		pText1->SetColor({ 1, 0, 0 });

		Actor* pActor2 = pActor1->CreateChild();
		pActor2->SetPosition(0.0f, 40.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
		pText2->SetText("The top 5 players");
		pText2->SetColor({ 1, 1, 1 });
	}

	void HighscoresMenuState::SetupHighScoreActors()
	{
		m_pPlayers->ForEachChild([](Actor& child) { child.Destroy(); });

		std::array<Player, 5> players = GetTopPlayers();

		float ypos = 0.0f;
		for (size_t i = 0; i < players.size() && i < 5; ++i)
		{
			std::stringstream ss;
			ss << players[i].name << ' ' << players[i].score;

			Actor* pActor = m_pPlayers->CreateChild();
			pActor->SetPosition(0.0f, ypos);
			auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 30);
			pText->SetText(ss.str());

			switch (i)
			{
				case 0:
					pText->SetColor({ 1.0f, 0.85f, 0.0f });
					break;

				case 1:
					pText->SetColor({ 0.75f, 0.75f, 0.75f });
					break;

				case 2:
					pText->SetColor({ 0.8f, 0.5f, 0.2f });
					break;

				default:
					pText->SetColor({ 0.3f, 0.3f, 0.3f });
					break;
			}

			ypos += 80.0f;
		}
	}

	/* static */ std::array<HighscoresMenuState::Player, 5> HighscoresMenuState::GetTopPlayers()
	{
		std::array<Player, 5> topPlayers;
		topPlayers.fill({ "None", 0 });

		std::ifstream file("assets/local/highscores.txt");
		if (!file.is_open())
		{
			return topPlayers;
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

			Player player = {
				.name = line.substr(0, idx),
				.score = std::stoul(line.substr(idx + 1))
			};

			players.push_back(std::move(player));
		}

		file.close();

		std::sort(players.begin(), players.end(), [](const Player& p1, const Player& p2) {
			return p1.score > p2.score;
		});
		
		for (size_t i = 0; i < topPlayers.size() && i < players.size(); ++i)
		{
			topPlayers[i] = std::move(players[i]);
		}

		return topPlayers;
	}
}
