#include "menu_fsm_component.h"

using namespace hyper;

namespace burger_time
{
	MenuFSMComponent::MenuFSMComponent(hyper::Actor& actor, size_t minStates)
		: AComponent(actor)
		, m_MinStates(minStates)
	{

	}

	void MenuFSMComponent::PushMenuState(AMenuState* pState)
	{
		if (!m_Stack.empty())
		{
			m_Stack.top()->OnExit();
		}

		m_Stack.push(pState);
		pState->OnEnter();
	}

	void MenuFSMComponent::PopMenuState()
	{
		if (m_Stack.size() > m_MinStates)
		{
			m_Stack.top()->OnExit();
			m_Stack.pop();

			if (!m_Stack.empty())
			{
				m_Stack.top()->OnEnter();
			}
		}
	}

	AMenuState* MenuFSMComponent::GetCurrentMenuState() const
	{
		return m_Stack.top();
	}

	void MenuFSMComponent::OnUpdate(float)
	{

	}

	void MenuFSMComponent::OnRender(const IContext&) const
	{

	}
}
