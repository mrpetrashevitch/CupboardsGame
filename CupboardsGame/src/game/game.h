#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "config/config.h"
#include "graph/graph.h"
#include "object/chip.h"
#include "object/vertex.h"
#include "object/edge.h"

#include <tuple>

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
	sf::Music _music;
	sf::Texture _chip_texture;
	sf::Texture _chip_back_texture;
	sf::Texture _chip_back_blur_texture;
	sf::Texture _background_texture;
	sf::Sprite _background;
	sf::Text _text_game_name;
	sf::Text _text_press_start;
	sf::Text _text_next_level;
	sf::Text _text_loading;
	sf::Text _text_total_step;
	sf::Text _text_level;
	
	graph _graph;
	std::vector<vertex> _vertexes;
	std::vector<chip> _chips;
	std::vector<edge> _edges;

	bool _inited;
	bool _load_res();
	bool _load_level(const char* path_config_level);
	bool _check_win();
	std::tuple<float, float, float> _get_scale(const game_config& config, const sf::Vector2u& window_size);
	int _on_chip_click(const sf::Vector2f& pos);
	bool _on_vertex_click(const sf::Vector2f& pos, int chip_index);
};

