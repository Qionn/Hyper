#ifndef __HYPER_EVENT_H__
#define __HYPER_EVENT_H__

#include <concepts>
#include <typeinfo>

namespace hyper
{
	class AEvent
	{
	public:
		template<class T> requires std::derived_from<T, AEvent>
		const T* TryCastTo() const
		{
			if (typeid(T) == typeid(*this))
			{
				return reinterpret_cast<const T*>(this);
			}

			return nullptr;
		}

		virtual ~AEvent() = default;

	protected:
		AEvent() = default;
	};
}

#endif // !__HYPER_EVENT_H__
