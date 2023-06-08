#ifndef __BURGER_TIME_MENU_FSM_COMPONENT_H__
#define __BURGER_TIME_MENU_FSM_COMPONENT_H__

#include <memory>
#include <stack>
#include <type_traits>
#include <vector>

#include <hyper/scene/component.h>

#include "states/menu_state.h"

namespace burger_time
{
	class MenuFSMComponent final : public hyper::AComponent
	{
	public:
		MenuFSMComponent(hyper::Actor& actor, size_t minStates);

		void PushMenuState(AMenuState* pState);
		void PopMenuState();

		template<class T, class ... Args>
		T* CreateState(Args&&... args)
		{
			static_assert(std::is_base_of_v<AMenuState, T>, "Type T must derive from AMenuState");
			m_StatePool.push_back(std::make_unique<T>(this, std::forward<Args>(args)...));
			return static_cast<T*>(m_StatePool.back().get());
		}

		AMenuState* GetCurrentMenuState() const;

		~MenuFSMComponent() = default;

	private:
		size_t m_MinStates;
		std::stack<AMenuState*> m_Stack;
		std::vector<std::unique_ptr<AMenuState>> m_StatePool;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;
	};
}

#endif // !__BURGER_TIME_MENU_FSM_COMPONENT_H__
