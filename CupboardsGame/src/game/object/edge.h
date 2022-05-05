#pragma once
#include "../../CupboardsGame/build_config.h"
#include <SFML/Graphics.hpp>
#include <cmath>

namespace game::object
{
	class edge
	{
	public:
		edge(const sf::Vector2f& pos_s, const sf::Vector2f& pos_d, float mult);
		~edge();
		void on_drow(sf::RenderWindow& window);
	private:
		sf::RectangleShape _base;
		sf::Vector2f _base_size;
	};
}