#ifndef __HYPER_SDL2_INPUT_H__
#define __HYPER_SDL2_INPUT_H__

#include <functional>

#include "hyper/input/input.h"

namespace hyper
{
	class Input::Impl final
	{
	public:
		using EventCallback = std::function<void(const AEvent&)>;

	public:
		Impl() = default;

		void Update();

		void SetEventCallback(const EventCallback& callback);

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl() = default;

	private:
		EventCallback m_Callback;

	private:
		void FireEvent(const AEvent& event) const;
	};
}

#endif // !__HYPER_SDL2_INPUT_H__
