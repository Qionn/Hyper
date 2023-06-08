#include "level_scene.h"

#include "commands/pause_command.h"
#include "components/map_component.h"

#include <hyper/input/input.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	void LoadLevelScene(Scene& scene, Input& input, std::string_view mapFile)
	{
		Actor* pMapActor = scene.CreateActor();
		pMapActor->SetPosition(400.0f, 400.0f);
		pMapActor->AddComponent<MapComponent>(mapFile);

		Actor* pMenuFSMActor = scene.CreateActor();
		pMenuFSMActor->SetPosition(400.0f, 375.0f);
		auto pMenuStack = pMenuFSMActor->AddComponent<MenuFSMComponent>(0);

		input.Bind(Key::eEscape, KeyState::ePressed, std::make_unique<PauseCommand>(pMenuStack, input));
	}
}
