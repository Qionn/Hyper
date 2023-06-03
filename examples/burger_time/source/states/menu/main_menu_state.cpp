#include "constants.h"
#include "main_menu_state.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	MainMenuState::MainMenuState(Scene& scene)
	{
		m_pRootActor = scene.CreateActor();
		m_pRootActor->SetEnabled(false);

		SetupTitleActors(scene);
	}

	void MainMenuState::OnEnter()
	{
		m_pRootActor->SetEnabled(true);
	}

	void MainMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
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
}
