#include "level_scene.h"

#include "commands/pause_command.h"
#include "components/ai_component.h"
#include "components/character_component.h"
#include "components/map_component.h"

#include <hyper/input/input.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{

	class MoveCommand final : public hyper::ICommand
	{
	public:
		MoveCommand(CharacterComponent* pCharachter, const glm::vec2& direction)
			: m_pCharacter{ pCharachter }, m_Direction{ direction } {}

		void Execute() override
		{
			m_pCharacter->Move(m_Direction);
		}

	private:
		CharacterComponent* m_pCharacter;
		glm::vec2 m_Direction;
	};



	void LoadLevelScene(Scene& scene, Input& input, std::string_view mapFile)
	{
		Actor* pMapActor = scene.CreateActor();
		pMapActor->SetPosition(400.0f, 400.0f);
		auto pMap = pMapActor->AddComponent<MapComponent>(mapFile);

		{ // Test Charachter & AI
			Actor* pActor = scene.CreateActor();
			pActor->SetPosition(500.0f, 200.0f);
			pActor->AddComponent<SpriteComponent>("assets/sprites/pepper_test.png");
			auto pCharacter = pActor->AddComponent<CharacterComponent>(pMap, 100.0f);

			input.Bind(Key::eA, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(-1, 0)));
			input.Bind(Key::eD, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(1, 0)));
			input.Bind(Key::eW, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, -1)));
			input.Bind(Key::eS, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, 1)));

			Actor* pAI = scene.CreateActor();
			pAI->SetPosition(200.0f, 0.0f);
			pAI->AddComponent<SpriteComponent>("assets/sprites/hotdog_test.png");
			pAI->AddComponent<CharacterComponent>(pMap, 75.0f);
			pAI->AddComponent<AIComponent>(pActor);
		}

		Actor* pMenuFSMActor = scene.CreateActor();
		pMenuFSMActor->SetPosition(400.0f, 375.0f);
		auto pMenuStack = pMenuFSMActor->AddComponent<MenuFSMComponent>(0);

		input.Bind(Key::eEscape, KeyState::ePressed, std::make_unique<PauseCommand>(pMenuStack, input));
	}
}
