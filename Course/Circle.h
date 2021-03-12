#pragma once
#include "MyShape.h"
#include "CircleMemento.h"

class Circle : public MyShape
{
public:
	explicit Circle(float radius = 0, std::size_t pointCount = 30); 
	void set_radius(float radius);	
	float get_radius() const;
	void set_point_count(std::size_t count);
	std::size_t get_point_count() const override;
	Vector2f get_point(std::size_t index) const override;
	void draw(sf::RenderWindow& window) const override;
	MyShape* clone() const override;
	void move(float offsetX, float offsetY) override; 
	void move(const Vector2f& offset) override;
	void set_memento(const ShapeMemento* memento) override;
	ShapeMemento* create_memento() const override;

private:
	float       radius;
	std::size_t point_count;
};