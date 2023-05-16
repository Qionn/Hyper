#ifndef __HYPER_APPLICATION_H__
#define __HYPER_APPLICATION_H__

#include <memory>
#include <string_view>

#include "hyper/core/renderer.h"
#include "hyper/core/window.h"
#include "hyper/event/observer.h"
#include "hyper/utils/layer_stack.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Application final : public IObserver
	{
	public:
		explicit Application(std::string_view name);

		void Start();
		void Stop();

		template<class T, class ... Args>
		void PushLayer(Args&&... args)
		{
			m_pLayerStack->Push<T>(std::forward<Args>(args)...);
		}

		void PopLayer();

		Application(const Application&)				= delete;
		Application(Application&&)					= delete;
		Application& operator=(const Application&)	= delete;
		Application& operator=(Application&&)		= delete;

		~Application();

	private:
		std::unique_ptr<Window> m_pWindow;
		std::unique_ptr<Renderer> m_pRenderer;
		std::unique_ptr<LayerStack> m_pLayerStack;

		bool m_IsRunning = false;
		
	private:
		bool OnEvent(const AEvent& event) override;
		bool OnWindowCloseEvent(const WindowCloseEvent& event);
	};
}

#endif // !__HYPER_APPLICATION_H__
