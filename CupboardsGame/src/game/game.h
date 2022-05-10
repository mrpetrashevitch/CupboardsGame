#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "config/config.h"
#include "graph/graph.h"
#include "object/chip.h"
#include "object/vertex.h"
#include "object/edge.h"
#include "object/background.h"

namespace game
{
	class game
	{
	public:
		game();
		~game();

		bool init();
		void run();
	private:
		sf::RenderWindow _window;
		sf::Font _font;
		sf::Texture _chip_texture;
		sf::Texture _chip_back_texture;
		sf::Texture _chip_back_blur_texture;
		sf::Texture _background_texture;

		sf::Text _text_game_name;
		sf::Text _text_game_over;
		sf::Text _text_press_start;
		sf::Text _text_next_level;
		sf::Text _text_loading;
		sf::Text _text_total_step;
		sf::Text _text_level;

		sf::Music _music;
		sf::SoundBuffer _sound_select_buffer;
		sf::SoundBuffer _sound_level_complete_buffer;

		graph::graph _graph;
		std::vector<object::vertex> _vertexes;
		std::vector<object::chip> _chips;
		std::vector<object::edge> _edges;
		object::background _background;

		bool _inited;
		bool _load_res();
		bool _load_level(const char* path_config_level);
		bool _check_win();
		float _set_scale(config::game_config& config, const sf::Vector2u& window_size);
		int _on_chip_click(const sf::Vector2f& pos);
		bool _on_vertex_click(const sf::Vector2f& pos, int chip_index);
	};
}