#include "scenes/main_menu_scene.h"
#include "constants.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	void LoadMainMenuScene(hyper::Scene& scene)
	{
		{ // Title
			Actor* pActor = scene.CreateAndAddActor();
			pActor->SetPosition(400.0f, 80.0f);
			auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
			pText->SetText("Burger Time");
			pText->SetColor({ 1, 0, 0 });
		}

		{
			Actor* pActor = scene.CreateAndAddActor();
			pActor->SetPosition(400.0f, 120.0f);
			auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
			pText->SetText("A recration of Burger Time 1982");
			pText->SetColor({ 1, 1, 1 });
		}

		{
			Actor* pActor = scene.CreateAndAddActor();
			pActor->SetPosition(400.0f, 150.0f);
			auto pText = pActor->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
			pText->SetText("Using the Hyper engine");
			pText->SetColor({ 1, 1, 1 });
		}
	}
}
