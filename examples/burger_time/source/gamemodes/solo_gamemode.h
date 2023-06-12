#ifndef __BURGER_TIME_SOLO_GAMEMODE_H__
#define __BURGER_TIME_SOLO_GAMEMODE_H__

#include <glm/vec2.hpp>

#include "gamemodes/gamemode.h"

namespace burger_time
{
	class SoloGamemode final : public IGamemode
	{
	public:
		SoloGamemode() = default;

		void Setup(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap) override;

		SoloGamemode(const SoloGamemode&)				= delete;
		SoloGamemode(SoloGamemode&&)					= delete;
		SoloGamemode& operator=(const SoloGamemode&)	= delete;
		SoloGamemode& operator=(SoloGamemode&&)			= delete;

		~SoloGamemode() = default;

	private:
		void SpawnPlayer(hyper::Scene& scene, hyper::Input& input, const MapComponent* pMap);
		void SpawnEnemies(hyper::Scene& scene, const MapComponent* pMap);
		void CreateHUD(hyper::Scene& scene, const MapComponent* pMap);

		static glm::vec2 GetRandomPosition(const MapComponent* pMap);

	private:
		hyper::Actor* m_pPlayer = nullptr;
	};
}

#endif //!__BURGER_TIME_SOLO_GAMEMODE_H__
