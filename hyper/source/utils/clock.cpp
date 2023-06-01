#include "hyper/utils/clock.h"

namespace hyper
{
	float Clock::Tick()
	{
		auto now = clock_t::now();
		float dt = std::chrono::duration<float>(now - m_PrevTickTime).count();
		m_PrevTickTime = now;
		return dt;
	}
}
