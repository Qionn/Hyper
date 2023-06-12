#include "move_command.h"

namespace burger_time
{
	MoveCommand::MoveCommand(CharacterComponent* pCharachter, const glm::vec2& direction)
		: m_pCharacter{ pCharachter }, m_Direction{ direction }
	{

	}

	void MoveCommand::Execute()
	{
		m_pCharacter->Move(m_Direction);
	}
}
