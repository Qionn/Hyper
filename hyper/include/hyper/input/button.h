#ifndef __HYPER_BUTTON_H__
#define __HYPER_BUTTON_H__

namespace hyper
{
	enum class ButtonState
	{
		eDown,
		ePressed,
		eReleased
	};

	enum class Button
	{
		eA,
		eB,
		eX,
		eY,
		eBack,
		eGuide,
		eStart,
		eLeftStck,
		eRightStick,
		eLeftShoulder,
		eRightSoulder,
		eDpadUp,
		eDpadDown,
		eDpadLeft,
		eDpadRight,
		eTouchpad,

		eMax,
		eUnknown = -1
	};
}

#endif // !__HYPER_BUTTON_H__
