#include "hyper/event/dispatcher.h"

namespace hyper
{
	Dispatcher::Dispatcher(const AEvent& event)
		: m_Event{ event }
	{

	}

	bool Dispatcher::IsEventHandled() const
	{
		return m_IsHandled;
	}
}
