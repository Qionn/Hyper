#include "versus_gamemode.h"
#include "options.h"

#include "commands/move_command.h"
#include "components/character_component.h"
#include "components/ingredient_component.h"
#include "components/player_component.h"
#include "components/map_component.h"
#include "components/hud_component.h"

#include <hyper/input/input.h>
#include <hyper/scene/components/collider_component.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/scene.h>

#include <random>

using namespace hyper;

namespace burger_time
{
	void VersusGamemode::Setup(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap)
	{
		SpawnPlayer1(scene, input, pMap);
		SpawnPlayer2(scene, input, pMap);
		CreateHUD(scene, pMap);
	}

	void VersusGamemode::SpawnPlayer1(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap)
	{
		m_pPlayer1 = scene.CreateActor();
		m_pPlayer1->SetPosition(GetRandomPosition(pMap));
		m_pPlayer1->AddComponent<SpriteComponent>("assets/sprites/pepper_test.png");
		m_pPlayer1->AddComponent<ColliderComponent>(20.0f, 20.0f, -10.0f);
		auto pCharacter = m_pPlayer1->AddComponent<CharacterComponent>(pMap, 75.0f, 48.0f);
		m_pPlayer1->AddComponent<PlayerComponent>();

		input.Bind(Options::keys.characterLeft, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(-1, 0)));
		input.Bind(Options::keys.characterRight, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(1, 0)));
		input.Bind(Options::keys.characterUp, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, -1)));
		input.Bind(Options::keys.characterDown, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, 1)));

		if (input.GetGamepadCount() > 1)
		{
			input.Bind(Options::buttons.characterLeft, ButtonState::eDown, 0, std::make_unique<MoveCommand>(pCharacter, glm::vec2(-1, 0)));
			input.Bind(Options::buttons.characterRight, ButtonState::eDown, 0, std::make_unique<MoveCommand>(pCharacter, glm::vec2(1, 0)));
			input.Bind(Options::buttons.characterUp, ButtonState::eDown, 0, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, -1)));
			input.Bind(Options::buttons.characterDown, ButtonState::eDown, 0, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, 1)));
		}
	}

	void VersusGamemode::SpawnPlayer2(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap)
	{
		m_pPlayer2 = scene.CreateActor();
		m_pPlayer2->SetPosition(GetRandomPosition(pMap));
		auto pEnemy = m_pPlayer2->AddComponent<EnemyComponent>(GetRandomEnemy(), true);
		m_pPlayer2->AddComponent<SpriteComponent>(pEnemy->GetSpritePath());
		auto pCharacter = m_pPlayer2->AddComponent<CharacterComponent>(pMap, 75.0f, 48.0f);
		m_pPlayer2->AddComponent<ColliderComponent>(20.0f, 30.0f);

		int gamepad = (input.GetGamepadCount() > 1) ? 1 : 0;

		input.Bind(Options::buttons.characterLeft, ButtonState::eDown, gamepad, std::make_unique<MoveCommand>(pCharacter, glm::vec2(-1, 0)));
		input.Bind(Options::buttons.characterRight, ButtonState::eDown, gamepad, std::make_unique<MoveCommand>(pCharacter, glm::vec2(1, 0)));
		input.Bind(Options::buttons.characterUp, ButtonState::eDown, gamepad, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, -1)));
		input.Bind(Options::buttons.characterDown, ButtonState::eDown, gamepad, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, 1)));
	}

	void VersusGamemode::CreateHUD(hyper::Scene& scene, const MapComponent* pMap)
	{
		const auto& ingredients = pMap->GetIngredients();
		const auto& catchers = pMap->GetCatchers();

		Actor* pActor = scene.CreateActor();
		auto pHud = pActor->AddComponent<HUDComponent>(4, static_cast<int>(catchers.size()));

		for (Actor* pIngredientActor : ingredients)
		{
			auto pIngredient = pIngredientActor->GetComponent<IngredientComponent>();
			pIngredient->AddObserver(pHud);
		}

		auto pPlayer = m_pPlayer1->GetComponent<PlayerComponent>();
		pPlayer->AddObserver(pHud);
	}

	EnemyComponent::Type VersusGamemode::GetRandomEnemy()
	{
		std::random_device rd;
		std::default_random_engine re(rd());
		std::uniform_int_distribution<int> dist(0, 2);

		return static_cast<EnemyComponent::Type>(dist(re));
	}

	glm::vec2 VersusGamemode::GetRandomPosition(const MapComponent* pMap)
	{
		const std::vector<MapComponent::Platform>& platforms = pMap->GetPlatforms();

		std::random_device rd;
		std::default_random_engine re(rd());
		std::uniform_int_distribution<size_t> dist(0, platforms.size() - 1);

		size_t idx = dist(re);
		const MapComponent::Platform& platform = platforms[idx];

		std::uniform_real_distribution<float> dist2(platform.minX + 1.0f, platform.maxX - 1.0f);
		return glm::vec2(dist2(re), platform.height - 40.0f);
	}
}
