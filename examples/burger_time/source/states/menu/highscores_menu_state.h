#ifndef __BURGER_TIME_HIGHSCORES_MENU_STATE_H__
#define __BURGER_TIME_HIGHSCORES_MENU_STATE_H__

#include <array>
#include <vector>
#include <string>

#include <hyper/fwd.h>

#include "states/menu_state.h"

namespace burger_time
{
	class HighscoresMenuState final : public IMenuState
	{
	public:
		HighscoresMenuState(hyper::Scene& scene);

		void OnEnter() override;
		void OnExit() override;
		void PerformAction(Action action) override;

		HighscoresMenuState(const HighscoresMenuState&)				= delete;
		HighscoresMenuState(HighscoresMenuState&&)					= delete;
		HighscoresMenuState& operator=(const HighscoresMenuState&)	= delete;
		HighscoresMenuState& operator=(HighscoresMenuState&&)		= delete;

		~HighscoresMenuState() = default;

	private:
		struct Player
		{
			std::string name;
			uint32_t score;
		};

	private:
		hyper::Actor* m_pRootActor;
		hyper::Actor* m_pPlayers;

	private:
		void SetupTitleActors();
		void SetupHighScoreActors();

		static std::array<Player, 5> GetTopPlayers();
	};
}

#endif // !__BURGER_TIME_HIGHSCORES_MENU_STATE_H__
