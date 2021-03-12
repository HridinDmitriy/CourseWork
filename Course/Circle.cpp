#include "Circle.h"

Circle::Circle(float _radius, std::size_t _point_count)
	: radius(_radius), point_count(_point_count)
{
	update_all();  
}

void Circle::set_radius(float _radius)
{
	radius = _radius;
	update_all();
}


float Circle::get_radius() const
{
	return radius;
}

void Circle::set_point_count(std::size_t _point_count)
{
	point_count = _point_count;
	update_all();
}

std::size_t Circle::get_point_count() const
{
	return point_count;
}

Vector2f Circle::get_point(std::size_t _index) const
{
	static const float pi = 3.141592654f;     

	float angle = _index * 2 * pi / point_count - pi / 2;
	float x = std::cos(angle) * radius;
	float y = std::sin(angle) * radius;

	return Vector2f(radius + x, radius + y);
}

void Circle::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

MyShape* Circle::clone() const
{
	Circle* circle_copy = new Circle();

	circle_copy->setOrigin(getOrigin());
	circle_copy->setPosition(getPosition());
	circle_copy->setRotation(getRotation());
	circle_copy->setScale(getScale());
	circle_copy->set_fill_color(get_fill_color());
	circle_copy->set_base_color(get_base_color());
	circle_copy->set_outline_color(get_outline_color());
	circle_copy->set_outline_thickness(get_outline_thickness());
	circle_copy->set_point_count(get_point_count());
	circle_copy->set_radius(get_radius());

	return circle_copy;
}

void Circle::move(float offsetX, float offsetY)
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

void Circle::move(const Vector2f& offset)
{
	move(offset.x, offset.y);
}

ShapeMemento* Circle::create_memento() const
{
	CircleMemento* tmp_memento = new CircleMemento();
	tmp_memento->set_state(get_fill_color(), get_base_color(), get_outline_color(), get_outline_thickness(),
		getRotation(), getOrigin(), getPosition(), getScale(), get_radius(), get_point_count());
	return tmp_memento;
}

void Circle::set_memento(const ShapeMemento* memento)
{
	MyShape::set_memento(memento);
	set_radius(((CircleMemento*)memento)->radius);
	set_point_count(((CircleMemento*)memento)->point_count);
}