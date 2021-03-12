#pragma once
#include "SFML/Graphics.hpp"

class CircleWithBaseColor : public sf::CircleShape
{
public:  
	CircleWithBaseColor();
	CircleWithBaseColor(float radius, int pointCount); 
	~CircleWithBaseColor(); 
	sf::Color get_base_color();
	void set_base_color(const sf::Color& color);
	
private:
	sf::Color base_color;
};