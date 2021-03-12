#pragma once
#include "MyShape.h"
#include "RectMemento.h"

class Rectangle : public MyShape
{
public:
	explicit Rectangle(const Vector2f& size = Vector2f(0, 0));
	void set_size(const Vector2f& size);
	const Vector2f& get_size() const;
	virtual std::size_t get_point_count() const;
	virtual Vector2f get_point(std::size_t index) const;
	void draw(sf::RenderWindow& window) const override;
	MyShape* clone() const override;
	void move(float offsetX, float offsetY) override;
	void move(const Vector2f& offset) override;
	void set_memento(const ShapeMemento* memento) override;
	ShapeMemento* create_memento() const override;

private:
	Vector2f size; 
};

