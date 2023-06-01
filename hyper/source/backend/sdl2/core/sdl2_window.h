#ifndef __HYPER_SDL2_WINDOW_H__
#define __HYPER_SDL2_WINDOW_H__

#include <functional>

#include <SDL.h>

#include "hyper/core/window.h"

namespace hyper
{
	class Window::Impl final
	{
	public:
		Impl(uint32_t width, uint32_t height, std::string_view title);

		void Show();
		void Hide();

		id_t GetId() const;
		void* GetNativeWindow() const;

		Impl(const Impl&) = delete;
		Impl(Impl&&) = delete;
		Impl& operator=(const Impl&) = delete;
		Impl& operator=(Impl&&) = delete;

		~Impl();

	private:
		id_t m_Id;
		SDL_Window* m_pWindow;

		static inline size_t s_InstanceCount = 0;
	};
}

#endif // !__HYPER_SDL2_WINDOW_H__
