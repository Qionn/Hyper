#ifndef __HYPER_COMMAND_LAYER_H__
#define __HYPER_COMMAND_LAYER_H__

#include <map>
#include <memory>
#include <vector>

#include "hyper/input/key.h"
#include "hyper/input/button.h"
#include "hyper/utils/command.h"
#include "hyper/fwd.h"

namespace hyper
{
	class CommandLayer final
	{
	public:
		CommandLayer() = default;

		void Update(Keyboard* pKeyboard);
		void Update(Gamepad* pGamepad, int index);

		void Bind(Key key, KeyState state, std::unique_ptr<ICommand> command);
		void Bind(Button button, ButtonState state, int gamepad, std::unique_ptr<ICommand> command);

		void Unbind(Key key, KeyState state);
		void Unbind(Button button, ButtonState state, int gamepad);

		void UnbindAll();

		CommandLayer(const CommandLayer&)				= delete;
		CommandLayer(CommandLayer&&)					= delete;
		CommandLayer& operator=(const CommandLayer&)	= delete;
		CommandLayer& operator=(CommandLayer&&)			= delete;

		~CommandLayer() = default;

	private:
		std::map<std::pair<Key, KeyState>, std::unique_ptr<ICommand>> m_KeyboardCommands;
		std::vector<std::pair<Key, KeyState>> m_KeysToUnbind;

		std::map<std::pair<int, std::pair<Button, ButtonState>>, std::unique_ptr<ICommand>> m_GamepadCommands;
		std::vector<std::pair<int, std::pair<Button, ButtonState>>> m_ButtonsToUnbind;
	};
}

#endif // !__HYPER_COMMAND_LAYER_H__
