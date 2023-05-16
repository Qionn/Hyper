#ifndef __HYPER_OBSERVER_H__
#define __HYPER_OBSERVER_H__

#include "hyper/fwd.h"

namespace hyper
{
	class IObserver
	{
	public:
		virtual bool OnEvent(const AEvent& event) = 0;
		virtual ~IObserver() = default;
	};
}


#endif // !__HYPER_OBSERVER_H__
