#include "hyper/input/command_layer.h"
#include "hyper/input/keyboard.h"

#include <algorithm>

namespace hyper
{
	void CommandLayer::Update(Keyboard* pKeyboard)
	{
		for (const auto& keyStatePair : m_KeysToUnbind)
		{
			m_KeyboardCommands.erase(keyStatePair);
		}

		pKeyboard->Update();

		for (auto& [id, pCommand] : m_KeyboardCommands)
		{
			auto [key, state] = id;

			switch (state)
			{
				case KeyState::eDown:
					if (pKeyboard->IsDown(key))
					{
						pCommand->Execute();
					}
					break;

				case KeyState::ePressed:
					if (pKeyboard->IsPressed(key))
					{
						pCommand->Execute();
					}
					break;

				case KeyState::eReleased:
					if (pKeyboard->IsReleased(key))
					{
						pCommand->Execute();
					}
					break;
			}
		}
	}

	void CommandLayer::Bind(Key key, KeyState state, std::unique_ptr<ICommand> command)
	{
		std::pair<Key, KeyState> keyStatePair(key, state);

		if (auto it = std::remove(m_KeysToUnbind.begin(), m_KeysToUnbind.end(), keyStatePair); it != m_KeysToUnbind.end())
		{
			m_KeysToUnbind.erase(it, m_KeysToUnbind.end());
		}

		m_KeyboardCommands[keyStatePair] = std::move(command);
	}

	void CommandLayer::Unbind(Key key, KeyState state)
	{
		m_KeysToUnbind.push_back({ key, state });
	}

	void CommandLayer::UnbindAll()
	{
		for (const auto& [id, pCommand] : m_KeyboardCommands)
		{
			m_KeysToUnbind.push_back(id);
		}
	}
}
