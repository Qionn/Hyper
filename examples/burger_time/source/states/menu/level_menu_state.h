#ifndef __BURGER_TIME_LEVEL_MENU_STATE_H__
#define __BURGER_TIME_LEVEL_MENU_STATE_H__

#include <memory>

#include <hyper/fwd.h>

#include "states/menu_state.h"
#include "utils/menu_item_list.h"

namespace burger_time
{
	class MenuFSMComponent;

	class LevelMenuState final : public IMenuState
	{
	public:
		LevelMenuState(hyper::Scene& scene, MenuFSMComponent* pMenuFSM);

		void OnEnter() override;
		void OnExit() override;
		void PerformAction(Action action) override;

		LevelMenuState(const LevelMenuState&)				= delete;
		LevelMenuState(LevelMenuState&&)					= delete;
		LevelMenuState& operator=(const LevelMenuState&)	= delete;
		LevelMenuState& operator=(LevelMenuState&&)			= delete;

		~LevelMenuState() = default;

	private:
		hyper::Actor* m_pRootActor;
		MenuFSMComponent* m_pMenuFSM;
		std::unique_ptr<MenuItemList> m_pMenuItemList;

	private:
		void SetupTitleActors();
		void SetupMenuItems();

		void OnLevel1Select();
		void OnLevel2Select();
		void OnLevel3Select();
	};
}

#endif // !__BURGER_TIME_LEVEL_MENU_STATE_H__
