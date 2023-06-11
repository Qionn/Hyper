#ifndef __BURGER_TIME_OPTIONS_H__
#define __BURGER_TIME_OPTIONS_H__

#include <hyper/input/key.h>
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

		static inline Keys keys;
	};

	void SetupOptions(const hyper::Input& input);
}

#endif // !__BURGER_TIME_OPTIONS_H__
