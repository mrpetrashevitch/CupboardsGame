#include "background.h"

namespace game::object
{
	background::background()
	{

	}
	background::~background()
	{

	}
	void background::set_sprite(const sf::Sprite& sp)
	{
		_base = sp;
		_base_scale = _base.getScale();
	}
	void background::update(float dt_time)
	{
		auto curr = _base.getScale();
		auto val = _base_scale - curr;
		if (_up && val.x < -0.20f)
			_up = false;

		if(!_up && val.x > 0.0f)
			_up = true;

		if (_up)
			_base.setScale(curr.x + (_speed * dt_time), curr.y + (_speed * dt_time));
		else
			_base.setScale(curr.x - (_speed * dt_time), curr.y - (_speed * dt_time));
	}

	void background::on_drow(sf::RenderWindow& window)
	{
		window.draw(_base);
	}

}