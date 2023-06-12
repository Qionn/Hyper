#include "level_scene.h"
#include "options.h"

#include "commands/pause_command.h"
#include "components/map_component.h"

#include <hyper/input/input.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	void LoadLevelScene(Scene& scene, Input& input, std::string_view mapFile, IGamemode* pGamemode)
	{
		Actor* pMapActor = scene.CreateActor();
		pMapActor->SetPosition(400.0f, 400.0f);
		auto pMap = pMapActor->AddComponent<MapComponent>(mapFile);

		pGamemode->Setup(scene, input, pMap);

		Actor* pMenuFSMActor = scene.CreateActor();
		pMenuFSMActor->SetPosition(400.0f, 375.0f);
		auto pMenuStack = pMenuFSMActor->AddComponent<MenuFSMComponent>(0);

		input.Bind(Options::keys.pause, KeyState::ePressed, std::make_unique<PauseCommand>(pMenuStack, input));
		input.Bind(Options::buttons.pause, ButtonState::ePressed, 0, std::make_unique<PauseCommand>(pMenuStack, input));
	}
}