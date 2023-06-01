#ifndef __HYPER_WINDOW_H__
#define __HYPER_WINDOW_H__

#include <cstdint>
#include <string_view>

namespace hyper
{
	class Window final
	{
	public:
		using id_t = uintptr_t;

	public:
		Window(uint32_t width, uint32_t height, std::string_view title);

		void Show();
		void Hide();

		id_t GetId() const;
		void* GetNativeWindow() const;

		Window(const Window&)				= delete;
		Window(Window&&)					= delete;
		Window& operator=(const Window&)	= delete;
		Window& operator=(Window&&)			= delete;

		~Window();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}

#endif // !__HYPER_WINDOW_H__
