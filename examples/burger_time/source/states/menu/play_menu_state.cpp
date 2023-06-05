#include "constants.h"
#include "play_menu_state.h"

#include "components/menu_fsm_component.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	PlayMenuState::PlayMenuState(hyper::Scene& scene, MenuFSMComponent* pMenuFSM)
		: m_pMenuFSM{ pMenuFSM }
	{
		m_pRootActor = scene.CreateActor();
		m_pRootActor->SetEnabled(false);

		SetupTitleActors(scene);
		SetupMenuItems(scene);
	}

	void PlayMenuState::OnEnter()
	{
		m_pRootActor->SetEnabled(true);
	}

	void PlayMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
	}

	void PlayMenuState::PerformAction(Action action)
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

	void PlayMenuState::SetupTitleActors(Scene& scene)
	{
		Actor* pActor1 = scene.CreateActor();
		pActor1->SetParent(m_pRootActor, false);
		pActor1->SetPosition(400.0f, 80.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
		pText1->SetText("Play");
		pText1->SetColor({ 1, 0, 0 });

		Actor* pActor2 = scene.CreateActor();
		pActor2->SetParent(pActor1, false);
		pActor2->SetPosition(0.0f, 40.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
		pText2->SetText("Choose a gamemode to begin");
		pText2->SetColor({ 1, 1, 1 });
	}

	void PlayMenuState::SetupMenuItems(Scene& scene)
	{
		Actor* pActor = scene.CreateActor();
		pActor->SetParent(m_pRootActor, false);
		pActor->SetPosition(400.0f, 350.0f);

		m_pMenuItemList = std::make_unique<MenuItemList>(pActor, 36, 80.0f);
		m_pMenuItemList->AddItem("Solo", std::bind(&PlayMenuState::OnSoloSelect, this));
		m_pMenuItemList->AddItem("Co-op", std::bind(&PlayMenuState::OnCoopSelect, this));
		m_pMenuItemList->AddItem("Versus", std::bind(&PlayMenuState::OnVersusSelect, this));
	}

	void PlayMenuState::OnSoloSelect()
	{

	}

	void PlayMenuState::OnCoopSelect()
	{

	}

	void PlayMenuState::OnVersusSelect()
	{

	}
}
