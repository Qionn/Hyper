#ifndef __HYPER_ACTOR_H__
#define __HYPER_ACTOR_H__

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include <glm/vec2.hpp>

#include "hyper/scene/component.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Actor final
	{
	public:
		explicit Actor(Scene& scene);

		void Update(float dt);
		void Render() const;

		void Translate(float x, float y);
		void Translate(const glm::vec2& translation);

		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& position);
		const glm::vec2& GetLocalPosition() const;
		const glm::vec2& GetWorldPosition() const;

		Actor* CreateChild();
		void SetParent(Actor* pParent, bool keepWorldPosition);
		void ForEachChild(const std::function<void(Actor&)>& functor) const;
		bool HasParent() const;
		Actor* GetParent() const;

		void Destroy();
		Scene& GetScene() const;

		void SetEnabled(bool enabled);
		bool IsEnabled() const;

		template<class T, class ... Args> T* AddComponent(Args&&... args);
		template<class T> bool RemoveComponent();
		template<class T> T* GetComponent() const;

		Actor(const Actor&) = delete;
		Actor(Actor&&) = delete;
		Actor& operator=(const Actor&) = delete;
		Actor& operator=(Actor&&) = delete;

		~Actor();

	private:
		Scene& m_Scene;
		IContext& m_Context;

		Actor* m_pParent = nullptr;
		std::vector<Actor*> m_Children;

		std::unordered_map<int, std::unique_ptr<AComponent>> m_Components;
		TransformComponent* m_pTransform;

		bool m_IsEnabled = true;

	private:
		void AddChild(Actor* pChild);
		void RemoveChild(Actor* pChild);
	};
}

#include "hyper/details/scene/actor.inl"

#endif // !__HYPER_ACTOR_H__