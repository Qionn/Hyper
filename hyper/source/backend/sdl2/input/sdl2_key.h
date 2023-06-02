#ifndef __HYPER_SDL2_KEY_H__
#define __HYPER_SDL2_KEY_H__

#include <SDL.h>

#include "hyper/input/key.h"

namespace hyper
{
	SDL_KeyCode KeyToSDL2Key(Key key);
	Key SDL2KeyToKey(SDL_KeyCode key);
}

#endif // !__HYPER_SDL2_KEY_H__
