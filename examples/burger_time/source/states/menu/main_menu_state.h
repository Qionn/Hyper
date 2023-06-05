#ifndef __BURGER_TIME_MAIN_MENU_STATE_H__
#define __BURGER_TIME_MAIN_MENU_STATE_H__

#include <memory>
#include <vector>

#include <hyper/fwd.h>

#include "states/menu/highscores_menu_state.h"
#include "states/menu/options_menu_state.h"
#include "states/menu/play_menu_state.h"
#include "utils/menu_item_list.h"

namespace burger_time
{
	class MenuFSMComponent;

	class MainMenuState final : public IMenuState
	{
	public:
		MainMenuState(hyper::Scene& scene, MenuFSMComponent* pMenuFSM);

		void OnEnter() override;
		void OnExit() override;
		void PerformAction(Action action) override;

		MainMenuState(const MainMenuState&)				= delete;
		MainMenuState(MainMenuState&&)					= delete;
		MainMenuState& operator=(const MainMenuState&)	= delete;
		MainMenuState& operator=(MainMenuState&&)		= delete;

		~MainMenuState() = default;

	private:
		hyper::Actor* m_pRootActor;

		MenuFSMComponent* m_pMenuFSM;

		std::unique_ptr<HighscoresMenuState> m_pHighscoresState;
		std::unique_ptr<OptionsMenuState> m_pOptionsState;
		std::unique_ptr<PlayMenuState> m_pPlayState;

		std::unique_ptr<MenuItemList> m_pMenuItemList;

	private:
		void SetupTitleActors(hyper::Scene& scene);
		void SetupMenuItems(hyper::Scene& scene);

		void OnPlaySelect();
		void OnHighscoresSelect();
		void OnOptionsSelect();
		void OnExitSelect();
	};
}

#endif // !__BURGER_TIME_MAIN_MENU_STATE_H__
