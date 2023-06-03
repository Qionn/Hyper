#ifndef __BURGER_TIME_MAIN_MENU_STATE_H__
#define __BURGER_TIME_MAIN_MENU_STATE_H__

#include <hyper/fwd.h>

#include "states/menu_state.h"

namespace burger_time
{
	class MainMenuState final : public IMenuState
	{
	public:
		MainMenuState(hyper::Scene& scene);

		void OnEnter() override;
		void OnExit() override;

		MainMenuState(const MainMenuState&)				= delete;
		MainMenuState(MainMenuState&&)					= delete;
		MainMenuState& operator=(const MainMenuState&)	= delete;
		MainMenuState& operator=(MainMenuState&&)		= delete;

		~MainMenuState() = default;

	private:
		hyper::Actor* m_pRootActor;

	private:
		void SetupTitleActors(hyper::Scene& scene);
	};
}

#endif // !__BURGER_TIME_MAIN_MENU_STATE_H__
