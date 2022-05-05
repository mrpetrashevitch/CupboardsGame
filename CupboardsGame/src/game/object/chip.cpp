#include "chip.h"

chip::chip(const sf::Vector2f& pos, float mult, sf::Sprite sp, sf::Color color) :
	_base(sp),
	_base_back(sp),
	_base_size(40.f * mult, 34.3f * mult),
	_base_back_size(46.f * mult, 39.4f * mult),
	_speed(400.f * mult)
{
	_base.setScale(_base_size.x / sp.getTexture()->getSize().x, _base_size.y / sp.getTexture()->getSize().y);
	_base.setOrigin(sp.getTexture()->getSize().x / 2.f, sp.getTexture()->getSize().y / 2.f);
	_base.setPosition(pos);

	_base_back.setScale(_base_back_size.x / sp.getTexture()->getSize().x, _base_back_size.y / sp.getTexture()->getSize().y);
	_base_back.setOrigin(sp.getTexture()->getSize().x / 2.f, sp.getTexture()->getSize().y / 2.f);
	_base_back.setPosition(pos);

	_color_sel = color;
	_color_norm = color;
	_color_norm.a = 230;
	_base.setColor(_color_norm);

	_color_back_sel = color;
	_color_back_sel.a = 90;
	_color_back_norm = color;
	_color_back_norm.a = 0;
	_base_back.setColor(_color_back_norm);
}

void chip::move_to_dest(const std::vector<sf::Vector2f>& path)
{
	_is_move_dest = true;

	for (auto& i : path)
		_path.push(i);
}

bool chip::on_select(const sf::Vector2f& pos)
{
	if ((_base.getPosition().x - _base_size.x / 2 < pos.x) &&
		(_base.getPosition().x + _base_size.x / 2 > pos.x) &&
		(_base.getPosition().y - _base_size.y / 2 < pos.y) &&
		(_base.getPosition().y + _base_size.y / 2 > pos.y))
	{
		_is_selected = true;
		_base.setColor(_color_sel);
	}
	else
	{
		_is_selected = false;
		_base.setColor(_color_norm);
	}
	return _is_selected;
}

void chip::on_entered(const sf::Vector2f& pos)
{
	if ((_base.getPosition().x - _base_size.x / 2 < pos.x) &&
		(_base.getPosition().x + _base_size.x / 2 > pos.x) &&
		(_base.getPosition().y - _base_size.y / 2 < pos.y) &&
		(_base.getPosition().y + _base_size.y / 2 > pos.y))
	{
		_base_back.setColor(_color_back_sel);
	}
	else
	{
		if (!_is_selected)
			_base_back.setColor(_color_back_norm);
	}
}

void chip::update(float deltaTime)
{
	if (_is_move_dest)
	{
		auto pos = _path.front();
		float dx = pos.x - _base.getPosition().x;
		float dy = pos.y - _base.getPosition().y;
		float distance = std::sqrt(dx * dx + dy * dy);

		if (distance > 10.f)
		{
			float alpha = std::atan2(dy, dx);
			_base.move(_speed * deltaTime * std::cos(alpha), _speed * deltaTime * std::sin(alpha));
			_base_back.move(_speed * deltaTime * std::cos(alpha), _speed * deltaTime * std::sin(alpha));
		}
		else
		{
			_path.pop();
			if (_path.empty())
				_is_move_dest = false;
			_base.setPosition(pos.x, pos.y);
			_base_back.setPosition(pos.x, pos.y);
		}
	}
}

void chip::on_drow(sf::RenderWindow& window)
{
	window.draw(_base_back);
	window.draw(_base);
}

const sf::Vector2f& chip::get_pos()
{
	return _base.getPosition();
}

void chip::set_vertex_index(int vertex_index)
{
	_vertex_index = vertex_index;
}

int chip::get_vertex_index()
{
	return _vertex_index;
}

void chip::set_vertex_dest(int vertex_dest)
{
	_vertex_dest = vertex_dest;
}

int chip::get_vertex_dest()
{
	return _vertex_dest;
}
