#ifndef __HYPER_TIME_H__
#define __HYPER_TIME_H__

#include <chrono>
#include <concepts>

namespace hyper
{
	class Time final
	{
	public:
		using Clock = std::chrono::high_resolution_clock;

		static void start();
		static void stop();

		template<class T = float> requires std::floating_point<T>
		static T deltatime()
		{
			return std::chrono::duration<T>(s_DeltaTime).count();
		}

	private:
		static Clock::time_point s_Start;
		static Clock::duration s_DeltaTime;
	};
}

#endif // !__HYPER_TIME_H__
