#include "constants.h"
#include "main_menu_state.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>
#include <hyper/service/service_hub.h>


using namespace hyper;

namespace burger_time
{
	MainMenuState::MainMenuState(Scene& scene)
	{
		ISoundService* pSoundService = ServiceHub::SoundService();
		m_NavigateSoundId = pSoundService->AddSound("assets/audio/menu_navigate_01.wav");

		m_pRootActor = scene.CreateActor();
		m_pRootActor->SetEnabled(false);

		SetupTitleActors(scene);
		SetupItemActors(scene);
		SetupItemMarkers(scene);
	}

	void MainMenuState::OnEnter()
	{
		m_pRootActor->SetEnabled(true);
	}

	void MainMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
	}

	void MainMenuState::PerformAction(Action action)
	{
		switch (action)
		{
			case Action::eUp:
			{
				uint32_t newItem = (m_CurrentItem - 1) % m_Items.size();
				SelectItem(newItem);
				break;
			}

			case Action::eDown:
			{
				uint32_t newItem = (m_CurrentItem + 1) % m_Items.size();
				SelectItem(newItem);
				break;
			}
		}
	}

	void MainMenuState::SetupTitleActors(Scene& scene)
	{
		Actor* pActor1 = scene.CreateActor();
		pActor1->SetParent(m_pRootActor, false);
		pActor1->SetPosition(400.0f, 80.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
		pText1->SetText("Burger Time");
		pText1->SetColor({ 1, 0, 0 });

		Actor* pActor2 = scene.CreateActor();
		pActor2->SetParent(pActor1, false);
		pActor2->SetPosition(0.0f, 40.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
		pText2->SetText("A recration of Burger Time 1982");
		pText2->SetColor({ 1, 1, 1 });

		Actor* pActor3 = scene.CreateActor();
		pActor3->SetParent(pActor2, false);
		pActor3->SetPosition(0.0f, 30.0f);
		auto pText3 = pActor3->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
		pText3->SetText("Using the Hyper engine");
		pText3->SetColor({ 1, 1, 1 });
	}

	void MainMenuState::SetupItemActors(hyper::Scene& scene)
	{
		Actor* pActor1 = scene.CreateActor();
		pActor1->SetParent(m_pRootActor, false);
		pActor1->SetPosition(400.0f, 350.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
		pText1->SetText("Play");
		pText1->SetColor({ 1, 1, 1 });
		m_Items.push_back(pActor1);

		Actor* pActor2 = scene.CreateActor();
		pActor2->SetParent(pActor1, false);
		pActor2->SetPosition(0.0f, 80.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
		pText2->SetText("Highscores");
		pText2->SetColor({ 1, 1, 1 });
		m_Items.push_back(pActor2);

		Actor* pActor3 = scene.CreateActor();
		pActor3->SetParent(pActor2, false);
		pActor3->SetPosition(0.0f, 80.0f);
		auto pText3 = pActor3->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
		pText3->SetText("Options");
		pText3->SetColor({ 1, 1, 1 });
		m_Items.push_back(pActor3);

		Actor* pActor4 = scene.CreateActor();
		pActor4->SetParent(pActor3, false);
		pActor4->SetPosition(0.0f, 80.0f);
		auto pText4 = pActor4->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
		pText4->SetText("Exit");
		pText4->SetColor({ 1, 1, 1 });
		m_Items.push_back(pActor4);
	}

	void MainMenuState::SetupItemMarkers(hyper::Scene& scene)
	{
		m_pItemMarkerLeft = scene.CreateActor();
		m_pItemMarkerLeft->SetParent(m_Items[m_CurrentItem], false);
		m_pItemMarkerLeft->SetPosition(-200.0f, 0.0f);
		auto pItemMarkerTextLeft = m_pItemMarkerLeft->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
		pItemMarkerTextLeft->SetText(">");
		pItemMarkerTextLeft->SetColor({ 1, 1, 1 });

		m_pItemMarkerRight = scene.CreateActor();
		m_pItemMarkerRight->SetParent(m_Items[m_CurrentItem], false);
		m_pItemMarkerRight->SetPosition(200.0f, 0.0f);
		auto pItemMarkerTextRight = m_pItemMarkerRight->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 36);
		pItemMarkerTextRight->SetText("<");
		pItemMarkerTextRight->SetColor({ 1, 1, 1 });
	}

	void MainMenuState::SelectItem(uint32_t item)
	{
		ISoundService* pSoundService = ServiceHub::SoundService();
		pSoundService->Play(m_NavigateSoundId, 0.5f);

		Actor* pItem = m_Items[item];
		m_pItemMarkerLeft->SetParent(pItem, false);
		m_pItemMarkerRight->SetParent(pItem, false);
		m_CurrentItem = item;
	}
}
