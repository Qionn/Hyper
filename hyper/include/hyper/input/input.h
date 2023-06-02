#ifndef __HYPER_INPUT_H__
#define __HYPER_INPUT_H__

#include <memory>

#include "hyper/event/subject.h"
#include "hyper/input/key.h"
#include "hyper/utils/command.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Input final : public ASubject
	{
	public:
		Input();

		void Update();

		void Bind(Key key, KeyState state, std::unique_ptr<ICommand> command);
		void Unbind(Key key, KeyState state);

		void ClearBindings();

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
