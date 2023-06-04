#include "constants.h"
#include "play_menu_state.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	PlayMenuState::PlayMenuState(Scene& scene)
	{
		m_pRootActor = scene.CreateActor();
		m_pRootActor->SetEnabled(false);

		SetupTitleActors(scene);
	}

	void PlayMenuState::OnEnter()
	{
		m_pRootActor->SetEnabled(true);
	}

	void PlayMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
	}

	void PlayMenuState::PerformAction(Action)
	{

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
}
