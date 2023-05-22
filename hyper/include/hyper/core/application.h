#ifndef __HYPER_APPLICATION_H__
#define __HYPER_APPLICATION_H__

#include <functional>
#include <memory>
#include <string_view>

#include "hyper/core/renderer.h"
#include "hyper/core/window.h"
#include "hyper/event/observer.h"
#include "hyper/scene/scene_factory.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Application final : public IObserver
	{
	public:
		using LoadSceneFunctor = std::function<SceneFactory()>;

		struct Info final
		{
			std::string_view name;
			uint32_t windowWidth;
			uint32_t windowHeight;
			LoadSceneFunctor loadScene;
		};

	public:
		explicit Application(const Info& info);

		void Start();
		void Stop();

		Application(const Application&)				= delete;
		Application(Application&&)					= delete;
		Application& operator=(const Application&)	= delete;
		Application& operator=(Application&&)		= delete;

		~Application();

	private:
		std::unique_ptr<Window> m_pWindow;
		std::unique_ptr<Renderer> m_pRenderer;
		std::unique_ptr<Scene> m_pScene;

		bool m_IsRunning = false;
		
	private:
		bool OnEvent(const AEvent& event) override;
		bool OnWindowCloseEvent(const WindowCloseEvent& event);
	};
}

#endif // !__HYPER_APPLICATION_H__
