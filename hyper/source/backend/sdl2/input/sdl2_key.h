#ifndef __HYPER_SDL2_KEY_H__
#define __HYPER_SDL2_KEY_H__

#include "hyper/input/key.h"

namespace hyper
{
	int KeyToSDL2Key(Key key);
	Key SDL2KeyToKey(int key);
}

#endif // !__HYPER_SDL2_KEY_H__
