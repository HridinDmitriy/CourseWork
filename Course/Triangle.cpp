#include "Triangle.h"

Triangle::Triangle(float radius)
{
	set_radius(radius); 
}

void Triangle::set_radius(float _radius)
{
	radius = _radius;
	update_all();
}

float Triangle::get_radius() const
{
	return radius; 
}

std::size_t Triangle::get_point_count() const
{
	return 3;
}

Vector2f Triangle::get_point(std::size_t index) const
{
	static const float pi = 3.141592654f;

	float angle = index * 2 * pi / 3 - pi / 2;
	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;

	return Vector2f(radius + x, radius + y);
}

void Triangle::draw(sf::RenderWindow & window) const
{
	window.draw(*this);
}

MyShape* Triangle::clone() const
{
	Triangle* triangle_copy = new Triangle();

	triangle_copy->setOrigin(getOrigin());
	triangle_copy->setPosition(getPosition());
	triangle_copy->setRotation(getRotation());
	triangle_copy->setScale(getScale());
	triangle_copy->set_fill_color(get_fill_color());
	triangle_copy->set_base_color(get_base_color());
	triangle_copy->set_outline_color(get_outline_color());
	triangle_copy->set_outline_thickness(get_outline_thickness());
	triangle_copy->set_radius(get_radius());

	return triangle_copy;
}

void Triangle::move(float offsetX, float offsetY)
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

void Triangle::move(const Vector2f& offset)
{
	move(offset.x, offset.y);
}

ShapeMemento* Triangle::create_memento() const
{
	TriangleMemento* tmp_memento = new TriangleMemento();
	tmp_memento->set_state(get_fill_color(), get_base_color(), get_outline_color(), get_outline_thickness(),
		getRotation(), getOrigin(), getPosition(), getScale(), get_radius());
	return tmp_memento;
}

void Triangle::set_memento(const ShapeMemento* memento)
{
	MyShape::set_memento(memento);
	set_radius(((Triangle*)memento)->radius);
}