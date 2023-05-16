#ifndef __HYPER_SDL2_WINDOW_H__
#define __HYPER_SDL2_WINDOW_H__

#include <functional>

#include <SDL.h>

#include "hyper/core/window.h"

namespace hyper
{
	class Window::Impl final
	{
		using EventCallback = std::function<void(const AEvent&)>;

	public:
		Impl(uint32_t width, uint32_t height, std::string_view title);

		void Update();
		void Show();
		void Hide();

		void* GetNativeWindow() const;
		void SetEventCallback(const EventCallback& callback);

		Impl(const Impl&) = delete;
		Impl(Impl&&) = delete;
		Impl& operator=(const Impl&) = delete;
		Impl& operator=(Impl&&) = delete;

		~Impl();

	private:
		SDL_Window* m_pWindow;
		uint32_t m_Id;

		EventCallback m_Callback;

		static inline size_t s_InstanceCount = 0;

	private:
		void FireEvent(const AEvent& event) const;
		static int EventFilter(void* pUserData, SDL_Event* pEvent);
	};
}

#endif // !__HYPER_SDL2_WINDOW_H__
