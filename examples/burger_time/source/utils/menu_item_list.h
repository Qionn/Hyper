#ifndef __BURGER_TIME_MENU_ITEM_LIST_H__
#define __BURGER_TIME_MENU_ITEM_LIST_H__

#include <functional>
#include <string_view>
#include <vector>

#include <glm/vec2.hpp>

#include <hyper/service/sound_service.h>
#include <hyper/fwd.h>

namespace burger_time
{
	class MenuItemList final
	{
	public:
		MenuItemList(hyper::Actor* pRootActor, int ptSize, float spacing);

		void MoveCursor(int32_t delta);
		void Select() const;

		void AddItem(std::string_view label, std::function<void()> onSelect);

		MenuItemList(const MenuItemList&)				= delete;
		MenuItemList(MenuItemList&&)					= delete;
		MenuItemList& operator=(const MenuItemList&)	= delete;
		MenuItemList& operator=(MenuItemList&&)			= delete;

		~MenuItemList() = default;

	private:
		struct Item
		{
			hyper::Actor* pActor;
			std::function<void()> onSelect;
		};

	private:
		int m_PointSize;
		float m_Spacing;

		hyper::Actor* m_pRootActor;

		int32_t m_CurrentItem = 0;
		std::vector<Item> m_Items;
		hyper::Actor* m_pItemMarker;

		hyper::SoundId m_SoundId;

	private:
		void SetupItemMarker();
	};
}

#endif // !__BURGER_TIME_MENU_ITEM_LIST_H__
