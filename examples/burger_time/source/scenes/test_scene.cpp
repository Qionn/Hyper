#include "scenes/test_scene.h"

#include <hyper/scene/components/sprite_component.h>

using namespace hyper;

namespace burger_time
{
	hyper::SceneFactory LoadTestScene()
	{
		SceneFactory factory;

		factory.AddActor([](Actor& actor) {
			auto pSprite = actor.AddComponent<SpriteComponent>("assets/test_image.jpg");
			pSprite->SetSize(100, 100);
			actor.SetPosition(100, 100);
		});

		return factory;
	}
}
