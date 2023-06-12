#include "hyper/input/command_layer.h"
#include "hyper/input/gamepad.h"
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

	void CommandLayer::Update(Gamepad* pGamepad, int index)
	{
		for (const auto& buttonStatePair : m_ButtonsToUnbind)
		{
			m_GamepadCommands.erase(buttonStatePair);
		}

		pGamepad->Update();

		for (auto& [id, pCommand] : m_GamepadCommands)
		{
			auto [gamepadIndex, statePair] = id;
			if (gamepadIndex == index)
			{
				auto [button, state] = statePair;

				switch (state)
				{
					case ButtonState::eDown:
						if (pGamepad->IsDown(button))
						{
							pCommand->Execute();
						}
						break;

					case ButtonState::ePressed:
						if (pGamepad->IsPressed(button))
						{
							pCommand->Execute();
						}
						break;

					case ButtonState::eReleased:
						if (pGamepad->IsReleased(button))
						{
							pCommand->Execute();
						}
						break;
				}
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

	void CommandLayer::Bind(Button button, ButtonState state, int gamepad, std::unique_ptr<ICommand> command)
	{
		std::pair<int, std::pair<Button, ButtonState>> buttonStatePair(gamepad, { button, state });

		if (auto it = std::remove(m_ButtonsToUnbind.begin(), m_ButtonsToUnbind.end(), buttonStatePair); it != m_ButtonsToUnbind.end())
		{
			m_ButtonsToUnbind.erase(it, m_ButtonsToUnbind.end());
		}

		m_GamepadCommands[buttonStatePair] = std::move(command);
	}

	void CommandLayer::Unbind(Key key, KeyState state)
	{
		m_KeysToUnbind.push_back({ key, state });
	}

	void CommandLayer::Unbind(Button button, ButtonState state, int gamepad)
	{
		m_ButtonsToUnbind.push_back({ gamepad, { button, state } });
	}

	void CommandLayer::UnbindAll()
	{
		for (const auto& [id, pCommand] : m_KeyboardCommands)
		{
			m_KeysToUnbind.push_back(id);
		}

		for (const auto& [id, pCommand] : m_GamepadCommands)
		{
			m_ButtonsToUnbind.push_back(id);
		}
	}
}
