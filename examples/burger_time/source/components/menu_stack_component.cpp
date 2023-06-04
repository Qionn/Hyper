#include "menu_stack_component.h"

using namespace hyper;

namespace burger_time
{
	MenuStackComponent::MenuStackComponent(Actor& actor)
		: AComponent(actor)
	{
		Scene& scene = GetScene();

		m_pMainMenuState	= std::make_unique<MainMenuState>(scene);
		m_pOptionsMenuState	= std::make_unique<OptionsMenuState>(scene);
		m_pPlayMenuState	= std::make_unique<PlayMenuState>(scene);

		PushMenuState(m_pMainMenuState.get());
	}

	void MenuStackComponent::PushMenuState(IMenuState* pState)
	{
		if (!m_StateStack.empty())
		{
			IMenuState* pTopState = m_StateStack.top();
			pTopState->OnExit();
		}

		m_StateStack.push(pState);
		pState->OnEnter();
	}

	void MenuStackComponent::PopMenuState()
	{
		if (m_StateStack.size() > 1)
		{
			IMenuState* pTopState = m_StateStack.top();
			m_StateStack.pop();
			pTopState->OnExit();

			pTopState = m_StateStack.top();
			pTopState->OnEnter();
		}
	}

	IMenuState* MenuStackComponent::GetCurrentMenuState() const
	{
		return m_StateStack.top();
	}

	MainMenuState* MenuStackComponent::GetMainMenuState() const
	{
		return m_pMainMenuState.get();
	}

	OptionsMenuState* MenuStackComponent::GetOptionsMenuState() const
	{
		return m_pOptionsMenuState.get();
	}

	PlayMenuState* MenuStackComponent::GetPlayMenuState() const
	{
		return m_pPlayMenuState.get();
	}

	void MenuStackComponent::OnUpdate(float)
	{

	}

	void MenuStackComponent::OnRender(const IContext&) const
	{

	}

}
