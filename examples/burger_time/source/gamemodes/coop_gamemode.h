#ifndef __BURGER_TIME_COOP_GAMEMODE_H__
#define __BURGER_TIME_COOP_GAMEMODE_H__

#include <glm/vec2.hpp>

#include "gamemodes/gamemode.h"

namespace burger_time
{
	class CoopGamemode final : public IGamemode
	{
	public:
		CoopGamemode() = default;

		void Setup(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap) override;

		CoopGamemode(const CoopGamemode&) = delete;
		CoopGamemode(CoopGamemode&&) = delete;
		CoopGamemode& operator=(const CoopGamemode&) = delete;
		CoopGamemode& operator=(CoopGamemode&&) = delete;

		~CoopGamemode() = default;

	private:
		void SpawnPlayer1(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap);
		void SpawnPlayer2(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap);
		void SpawnEnemies(hyper::Scene& scene, const MapComponent* pMap, hyper::Actor* pTarget);
		void CreateHUD(hyper::Scene& scene, const MapComponent* pMap);

		static glm::vec2 GetRandomPosition(const MapComponent* pMap);

	private:
		hyper::Actor* m_pPlayer1 = nullptr;
		hyper::Actor* m_pPlayer2 = nullptr;
	};
}

#endif // !__BURGER_TIME_COOP_GAMEMODE_H__
