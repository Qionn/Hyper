#include "map_parser.h"

#include <hyper/utils/logging.h>

#include <fstream>

using namespace hyper;

namespace burger_time
{
	MapParser::MapParser(std::string_view mapFile)
	{
		std::ifstream file(mapFile.data(), std::ios::binary);
		if (!file.is_open())
		{
			LogWarn("Couldn't open map file '{}'", mapFile);
			return;
		}

		std::string line;
		while (std::getline(file, line))
		{
			ParseLine(line);
		}
	}

	const std::vector<std::string>& MapParser::GetBackgrounds() const
	{
		return m_Backgrounds;
	}

	void MapParser::ParseLine(std::string_view line)
	{
		switch (line[0])
		{
			case 'b':
				ParseBackground(line.substr(2));
				break;
		}
	}

	void MapParser::ParseBackground(std::string_view line)
	{
		m_Backgrounds.emplace_back(line);
	}
}
