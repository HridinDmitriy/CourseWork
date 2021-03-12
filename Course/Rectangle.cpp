#include "Rectangle.h"

Rectangle::Rectangle(const Vector2f& _size)
{
	set_size(_size);
}

void Rectangle::set_size(const Vector2f& _size)
{
	size = _size;
	update_all();
} 

const Vector2f& Rectangle::get_size() const
{
	return size;
}

std::size_t Rectangle::get_point_count() const
{
	return 4;
}

Vector2f Rectangle::get_point(std::size_t _index) const
{
	switch (_index)
	{
	default:
	case 0: return Vector2f(0, 0);
	case 1: return Vector2f(size.x, 0);
	case 2: return Vector2f(size.x, size.y);
	case 3: return Vector2f(0, size.y);
	}
}

void Rectangle::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

MyShape* Rectangle::clone() const
{
	Rectangle* rectangle_copy = new Rectangle();

	rectangle_copy->setOrigin(getOrigin());
	rectangle_copy->setPosition(getPosition());
	rectangle_copy->setRotation(getRotation());
	rectangle_copy->setScale(getScale());
	rectangle_copy->set_fill_color(get_fill_color());
	rectangle_copy->set_base_color(get_base_color());
	rectangle_copy->set_outline_color(get_outline_color());
	rectangle_copy->set_outline_thickness(get_outline_thickness());
	rectangle_copy->set_size(get_size());

	return rectangle_copy;
}

void Rectangle::move(float offsetX, float offsetY)
{
	Transformable::move(offsetX, offsetY);

	if (getPosition().x <= 0)
	{
		setPosition(WINDOW_WIDTH, getPosition().y);
	}
	else if (getPosition().x >= WINDOW_WIDTH)
	{
		setPosition(0, getPosition().y);
	}
	else if (getPosition().y <= 0)
	{
		setPosition(getPosition().x, WINDOW_HEIGHT);
	}
	else if (getPosition().y >= WINDOW_HEIGHT)
	{
		setPosition(getPosition().x, 0);
	}
}

void Rectangle::move(const Vector2f & offset)
{
	move(offset.x, offset.y);
}

ShapeMemento* Rectangle::create_memento() const
{
	RectMemento* tmp_memento = new RectMemento();
	tmp_memento->set_state(get_fill_color(), get_base_color(), get_outline_color(), get_outline_thickness(),
		getRotation(), getOrigin(), getPosition(), getScale(), get_size());
	return tmp_memento;
}

void Rectangle::set_memento(const ShapeMemento* memento)
{
	MyShape::set_memento(memento);
	set_size(((Rectangle*)memento)->size);
}