#ifndef __HYPER_INPUT_H__
#define __HYPER_INPUT_H__

#include <memory>

#include "hyper/event/subject.h"
#include "hyper/input/command_layer.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Input final : public ASubject
	{
	public:
		Input();

		void Update();

		void PushLayer(CommandLayer* pLayer);
		void PopLayer();

		void Bind(Key key, KeyState state, std::unique_ptr<ICommand> command);
		void Bind(Button button, ButtonState state, int gamepad, std::unique_ptr<ICommand> command);

		void Unbind(Key key, KeyState state);
		void Unbind(Button button, ButtonState state, int gamepad);

		void UnbindAll();
		void Reset();

		int GetGamepadCount() const;

		Keyboard& GetKeyboard() const;
		Gamepad* GetGamepad(int index) const;

		Input(const Input&)				= delete;
		Input(Input&&)					= delete;
		Input& operator=(const Input&)	= delete;
		Input& operator=(Input&&)		= delete;

		~Input();

	private:
		class Impl;
		Impl* m_pImpl;
	};
}

#endif // !__HYPER_INPUT_H__
