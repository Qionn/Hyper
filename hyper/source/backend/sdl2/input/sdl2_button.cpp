#include "sdl2_button.h"

namespace hyper
{
	SDL_GameControllerButton ButtonToSDL2Button(Button button)
	{
		switch (button)
		{
			case Button::eA:			return SDL_CONTROLLER_BUTTON_A;
			case Button::eB:			return SDL_CONTROLLER_BUTTON_B;
			case Button::eX:			return SDL_CONTROLLER_BUTTON_X;
			case Button::eY:			return SDL_CONTROLLER_BUTTON_Y;
			case Button::eBack:			return SDL_CONTROLLER_BUTTON_BACK;
			case Button::eGuide:		return SDL_CONTROLLER_BUTTON_GUIDE;
			case Button::eStart:		return SDL_CONTROLLER_BUTTON_START;
			case Button::eLeftStck:		return SDL_CONTROLLER_BUTTON_LEFTSTICK;
			case Button::eRightStick:	return SDL_CONTROLLER_BUTTON_RIGHTSTICK;
			case Button::eLeftShoulder:	return SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
			case Button::eRightSoulder:	return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
			case Button::eDpadUp:		return SDL_CONTROLLER_BUTTON_DPAD_UP;
			case Button::eDpadDown:		return SDL_CONTROLLER_BUTTON_DPAD_DOWN;
			case Button::eDpadLeft:		return SDL_CONTROLLER_BUTTON_DPAD_LEFT;
			case Button::eDpadRight:	return SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
			case Button::eTouchpad:		return SDL_CONTROLLER_BUTTON_TOUCHPAD;
			default:					return SDL_CONTROLLER_BUTTON_INVALID;
		}
	}

	Button SDL2ButtonToButton(SDL_GameControllerButton button)
	{
		switch (button)
		{
			case SDL_CONTROLLER_BUTTON_A:				return Button::eA;
			case SDL_CONTROLLER_BUTTON_B:				return Button::eB;
			case SDL_CONTROLLER_BUTTON_X:				return Button::eX;
			case SDL_CONTROLLER_BUTTON_Y:				return Button::eY;
			case SDL_CONTROLLER_BUTTON_BACK:			return Button::eBack;
			case SDL_CONTROLLER_BUTTON_GUIDE:			return Button::eGuide;
			case SDL_CONTROLLER_BUTTON_START:			return Button::eStart;
			case SDL_CONTROLLER_BUTTON_LEFTSTICK:		return Button::eLeftStck;
			case SDL_CONTROLLER_BUTTON_RIGHTSTICK:		return Button::eRightStick;
			case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:	return Button::eLeftShoulder;
			case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:	return Button::eRightSoulder;
			case SDL_CONTROLLER_BUTTON_DPAD_UP:			return Button::eDpadUp;
			case SDL_CONTROLLER_BUTTON_DPAD_DOWN:		return Button::eDpadDown;
			case SDL_CONTROLLER_BUTTON_DPAD_LEFT:		return Button::eDpadLeft;
			case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:		return Button::eDpadRight;
			case SDL_CONTROLLER_BUTTON_TOUCHPAD:		return Button::eTouchpad;
			default:									return Button::eUnknown;
		}
	}
}
