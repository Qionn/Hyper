#include "solo_gamemode.h"
#include "options.h"

#include "components/enemy_component.h"
#include "components/character_component.h"
#include "components/player_component.h"
#include "components/map_component.h"

#include <hyper/input/input.h>
#include <hyper/scene/components/collider_component.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/scene.h>

#include <random>

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

	void SoloGamemode::Setup(hyper::Scene& scene, Input& input, const MapComponent* pMap)
	{
		SpawnPlayer(scene, input, pMap);
		//SpawnEnemies(scene, pMap);
	}

	void SoloGamemode::SpawnPlayer(hyper::Scene& scene, Input& input, const MapComponent* pMap)
	{
		m_pPlayer = scene.CreateActor();
		m_pPlayer->SetPosition(GetRandomPosition(pMap));
		m_pPlayer->AddComponent<SpriteComponent>("assets/sprites/pepper_test.png");
		m_pPlayer->AddComponent<ColliderComponent>(30.0f, 48.0f);
		auto pCharacter = m_pPlayer->AddComponent<CharacterComponent>(pMap, 75.0f, 48.0f);
		m_pPlayer->AddComponent<PlayerComponent>();

		input.Bind(Options::keys.characterLeft, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(-1, 0)));
		input.Bind(Options::keys.characterRight, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(1, 0)));
		input.Bind(Options::keys.characterUp, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, -1)));
		input.Bind(Options::keys.characterDown, KeyState::eDown, std::make_unique<MoveCommand>(pCharacter, glm::vec2(0, 1)));
	}

	void SoloGamemode::SpawnEnemies(hyper::Scene& scene, const MapComponent* pMap)
	{
		EnemyComponent::Type enemies[] = {
			EnemyComponent::Type::eHotdog,
			EnemyComponent::Type::ePicke,
			EnemyComponent::Type::eEgg,
		};

		for (const auto& enemy : enemies)
		{
			Actor* pActor = scene.CreateActor();
			pActor->SetPosition(GetRandomPosition(pMap));
			auto pEnemy = pActor->AddComponent<EnemyComponent>(enemy);
			pActor->AddComponent<SpriteComponent>(pEnemy->GetSpritePath());
			pActor->AddComponent<CharacterComponent>(pMap, 50.0f, 48.0f);
			pEnemy->SetTargetActor(m_pPlayer);
		}
	}

	/* static */ glm::vec2 SoloGamemode::GetRandomPosition(const MapComponent* pMap)
	{
		const std::vector<MapComponent::Platform>& platforms = pMap->GetPlatforms();

		std::random_device rd;
		std::default_random_engine re(rd());
		std::uniform_int_distribution<size_t> dist(0, platforms.size() - 1);

		size_t idx = dist(re);
		const MapComponent::Platform& platform = platforms[idx];

		std::uniform_real_distribution<float> dist2(platform.minX + 1.0f, platform.maxX -1.0f);
		return glm::vec2(dist2(re), platform.height - 40.0f);
	}
}
