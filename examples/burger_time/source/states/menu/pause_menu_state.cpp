#include "constants.h"
#include "pause_menu_state.h"

#include "components/menu_fsm_component.h"
#include "scenes/main_menu_scene.h"

#include <hyper/input/input.h>
#include <hyper/scene/components/rect_component.h>
#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>
#include <hyper/service/service_hub.h>

using namespace hyper;

namespace burger_time
{
	PauseMenuState::PauseMenuState(MenuFSMComponent* pMenuFSM, hyper::Input& input)
		: AMenuState(pMenuFSM, 32, 50)
	{
		SetupBackground();

		AddItem("Resume", std::bind(&PauseMenuState::OnResumeSelect, this, std::ref(input)));
		AddItem("Toggle Mute", std::bind(&PauseMenuState::OnMuteSelect, this));
		AddItem("Skip Level", std::bind(&PauseMenuState::OnSkipLevelSelect, this));
		AddItem("Menu", std::bind(&PauseMenuState::OnMenuSelect, this));
	}

	void PauseMenuState::OnEnter()
	{
		AMenuState::OnEnter();
		GetMenuFSM()->GetScene().SetTimeScale(0.0f);
	}

	void PauseMenuState::OnExit()
	{
		AMenuState::OnExit();
		GetMenuFSM()->GetScene().SetTimeScale(1.0f);
	}

	void PauseMenuState::OnResumeSelect(hyper::Input& input)
	{
		GetMenuFSM()->PopMenuState();
		input.PopLayer();
	}

	void PauseMenuState::OnMuteSelect()
	{
		ISoundService* pSound = ServiceHub::SoundService();

		if (pSound->IsMuted())
		{
			pSound->Unmute();
		}
		else
		{
			pSound->Mute();
		}
	}

	void PauseMenuState::OnSkipLevelSelect()
	{

	}

	void PauseMenuState::OnMenuSelect()
	{
		Scene& scene = GetMenuFSM()->GetScene();
		scene.RequestLoad(&LoadMainMenuScene);
	}

	void PauseMenuState::SetupBackground()
	{
		// Background
		Actor* pActor1 = GetRootActor()->CreateChild();
		pActor1->AddComponent<RectComponent>(800.0f, 800.0f, glm::vec4(0, 0, 0, 0.8f));

		// White border
		Actor* pActor2 = pActor1->CreateChild();
		pActor2->SetPosition(0.0f, 25.0f);
		pActor2->AddComponent<RectComponent>(510.0f, 335.0f, glm::vec4(1, 1, 1, 1));

		// Black card
		Actor* pActor3 = pActor2->CreateChild();
		pActor3->AddComponent<RectComponent>(500.0f, 325.0f, glm::vec4(0, 0, 0, 1));

		// Title
		Actor* pActor4 = pActor1->CreateChild();
		pActor4->SetPosition(0.0f, -80.0f);
		auto pText = pActor4->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 56);
		pText->SetText("Paused");
		pText->SetColor({ 1, 0, 0 });
	}
}
