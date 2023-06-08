#include "pause_command.h"

#include "commands/menu_command.h"

#include <hyper/input/input.h>

using namespace hyper;

namespace burger_time
{
	PauseCommand::PauseCommand(MenuFSMComponent* pMenuFSM, hyper::Input& input)
		: m_pMenuFSM{ pMenuFSM }
		, m_Input{ input }
	{
		m_pState = m_pMenuFSM->CreateState<PauseMenuState>(input);
		m_pCommandLayer = std::make_unique<CommandLayer>();

		m_pCommandLayer->Bind(Key::eUp, KeyState::ePressed, std::make_unique<MenuCommand>(m_pMenuFSM, MenuCommand::Action::eCursorUp));
		m_pCommandLayer->Bind(Key::eDown, KeyState::ePressed, std::make_unique<MenuCommand>(m_pMenuFSM, MenuCommand::Action::eCursorDown));
		m_pCommandLayer->Bind(Key::eEnter, KeyState::ePressed, std::make_unique<MenuCommand>(m_pMenuFSM, MenuCommand::Action::eSelect));
	}

	void PauseCommand::Execute()
	{
		m_pMenuFSM->PushMenuState(m_pState);
		m_Input.PushLayer(m_pCommandLayer.get());
	}
}
