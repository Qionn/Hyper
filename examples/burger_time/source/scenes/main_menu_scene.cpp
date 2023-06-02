#include "scenes/main_menu_scene.h"
#include "constants.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	void LoadMainMenuScene(Scene& scene, Input&)
	{
		{ // Title
			auto pActor1 = std::make_shared<Actor>(scene);
			pActor1->SetPosition(400.0f, 80.0f);
			auto pText1 = pActor1->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 52);
			pText1->SetText("Burger Time");
			pText1->SetColor({ 1, 0, 0 });
			scene.AddActor(pActor1);

			auto pActor2 = std::make_shared<Actor>(scene);
			pActor2->SetParent(pActor1.get(), false);
			pActor2->SetPosition(0.0f, 40.0f);
			auto pText2 = pActor2->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
			pText2->SetText("A recration of Burger Time 1982");
			pText2->SetColor({ 1, 1, 1 });

			auto pActor3 = std::make_shared<Actor>(scene);
			pActor3->SetParent(pActor2.get(), false);
			pActor3->SetPosition(0.0f, 30.0f);
			auto pText3 = pActor3->AddComponent<TextComponent>(BURGER_TIME_FONT_PATH, 24);
			pText3->SetText("Using the Hyper engine");
			pText3->SetColor({ 1, 1, 1 });
		}
	}
}
