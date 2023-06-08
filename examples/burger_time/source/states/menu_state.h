#ifndef __BURGER_TIME_MENU_STATE_H__
#define __BURGER_TIME_MENU_STATE_H__

#include <functional>
#include <string_view>
#include <vector>

#include <glm/vec2.hpp>

#include <hyper/fwd.h>

namespace burger_time
{
	class MenuFSMComponent;

	class AMenuState
	{
	public:
		AMenuState(MenuFSMComponent* pMenuFSM, int fontSize, float spacing);

		virtual void OnEnter();
		virtual void OnExit();

		void SetCursor(size_t index);
		void MoveCursor(int32_t delta);
		void Select() const;

		hyper::Actor* GetRootActor() const;
		MenuFSMComponent* GetMenuFSM() const;

		AMenuState(const AMenuState&)				= delete;
		AMenuState(AMenuState&&)					= delete;
		AMenuState& operator=(const AMenuState&)	= delete;
		AMenuState& operator=(AMenuState&&)			= delete;

		virtual ~AMenuState() = default;

	protected:
		void AddItem(std::string_view label, std::function<void()> onSelect);

	private:
		struct Item
		{
			hyper::Actor* pActor;
			std::function<void()> onSelect;
		};

	private:
		hyper::Actor* m_pRootActor;
		MenuFSMComponent* m_pMenuFSM;

		size_t m_CurrentItem = 0;
		std::vector<Item> m_Items;
		hyper::Actor* m_pItemMarker;

		int m_FontSize;
		float m_Spacing;

	private:
		void SetupItemMarker();
	};
}

#endif // !__BURGER_TIME_MENU_STATE_H__
