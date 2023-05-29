#include "scenes/test_scene.h"

#include <hyper/graphics/context.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	SceneFactory LoadTestSceneFactory()
	{
		SceneFactory factory;

		factory.AddActor([](Scene& scene, Actor& actor) {
			IContext& context = scene.GetContext();
			actor.AddComponent<SpriteComponent>(context.CreateTexture("assets/sprites/level_01.png"));
			actor.SetPosition(400, 400);
		});

		factory.AddActor([](Scene& scene, Actor& actor) {
			IContext& context = scene.GetContext();
			actor.AddComponent<SpriteComponent>(context.CreateTexture("assets/sprites/player_idle.png"));
			actor.SetPosition(300, 50);
		});

		return factory;
	}
}
