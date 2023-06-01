#ifndef __HYPER_CLOCK_H__
#define __HYPER_CLOCK_H__

#include <chrono>

namespace hyper
{
	class Clock final
	{
	public:
		using clock_t = std::chrono::high_resolution_clock;

	public:
		float Tick();

	private:
		clock_t::time_point m_PrevTickTime = clock_t::now();
	};
}

#endif // !__HYPER_CLOCK_H__
