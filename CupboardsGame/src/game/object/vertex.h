#pragma once
#include "../../CupboardsGame/build_config.h"
#include <SFML/Graphics.hpp>

namespace game::object
{
	class vertex
	{
	public:
		vertex(const sf::Vector2f& pos, float mult, sf::Sprite sp, sf::Color color = sf::Color::Transparent);;
		~vertex();;
		void set_color(sf::Color color);
		sf::Color get_color();
		bool on_select(const sf::Vector2f& pos);
		void on_entered(const sf::Vector2f& pos);
		void set_flash(bool is_flash);
		void on_drow(sf::RenderWindow& window);
		const sf::Vector2f& get_pos();
	private:
		sf::Sprite _base;
		sf::Vector2f _base_size;
		sf::Color _color_norm;
		sf::Color _color_sel;

		sf::Sprite _base_back;
		sf::Vector2f _base_back_size;
		sf::Color _color_back_norm;
		sf::Color _color_back_sel;

		bool _is_selected = false;
		bool _is_flash = false;
	};
}