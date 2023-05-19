#ifndef __HYPER_ACTOR_H__
#define __HYPER_ACTOR_H__

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include <glm/vec2.hpp>

#include "hyper/scene/component.h"
#include "hyper/utils/typeid.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Actor final
	{
	public:
		void Update();
		void Render() const;

		template<class T, class ... Args>	T* AddComponent(Args&&... args);
		template<class T>					bool RemoveComponent();
		template<class T>					T* GetComponent() const;

		void ForEachChild(const std::function<void(Actor&)>& functor);

		void SetParent(Actor* pParent, bool keepWorldPosition);

		Actor* GetParent() const;
		Scene* GetScene() const;

		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& position);

		const glm::vec2& GetLocalPosition() const;
		const glm::vec2& GetWorldPosition() const;

		Actor(const Actor&)				= delete;
		Actor(Actor&&)					= delete;
		Actor& operator=(const Actor&)	= delete;
		Actor& operator=(Actor&&)		= delete;

		~Actor() = default;

	private:
		Scene* m_pScene;
		Actor* m_pParent = nullptr;
		std::vector<Actor*> m_Children;

		std::unordered_map<int, std::unique_ptr<AComponent>> m_Components;
		TransformComponent* m_pTransform;

		friend Scene;

	private:
		explicit Actor(Scene* pScene);

		void AddChild(Actor* pChild);
		void RemoveChild(const Actor* pChild);
	};
}

#include "hyper/details/scene/actor.inl"

#endif // !__HYPER_ACTOR_H__
