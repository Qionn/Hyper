#include "constants.h"
#include "level_menu_state.h"

#include "components/menu_fsm_component.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	LevelMenuState::LevelMenuState(Scene& scene, MenuFSMComponent* pMenuFSM)
		: m_pMenuFSM{ pMenuFSM }
	{
		m_pRootActor = scene.CreateActor();
		m_pRootActor->SetEnabled(false);

		SetupTitleActors();
		SetupMenuItems();
	}

	void LevelMenuState::OnEnter()
	{
		m_pMenuItemList->SetCursor(0);
		m_pRootActor->SetEnabled(true);
	}

	void LevelMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
	}

	void LevelMenuState::PerformAction(Action action)
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

	void LevelMenuState::SetupTitleActors()
	{
		Actor* pActor1 = m_pRootActor->CreateChild();
		pActor1->SetPosition(400.0f, 80.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
		pText1->SetText("Select Level");
		pText1->SetColor({ 1, 0, 0 });

		Actor* pActor2 = pActor1->CreateChild();
		pActor2->SetPosition(0.0f, 40.0f);
		auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
		pText2->SetText("Choose a level to begin");
		pText2->SetColor({ 1, 1, 1 });
	}

	void LevelMenuState::SetupMenuItems()
	{
		Actor* pActor = m_pRootActor->CreateChild();
		pActor->SetPosition(400.0f, 350.0f);

		m_pMenuItemList = std::make_unique<MenuItemList>(pActor, 36, 80.0f);
		m_pMenuItemList->AddItem("Level 1", std::bind(&LevelMenuState::OnLevel1Select, this));
		m_pMenuItemList->AddItem("Level 2", std::bind(&LevelMenuState::OnLevel2Select, this));
		m_pMenuItemList->AddItem("Level 3", std::bind(&LevelMenuState::OnLevel3Select, this));
	}

	void LevelMenuState::OnLevel1Select()
	{

	}

	void LevelMenuState::OnLevel2Select()
	{

	}

	void LevelMenuState::OnLevel3Select()
	{

	}
}
