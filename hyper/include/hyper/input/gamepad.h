#ifndef __HYPER_GAMEPAD_H__
#define __HYPER_GAMEPAD_H__

#include "hyper/input/button.h"

namespace hyper
{
	class Gamepad final
	{
	public:
		Gamepad(int index);

		void Update();

		bool IsDown(Button button) const;
		bool IsPressed(Button button) const;
		bool IsReleased(Button button) const;

		Gamepad(const Gamepad&) = delete;
		Gamepad(Gamepad&&) = delete;
		Gamepad& operator=(const Gamepad&) = delete;
		Gamepad& operator=(Gamepad&&) = delete;

		~Gamepad();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}

#endif // !__HYPER_GAMEPAD_H__
