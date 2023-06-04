#ifndef __BURGER_TIME_MENU_STATE_H__
#define __BURGER_TIME_MENU_STATE_H__

namespace burger_time
{
	class IMenuState
	{
	public:
		enum class Action
		{
			eUp,
			eDown,
			eLeft,
			eRight,
			eSelect
		};

	public:
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void PerformAction(Action action) = 0;
		virtual ~IMenuState() = default;
	};
}

#endif // !__BURGER_TIME_MENU_STATE_H__
