#ifndef __BURGER_TIME_OPTIONS_H__
#define __BURGER_TIME_OPTIONS_H__

#include <hyper/input/key.h>
#include <hyper/input/button.h>
#include <hyper/fwd.h>

namespace burger_time
{
	struct Options final
	{
		struct Keys
		{
			hyper::Key menuUp;
			hyper::Key menuDown;
			hyper::Key menuSelect;
			hyper::Key menuReturn;
			hyper::Key pause;
			hyper::Key characterUp;
			hyper::Key characterDown;
			hyper::Key characterLeft;
			hyper::Key characterRight;
		};

		struct Buttons
		{
			hyper::Button menuUp;
			hyper::Button menuDown;
			hyper::Button menuSelect;
			hyper::Button menuReturn;
			hyper::Button pause;
			hyper::Button characterUp;
			hyper::Button characterDown;
			hyper::Button characterLeft;
			hyper::Button characterRight;
		};

		static inline Keys keys;
		static inline Buttons buttons;
	};

	void SetupOptions(const hyper::Input& input);
}

#endif // !__BURGER_TIME_OPTIONS_H__
