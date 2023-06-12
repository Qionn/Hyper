#ifndef __HYPER_SDL2_INPUT_H__
#define __HYPER_SDL2_INPUT_H__

#include <functional>
#include <memory>
#include <stack>
#include <vector>

#include "hyper/input/input.h"
#include "hyper/input/keyboard.h"
#include "hyper/input/gamepad.h"

namespace hyper
{
	class Input::Impl final
	{
	public:
		using EventCallback = std::function<void(const AEvent&)>;

	public:
		Impl();

		void Update();

		void PushLayer(CommandLayer* pLayer);
		void Poplayer();

		void Bind(Key key, KeyState state, std::unique_ptr<ICommand> command);
		void Bind(Button button, ButtonState state, int gamepad, std::unique_ptr<ICommand> command);

		void Unbind(Key key, KeyState state);
		void Unbind(Button button, ButtonState state, int gamepad);

		void UnbindAll();
		void Reset();

		int GetGamepadCount() const;

		Keyboard& GetKeyboard() const;
		Gamepad* GetGamepad(int index) const;

		void SetEventCallback(const EventCallback& callback);

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl() = default;

	private:
		std::unique_ptr<Keyboard> m_pKeyboard;
		std::vector<std::unique_ptr<Gamepad>> m_Gamepads;

		std::stack<CommandLayer*> m_LayerStack;
		std::unique_ptr<CommandLayer> m_pDefaultLayer;
		std::unique_ptr<CommandLayer> m_pDefaultLayerBuffer;

		EventCallback m_Callback;

	private:
		void HandleEvents();
		void FireEvent(const AEvent& event) const;
	};
}

#endif // !__HYPER_SDL2_INPUT_H__
