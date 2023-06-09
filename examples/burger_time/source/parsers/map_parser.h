#ifndef __BURGER_TIME_MAP_PARSER_H__
#define __BURGER_TIME_MAP_PARSER_H__

#include <string>
#include <vector>

namespace burger_time
{
	class MapParser final
	{
	public:
		struct Platform final
		{
			float minX, maxX;
			float height;
		};

		struct Ladder final
		{
			float bottom, top;
			float posX;
		};

	public:
		explicit MapParser(std::string_view mapFile);

		const std::string& GetBackground() const;
		const std::vector<Platform>& GetPlatforms() const;
		const std::vector<Ladder>& GetLadders() const;

		MapParser(const MapParser&)				= default;
		MapParser(MapParser&&)					= default;
		MapParser& operator=(const MapParser&)	= default;
		MapParser& operator=(MapParser&&)		= default;

		~MapParser() = default;

	private:
		std::string m_Background;
		std::vector<Platform> m_Platforms;
		std::vector<Ladder> m_Ladders;

	private:
		void ParseLine(const std::string& line);
		void ParseBackground(const std::string& line);
		void ParsePlatform(const std::string& line);
		void ParseLadder(const std::string& line);
	};
}

#endif // !__BURGER_TIME_MAP_PARSER_H__
