#ifndef __HYPER_TRANSFORM_COMPONENT_H__
#define __HYPER_TRANSFORM_COMPONENT_H__

#include <glm/vec2.hpp>

#include "hyper/scene/component.h"

namespace hyper
{
	class TransformComponent final : public AComponent
	{
	public:
		TransformComponent(Actor* pActor);

		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& position);

		const glm::vec2& GetLocalPosition() const;
		const glm::vec2& GetWorldPosition();

		void SetDirty();

		~TransformComponent() = default;

	private:
		glm::vec2 m_Position		= { 0, 0 };
		glm::vec2 m_WorldPosition	= { 0, 0 };
		bool m_IsDirty				= true;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const IContext& context) const override;
	};
}

#endif // !__HYPER_TRANSFORM_COMPONENT_H__
