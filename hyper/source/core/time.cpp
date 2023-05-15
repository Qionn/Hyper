#include "pch.h"

#include "hyper/core/time.h"

namespace hyper
{
	/* static */ Time::Clock::time_point Time::s_Start;
	/* static */ Time::Clock::duration Time::s_DeltaTime(0);

	/* static */ void Time::start()
	{
		s_Start = Clock::now();
	}

	/* static */ void Time::stop()
	{
		s_DeltaTime = Clock::now() - s_Start;
	}
}
