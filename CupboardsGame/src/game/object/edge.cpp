#include "edge.h"

edge::edge(const sf::Vector2f& pos_s, const sf::Vector2f& pos_d, float mult)
{
	auto dt = pos_s - pos_d;

	float distance = std::sqrt(dt.x * dt.x + dt.y * dt.y);
	float alpha = std::atan2(dt.y, dt.x) * 180 / 3.14159f;

	_base_size = { distance, 5 * mult };
	_base.setSize(_base_size);
	_base.setFillColor(sf::Color::Color(123, 123, 123));
	_base.setOrigin(_base_size / 2.f);
	_base.setPosition((pos_s.x + pos_d.x) / 2, (pos_s.y + pos_d.y) / 2);
	_base.setRotation(alpha);
}

edge::~edge()
{

}

void edge::on_drow(sf::RenderWindow& window)
{
	window.draw(_base);
}
