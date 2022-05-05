#include "vertex.h"

vertex::vertex(const sf::Vector2f& pos, float mult, sf::Sprite sp, sf::Color color) :
	_base(sp),
	_base_size(70.f * mult, 60.f * mult),
	_base_back(sp),
	_base_back_size(76.f * mult, 65.1f * mult)
{
	_base.setScale(_base_size.x / sp.getTexture()->getSize().x, _base_size.y / sp.getTexture()->getSize().y);
	_base.setOrigin(sp.getTexture()->getSize().x / 2.f, sp.getTexture()->getSize().y / 2.f);
	_base.setPosition(pos.x * mult, pos.y * mult);

	_base_back.setScale(_base_back_size.x / sp.getTexture()->getSize().x, _base_back_size.y / sp.getTexture()->getSize().y);
	_base_back.setOrigin(sp.getTexture()->getSize().x / 2.f, sp.getTexture()->getSize().y / 2.f);
	_base_back.setPosition(pos.x * mult, pos.y * mult);

	set_color(color);
}

vertex::~vertex() 
{

}

void vertex::set_color(sf::Color color)
{
	_color_sel = color;
	_color_norm = color;
	_base.setColor(_color_norm);

	_color_back_sel = color;
	_color_back_sel.a = 100;
	_color_back_norm = color;
	_color_back_norm.a = 0;
	_base_back.setColor(_color_back_norm);
}

sf::Color vertex::get_color()
{
	auto col = _color_norm;
	col.a = 255;
	return col;
}

bool vertex::on_select(const sf::Vector2f& pos)
{
	if ((_base.getPosition().x - _base_size.x / 2 < pos.x) &&
		(_base.getPosition().x + _base_size.x / 2 > pos.x) &&
		(_base.getPosition().y - _base_size.y / 2 < pos.y) &&
		(_base.getPosition().y + _base_size.y / 2 > pos.y))
	{
		_is_selected = true;
	}
	else
	{
		_is_selected = false;
	}
	return _is_selected;
}

void vertex::on_entered(const sf::Vector2f& pos)
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
		if (!_is_flash)
			_base_back.setColor(_color_back_norm);
	}
}

void vertex::set_flash(bool is_flash)
{
	_is_flash = is_flash;

	if (_is_flash)
	{
		_base_back.setColor(_color_back_sel);
	}
	else
	{
		_base_back.setColor(_color_back_norm);
	}
}

void vertex::on_drow(sf::RenderWindow& window)
{
	window.draw(_base_back);
	window.draw(_base);
}

const sf::Vector2f& vertex::get_pos()
{
	return _base.getPosition();
}
