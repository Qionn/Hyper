#ifndef __HYPER_INPUT_H__
#define __HYPER_INPUT_H__

#include "hyper/event/subject.h"
#include "hyper/fwd.h"

#define HYPER_INPUT (::hyper::Input::Get())

namespace hyper
{
	class Input final : public ASubject
	{
	public:
		static Input& Get();

		void Update();

		Input(const Input&)				= delete;
		Input(Input&&)					= delete;
		Input& operator=(const Input&)	= delete;
		Input& operator=(Input&&)		= delete;

		~Input();

	private:
		class Impl;
		Impl* m_pImpl;

	private:
		Input();
	};
}

#endif // !__HYPER_INPUT_H__
