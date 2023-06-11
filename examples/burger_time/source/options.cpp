#include "options.h"

#include <hyper/input/input.h>
#include <hyper/input/keyboard.h>
#include <hyper/utils/logging.h>

using namespace hyper;

namespace burger_time
{
	void SetupOptions(const Input& input)
	{
		Options::keys.menuUp		= Key::eUp;
		Options::keys.menuDown		= Key::eDown;
		Options::keys.menuSelect	= Key::eEnter;
		Options::keys.menuReturn	= Key::eEscape;
		Options::keys.pause			= Key::eEscape;

		const Keyboard& kb = input.GetKeyboard();

		if (kb.IsAzerty())
		{
			LogInfo("Using AZERTY keyboard layout");

			Options::keys.characterUp		= Key::eZ;
			Options::keys.characterDown		= Key::eS;
			Options::keys.characterLeft		= Key::eQ;
			Options::keys.characterRight	= Key::eD;
		}
		else
		{
			LogInfo("Using QWERTY keyboard layout");

			Options::keys.characterUp		= Key::eW;
			Options::keys.characterDown		= Key::eS;
			Options::keys.characterLeft		= Key::eA;
			Options::keys.characterRight	= Key::eD;
		}
	}
}
