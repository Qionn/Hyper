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
	class Actor final : public std::enable_shared_from_this<Actor>
	{
	public:
		explicit Actor(Scene& scene);

		void Update(float dt);
		void Render(const IContext& context) const;

		template<class T, class ... Args> T* AddComponent(Args&&... args);
		template<class T> bool RemoveComponent();
		template<class T> T* GetComponent() const;

		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& position);

		const glm::vec2& GetLocalPosition() const;
		const glm::vec2& GetWorldPosition() const;

		void ForEachChild(const std::function<void(Actor&)>& functor) const;

		void SetParent(Actor* pParent, bool keepWorldPosition);
		bool HasParent() const;
		Actor* GetParent() const;
		Scene* GetScene() const;

		Actor(const Actor&)				= delete;
		Actor(Actor&&)					= delete;
		Actor& operator=(const Actor&)	= delete;
		Actor& operator=(Actor&&)		= delete;

		~Actor();

	private:
		Scene* m_pScene;
		Actor* m_pParent = nullptr;
		std::vector<std::shared_ptr<Actor>> m_Children;
		std::unordered_map<int, std::unique_ptr<AComponent>> m_Components;
		TransformComponent* m_pTransform;

		friend Scene;

	private:
		void AddChild(std::shared_ptr<Actor> pChild);
		void RemoveChild(Actor* pChild);
	};
}

#include "hyper/details/scene/actor.inl"

#endif // !__HYPER_ACTOR_H__
