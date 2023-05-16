#ifndef __HYPER_APPLICATION_H__
#define __HYPER_APPLICATION_H__

#include <memory>
#include <string_view>

#include "hyper/core/window.h"
#include "hyper/event/observer.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Application final : public IObserver
	{
	public:
		explicit Application(std::string_view name);

		void Start();
		void Stop();

		Application(const Application&)				= delete;
		Application(Application&&)					= delete;
		Application& operator=(const Application&)	= delete;
		Application& operator=(Application&&)		= delete;

		~Application();

	private:
		std::unique_ptr<Window> m_pWindow;

		bool m_IsRunning = false;
		
	private:
		bool OnEvent(const AEvent& event) override;
		bool OnWindowCloseEvent(const WindowCloseEvent& event);
	};
}

#endif // !__HYPER_APPLICATION_H__
