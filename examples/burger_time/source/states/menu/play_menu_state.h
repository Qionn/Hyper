#ifndef __BURGER_TIME_PLAY_MENU_STATE_H__
#define __BURGER_TIME_PLAY_MENU_STATE_H__

#include <hyper/fwd.h>

#include "states/menu_state.h"

namespace burger_time
{
	class PlayMenuState final : public IMenuState
	{
	public:
		PlayMenuState(hyper::Scene& scene);

		void OnEnter() override;
		void OnExit() override;
		void PerformAction(Action action) override;

		PlayMenuState(const PlayMenuState&)				= delete;
		PlayMenuState(PlayMenuState&&)					= delete;
		PlayMenuState& operator=(const PlayMenuState&)	= delete;
		PlayMenuState& operator=(PlayMenuState&&)		= delete;

		~PlayMenuState() = default;

	private:
		hyper::Actor* m_pRootActor;

	private:
		void SetupTitleActors(hyper::Scene& scene);
	};
}

#endif // !__BURGER_TIME_PLAY_MENU_STATE_H__
