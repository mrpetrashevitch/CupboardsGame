#pragma once
#include "../../CupboardsGame/build_config.h"
#include <SFML/Graphics.hpp>

namespace game::object
{
	class background
	{
	public:
		background();
		~background();
		void set_sprite(const sf::Sprite& sp);
		void update(float dt_time);
		void on_drow(sf::RenderWindow& window);
	private:
		sf::Vector2f _base_scale;
		float _speed = 0.01f;
		bool _up = true;
		sf::Sprite _base;
	};
}

