#ifndef __HYPER_WINDOW_H__
#define __HYPER_WINDOW_H__

#include <string_view>

namespace hyper
{
	class Window final
	{
	public:
		Window(uint32_t width, uint32_t height, std::string_view title);

		void Show();
		void Hide();

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
