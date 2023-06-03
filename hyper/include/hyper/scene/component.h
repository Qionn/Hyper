#ifndef __HYPER_COMPONENT_H__
#define __HYPER_COMPONENT_H__

#include "hyper/fwd.h"

namespace hyper
{
	class AComponent
	{
	public:
		explicit AComponent(Actor& actor);

		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender(const IContext& context) const = 0;

		Actor& GetActor() const;
		Actor* GetActorParent() const;

		Scene& GetScene() const;

		AComponent(const AComponent&)				= delete;
		AComponent(AComponent&&)					= delete;
		AComponent& operator=(const AComponent&)	= delete;
		AComponent& operator=(AComponent&&)			= delete;

		virtual ~AComponent() = default;

	private:
		Actor& m_Actor;
	};
}

#endif // !__HYPER_COMPONENT_H__
