#ifndef __BURGER_TIME_MAP_PARSER_H__
#define __BURGER_TIME_MAP_PARSER_H__

#include <string>
#include <vector>

namespace burger_time
{
	class MapParser final
	{
	public:
		explicit MapParser(std::string_view mapFile);

		const std::vector<std::string>& GetBackgrounds() const;

		MapParser(const MapParser&)				= default;
		MapParser(MapParser&&)					= default;
		MapParser& operator=(const MapParser&)	= default;
		MapParser& operator=(MapParser&&)		= default;

		~MapParser() = default;

	private:
		std::vector<std::string> m_Backgrounds;

	private:
		void ParseLine(std::string_view line);
		void ParseBackground(std::string_view line);
	};
}

#endif // !__BURGER_TIME_MAP_PARSER_H__
