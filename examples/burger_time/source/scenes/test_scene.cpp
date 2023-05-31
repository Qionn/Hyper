#include "scenes/test_scene.h"

#include <hyper/graphics/context.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/components/text_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	void LoadTestScene(Scene& scene)
	{
		{
			Actor* pActor = scene.CreateAndAddActor();
			pActor->AddComponent<SpriteComponent>("assets/sprites/level_01.png");
			pActor->SetPosition(400, 400);
		}

		{
			Actor* pActor = scene.CreateAndAddActor();
			//pActor->AddComponent<SpriteComponent>("assets/sprites/player_idle.png");
			auto pTc = pActor->AddComponent<TextComponent>("assets/fonts/joystix_monospace.otf", 36);
			pTc->SetText("Words on the screen!", { 1, 1, 1 });
			pActor->SetPosition(100, 50);
		}
	}
}
