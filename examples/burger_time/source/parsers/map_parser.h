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

		struct Ingredient final
		{
			float posX, posY;
			int type;
		};

		struct Catcher final
		{
			float posX, posY;
		};

	public:
		explicit MapParser(std::string_view mapFile);

		const std::string& GetBackground() const;
		const std::vector<Platform>& GetPlatforms() const;
		const std::vector<Ladder>& GetLadders() const;
		const std::vector<Ingredient>& GetIngredients() const;
		const std::vector<Catcher>& GetCatchers() const;

		MapParser(const MapParser&)				= default;
		MapParser(MapParser&&)					= default;
		MapParser& operator=(const MapParser&)	= default;
		MapParser& operator=(MapParser&&)		= default;

		~MapParser() = default;

	private:
		std::string m_Background;
		std::vector<Platform> m_Platforms;
		std::vector<Ladder> m_Ladders;
		std::vector<Ingredient> m_Ingredients;
		std::vector<Catcher> m_Catchers;

	private:
		void ParseLine(const std::string& line);
		void ParseBackground(const std::string& line);
		void ParsePlatform(const std::string& line);
		void ParseLadder(const std::string& line);
		void ParseIngredient(const std::string& line);
		void ParseCatcher(const std::string& line);
	};
}

#endif // !__BURGER_TIME_MAP_PARSER_H__
