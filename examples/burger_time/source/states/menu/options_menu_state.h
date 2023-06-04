#ifndef __BURGER_TIME_OPTIONS_MENU_STATE_H__
#define __BURGER_TIME_OPTIONS_MENU_STATE_H__

#include <hyper/fwd.h>

#include "states/menu_state.h"

namespace burger_time
{
	class OptionsMenuState final : public IMenuState
	{
	public:
		OptionsMenuState(hyper::Scene& scene);

		void OnEnter() override;
		void OnExit() override;
		void PerformAction(Action action) override;

		OptionsMenuState(const OptionsMenuState&) = delete;
		OptionsMenuState(OptionsMenuState&&) = delete;
		OptionsMenuState& operator=(const OptionsMenuState&) = delete;
		OptionsMenuState& operator=(OptionsMenuState&&) = delete;

		~OptionsMenuState() = default;

	private:
		hyper::Actor* m_pRootActor;

	private:
		void SetupTitleActors(hyper::Scene& scene);
	};
}

#endif // !__BURGER_TIME_OPTIONS_MENU_STATE_H__
