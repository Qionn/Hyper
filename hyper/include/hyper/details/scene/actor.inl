#ifndef __HYPER_ACTOR_INL__
#define __HYPER_ACTOR_INL__

#include <type_traits>

#include "hyper/utils/typeid.h"

namespace hyper
{
	template<class T, class ... Args>
	T* Actor::AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of_v<AComponent, T>, "Type T must derive from AComponent");

		const int id = TypeId<T>();
		if (auto it = m_Components.find(id); it != m_Components.end())
		{
			return reinterpret_cast<T*>(it->second.get());
		}

		T* pComponent = new T(this, std::forward<Args>(args)...);
		m_Components.emplace(id, std::unique_ptr<AComponent>(pComponent));

		return pComponent;
	}

	template<class T>
	bool Actor::RemoveComponent()
	{
		static_assert(std::is_base_of_v<AComponent, T>, "Type T must derive from AComponent");
		static_assert(!std::is_same_v<TransformComponent, T>, "Unable to remove transform component");

		const int id = TypeId<T>();
		if (auto it = m_Components.find(id); it != m_Components.end())
		{
			m_Components.erase(it);
			return true;
		}

		return false;
	}

	template<class T>
	T* Actor::GetComponent() const
	{
		static_assert(std::is_base_of_v<AComponent, T>, "Type T must derive from AComponent");

		const int id = TypeId<T>();
		if (auto it = m_Components.find(id); it != m_Components.end())
		{
			return reinterpret_cast<T*>(it->second.get());
		}

		return nullptr;
	}
}

#endif // !__HYPER_ACTOR_INL__
