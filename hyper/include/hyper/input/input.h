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
		void Unbind(Key key, KeyState state);
		void UnbindAll();

		void Reset();

		Keyboard& GetKeyboard() const;

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
