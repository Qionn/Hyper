#ifndef __HYPER_COMPONENT_H__
#define __HYPER_COMPONENT_H__

#include "hyper/fwd.h"

namespace hyper
{
	class AComponent
	{
	public:
		AComponent(Actor* pActor);

		virtual void OnUpdate() = 0;
		virtual void OnRender() const = 0;

		Actor* GetActor() const;
		Actor* GetActorParent() const;

		Scene* GetScene() const;
		IContext& GetSceneContext() const;

		AComponent(const AComponent&)				= delete;
		AComponent(AComponent&&)					= delete;
		AComponent& operator=(const AComponent&)	= delete;
		AComponent& operator=(AComponent&&)			= delete;

		virtual ~AComponent() = default;

	private:
		Actor* m_pActor;
	};
}

#endif // !__HYPER_COMPONENT_H__
