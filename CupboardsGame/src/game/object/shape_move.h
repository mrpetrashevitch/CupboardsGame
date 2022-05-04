#pragma once
#include "../../CupboardsGame/build_config.h"
#include <SFML/Graphics.hpp>
#include <queue>

class shape_move
{
public:
	shape_move(const sf::Vector2f& pos, float mult, sf::Sprite sp, sf::Color color = sf::Color::Transparent);;
	~shape_move() {};
	void move_to_dest(const std::vector<sf::Vector2f>& path);
	bool on_select(const sf::Vector2f& pos);
	void on_entered(const sf::Vector2f& pos);
	void update(float dt_time);
	void on_drow(sf::RenderWindow& window);
	const sf::Vector2f& get_pos();
	void set_vertex_index(int vertex_index);
	int get_vertex_index();
	void set_vertex_dest(int vertex_dest);
	int get_vertex_dest();
private:
	float _speed = 0.f;
	bool _is_move_dest = false;
	bool _is_selected = false;
	int _vertex_index = -1;
	int _vertex_dest = -1;
	std::queue<sf::Vector2f> _path;

	sf::Sprite _base;
	sf::Vector2f _base_size;
	sf::Color _color_norm;
	sf::Color _color_sel;

	sf::Sprite _base_back;
	sf::Vector2f _base_back_size;
	sf::Color _color_back_norm;
	sf::Color _color_back_sel;
};

