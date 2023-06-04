#include "constants.h"
#include "options_menu_state.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	OptionsMenuState::OptionsMenuState(Scene& scene)
	{
		m_pRootActor = scene.CreateActor();
		m_pRootActor->SetEnabled(false);

		SetupTitleActors(scene);
	}

	void OptionsMenuState::OnEnter()
	{
		m_pRootActor->SetEnabled(true);
	}

	void OptionsMenuState::OnExit()
	{
		m_pRootActor->SetEnabled(false);
	}

	void OptionsMenuState::PerformAction(Action)
	{

	}

	void OptionsMenuState::SetupTitleActors(Scene& scene)
	{
		Actor* pActor1 = scene.CreateActor();
		pActor1->SetParent(m_pRootActor, false);
		pActor1->SetPosition(400.0f, 80.0f);
		auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
		pText1->SetText("Options");
		pText1->SetColor({ 1, 0, 0 });
	}
}
