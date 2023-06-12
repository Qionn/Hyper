#ifndef __HYPER_SDL2_BUTTON_H__
#define __HYPER_SDL2_BUTTON_H__

#include <SDL.h>

#include "hyper/input/button.h"

namespace hyper
{
	SDL_GameControllerButton ButtonToSDL2Button(Button button);
	Button SDL2ButtonToButton(SDL_GameControllerButton button);
}

#endif // !__HYPER_SDL2_BUTTON_H__
