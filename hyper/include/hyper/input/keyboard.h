#ifndef __HYPER_KEYBOARD_H__
#define __HYPER_KEYBOARD_H__

#include "hyper/input/key.h"

namespace hyper
{
	class Keyboard final
	{
	public:
		Keyboard();

		void Update();

		bool IsDown(Key key) const;
		bool IsPressed(Key key) const;
		bool IsReleased(Key key) const;

		Keyboard(const Keyboard&)				= delete;
		Keyboard(Keyboard&&)					= delete;
		Keyboard& operator=(const Keyboard&)	= delete;
		Keyboard& operator=(Keyboard&&)			= delete;

		~Keyboard();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}

#endif // !__HYPER_KEYBOARD_H__
