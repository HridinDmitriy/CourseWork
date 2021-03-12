#include "Pentagon.h"

Pentagon::Pentagon(float radius)
{
	set_radius(radius);
}

void Pentagon::set_radius(float _radius)
{
	radius = _radius;
	update_all();
}

float Pentagon::get_radius() const
{
	return radius;
}

std::size_t Pentagon::get_point_count() const
{
	return 5;
}

Vector2f Pentagon::get_point(std::size_t index) const
{
	static const float pi = 3.141592654f;

	float angle = index * 2 * pi / 5 - pi / 2;
	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;

	return Vector2f(radius + x, radius + y);
}

void Pentagon::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

MyShape* Pentagon::clone() const
{
	Pentagon* pent_copy = new Pentagon();

	pent_copy->setOrigin(getOrigin());
	pent_copy->setPosition(getPosition());
	pent_copy->setRotation(getRotation());
	pent_copy->setScale(getScale());
	pent_copy->set_fill_color(get_fill_color());
	pent_copy->set_base_color(get_base_color());
	pent_copy->set_outline_color(get_outline_color());
	pent_copy->set_outline_thickness(get_outline_thickness());
	pent_copy->set_radius(get_radius());

	return pent_copy;
}

void Pentagon::move(float offsetX, float offsetY)
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

void Pentagon::move(const Vector2f & offset)
{
	move(offset.x, offset.y);
}

ShapeMemento* Pentagon::create_memento() const
{
	PentagonMemento* tmp_memento = new PentagonMemento();
	tmp_memento->set_state(get_fill_color(), get_base_color(), get_outline_color(), get_outline_thickness(),
		getRotation(), getOrigin(), getPosition(), getScale(), get_radius());
	return tmp_memento;
}

void Pentagon::set_memento(const ShapeMemento* memento)
{
	MyShape::set_memento(memento);
	set_radius(((Pentagon*)memento)->radius);
}