#include "map_parser.h"

#include <hyper/utils/logging.h>

#include <fstream>

using namespace hyper;

namespace burger_time
{
	MapParser::MapParser(std::string_view mapFile)
	{
		std::ifstream file(mapFile.data());
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

	const std::string& MapParser::GetBackground() const
	{
		return m_Background;
	}

	const std::vector<MapParser::Platform>& MapParser::GetPlatforms() const
	{
		return m_Platforms;
	}

	const std::vector<MapParser::Ladder>& MapParser::GetLadders() const
	{
		return m_Ladders;
	}

	void MapParser::ParseLine(const std::string& line)
	{
		switch (line[0])
		{
			case 'b':
				ParseBackground(line.substr(2));
				break;

			case 'p':
				ParsePlatform(line.substr(2));
				break;

			case 'l':
				ParseLadder(line.substr(2));
				break;
		}
	}

	void MapParser::ParseBackground(const std::string& line)
	{
		m_Background = line;
	}

	void MapParser::ParsePlatform(const std::string& line)
	{
		Platform platform;

		size_t idx1 = line.find_first_of(',');
		platform.minX = std::stof(line.substr(0, idx1));

		size_t idx2 = line.find_first_of(',', idx1 + 1);
		platform.maxX = std::stof(line.substr(idx1 + 1, idx2 - idx1));

		platform.height = std::stof(line.substr(idx2 + 1));

		m_Platforms.push_back(platform);
	}

	void MapParser::ParseLadder(const std::string& line)
	{
		Ladder ladder;

		size_t idx1 = line.find_first_of(',');
		ladder.bottom = std::stof(line.substr(0, idx1));

		size_t idx2 = line.find_first_of(',', idx1 + 1);
		ladder.top = std::stof(line.substr(idx1 + 1, idx2 - idx1));

		ladder.posX = std::stof(line.substr(idx2 + 1));

		m_Ladders.push_back(ladder);
	}
}
