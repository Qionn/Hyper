#ifndef __BURGER_TIME_MOVE_COMMAND_H__
#define __BURGER_TIME_MOVE_COMMAND_H__

#include <glm/vec2.hpp>

#include <hyper/utils/command.h>

#include "components/character_component.h"

namespace burger_time
{
	class MoveCommand final : public hyper::ICommand
	{
	public:
		MoveCommand(CharacterComponent* pCharachter, const glm::vec2& direction);
		void Execute() override;

	private:
		CharacterComponent* m_pCharacter;
		glm::vec2 m_Direction;
	};
}

#endif // !__BURGER_TIME_MOVE_COMMAND_H__
