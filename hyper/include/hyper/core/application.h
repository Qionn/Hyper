#ifndef __HYPER_APPLICATION_H__
#define __HYPER_APPLICATION_H__

#include <functional>
#include <memory>
#include <string_view>

#include "hyper/core/renderer.h"
#include "hyper/core/window.h"
#include "hyper/event/observer.h"
#include "hyper/input/input.h"
#include "hyper/scene/scene.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Application final : public IObserver
	{
	public:
		struct Info final
		{
			std::string_view name;
			uint32_t windowWidth;
			uint32_t windowHeight;
		};

	public:
		explicit Application(const Info& info);

		void Start();
		void Stop();

		void LoadScene(const std::function<void(Scene&, Input&)>& loadScene);

		Application(const Application&)				= delete;
		Application(Application&&)					= delete;
		Application& operator=(const Application&)	= delete;
		Application& operator=(Application&&)		= delete;

		~Application() = default;

	private:
		std::unique_ptr<Window> m_pWindow;
		std::unique_ptr<Renderer> m_pRenderer;
		std::unique_ptr<Scene> m_pScene;
		std::unique_ptr<Input> m_pInput;

		bool m_IsRunning = false;
		bool m_CanStart = true;
		
	private:
		bool OnEvent(const AEvent& event) override;
		bool OnWindowCloseEvent(const WindowCloseEvent& event);
		bool OnSceneStopRequestEvent(const SceneStopRequestEvent& event);
		bool OnSceneLoadRequestEvent(const SceneLoadRequestEvent& event);
	};
}

#endif // !__HYPER_APPLICATION_H__
