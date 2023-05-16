#ifndef __HYPER_DISPATCHER_H__
#define __HYPER_DISPATCHER_H__

#include <functional>

#include "hyper/event/event.h"

namespace hyper
{
	class Dispatcher final
	{
	public:
		explicit Dispatcher(const AEvent& event);

		bool IsEventHandled() const;

		template<class T>
		void Dispatch(const std::function<bool(const T&)>& handler)
		{
			if (!m_IsHandled)
			{
				if (const T* event = m_Event.TryCastTo<T>())
				{
					m_IsHandled = handler(*event);
				}
			}
		}

		template<class T, class U>
		void Dispatch(bool(U::* handler)(const T&), U* thisPtr)
		{
			Dispatch<T>(std::bind(handler, thisPtr, std::placeholders::_1));
		}

		~Dispatcher() = default;

	private:
		const AEvent& m_Event;
		bool m_IsHandled = false;
	};
}

#endif // !__HYPER_DISPATCHER_H__
