#include "pch.h"
#include "CircleWithBaseColor.h"

CircleWithBaseColor::CircleWithBaseColor(float radius, int pointCount)
	: sf::CircleShape::CircleShape(radius, pointCount)
{ }

CircleWithBaseColor::CircleWithBaseColor() : sf::CircleShape::CircleShape()
{ }

CircleWithBaseColor::~CircleWithBaseColor()
{ }

sf::Color CircleWithBaseColor::get_base_color()
{
	return base_color;
}
void CircleWithBaseColor::set_base_color(const sf::Color& color)
{
	base_color = color;
}
