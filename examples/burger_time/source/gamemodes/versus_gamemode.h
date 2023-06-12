#ifndef __BURGER_TIME_VERSUS_GAMEMODE_H__
#define __BURGER_TIME_VERSUS_GAMEMODE_H__

#include <glm/vec2.hpp>

#include "components/enemy_component.h"
#include "gamemodes/gamemode.h"

namespace burger_time
{
	class VersusGamemode final : public IGamemode
	{
	public:
		VersusGamemode() = default;

		void Setup(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap) override;

		VersusGamemode(const VersusGamemode&)				= delete;
		VersusGamemode(VersusGamemode&&)					= delete;
		VersusGamemode& operator=(const VersusGamemode&)	= delete;
		VersusGamemode& operator=(VersusGamemode&&)			= delete;

		~VersusGamemode() = default;

	private:
		void SpawnPlayer1(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap);
		void SpawnPlayer2(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap);
		void CreateHUD(hyper::Scene& scene, const MapComponent* pMap);

		static EnemyComponent::Type GetRandomEnemy();
		static glm::vec2 GetRandomPosition(const MapComponent* pMap);

	private:
		hyper::Actor* m_pPlayer1 = nullptr;
		hyper::Actor* m_pPlayer2 = nullptr;
	};
}

#endif // !__BURGER_TIME_VERSUS_GAMEMODE_H__
