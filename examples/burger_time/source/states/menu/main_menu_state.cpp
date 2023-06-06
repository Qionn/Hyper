#include "constants.h"
#include "main_menu_state.h"

#include "components/menu_fsm_component.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	MainMenuState::MainMenuState(Scene& scene, MenuFSMComponent* pMenuFSM)
		: m_pMenuFSM{ pMenuFSM }
	{
		m_pRootActor = scene.CreateActor();
		m_pRootActor->SetEnabled(false);

		m_pHighscoresState	= std::make_unique<HighscoresMenuState>(scene);
		m_pOptionsState		= std::make_unique<OptionsMenuState>(scene);
		m_pPlayState		= std::make_unique<PlayMenuState>(scene, pMenuFSM);

		SetupTitleActors();
		SetupMenuItems();
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
				m_pMenuItemList->MoveCursor(1);
				break;
			}

			case Action::eDown:
			{
				m_pMenuItemList->MoveCursor(-1);
				break;
			}

			case Action::eSelect:
			{
				m_pMenuItemList->Select();
				break;
			}
		}
	}

	void MainMenuState::SetupTitleActors()
	{
		Actor* pActor1 = m_pRootActor->CreateChild();
		pActor1->SetPosition(400.0f, 80.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
		pText1->SetText("Burger Time");
		pText1->SetColor({ 1, 0, 0 });

		Actor* pActor2 = pActor1->CreateChild();
		pActor2->SetPosition(0.0f, 40.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
		pText2->SetText("A recration of Burger Time 1982");
		pText2->SetColor({ 1, 1, 1 });

		Actor* pActor3 = pActor2->CreateChild();
		pActor3->SetPosition(0.0f, 30.0f);
		auto pText3 = pActor3->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
		pText3->SetText("Using the Hyper engine");
		pText3->SetColor({ 1, 1, 1 });
	}

	void MainMenuState::SetupMenuItems()
	{
		Actor* pActor = m_pRootActor->CreateChild();
		pActor->SetPosition(400.0f, 350.0f);

		m_pMenuItemList = std::make_unique<MenuItemList>(pActor, 36, 80.0f);
		m_pMenuItemList->AddItem("Play", std::bind(&MainMenuState::OnPlaySelect, this));
		m_pMenuItemList->AddItem("Highscores", std::bind(&MainMenuState::OnHighscoresSelect, this));
		m_pMenuItemList->AddItem("Options", std::bind(&MainMenuState::OnOptionsSelect, this));
		m_pMenuItemList->AddItem("Exit", std::bind(&MainMenuState::OnExitSelect, this));
	}

	void MainMenuState::OnPlaySelect()
	{
		m_pMenuFSM->PushMenuState(m_pPlayState.get());
	}

	void MainMenuState::OnHighscoresSelect()
	{
		m_pMenuFSM->PushMenuState(m_pHighscoresState.get());
	}

	void MainMenuState::OnOptionsSelect()
	{
		m_pMenuFSM->PushMenuState(m_pOptionsState.get());
	}

	void MainMenuState::OnExitSelect()
	{

	}
}
