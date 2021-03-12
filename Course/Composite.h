#pragma once
#include <list>
#include "MyShape.h"
#include "CompositeMemento.h"
 
class Composite : public MyShape
{
public:
	Composite();
	Composite(const Composite& composite); 
	~Composite();   
	Composite& operator=(const Composite& composite); 
	void add_shape(MyShape* shape);
	void remove_selected_shapes();
	void select_shape(sf::Vector2i mouse_position);
	void compose_selected_shapes();
	void change_color_after_collision();
	void resize_shapes();   
	void remove_selecting();
	MyShape* get_selected_shape() const;
	void set_fill_color(const Color& color) override;
	void set_outline_color(const Color& color) override;
	void set_outline_thickness(float thickness) override;
	const Color& get_outline_color() const override;
	float get_outline_thickness() const override;
	void restore_color() override;
	bool contains(const Vector2f& point) const override;
	FloatRect get_global_bounds() const override;
	void setRotation(float angle) override;
	void setScale(float factorX, float factorY) override;
	void setScale(const Vector2f& factors) override;
	void move(float offsetX, float offsetY) override;
	void move(const Vector2f& offset) override;
	void auto_move(float speed, Clock& clock) override;  
	void rotate(float angle) override;
	void scale(float factorX, float factorY) override;
	void scale(const Vector2f& factor) override;
	void set_memento(const ShapeMemento* memento) override;
	ShapeMemento* create_memento() const override;

	void draw(sf::RenderWindow& window) const override;
	MyShape* clone() const override;
	std::size_t get_point_count() const override;
	size_t size() const;
	void clear(); 

private:
	using MyShape::get_local_bounds;
	using MyShape::set_base_color;
	using MyShape::get_fill_color;
	using Transformable::setPosition; 
	using Transformable::setOrigin;
	using Transformable::getPosition;
	using Transformable::getRotation;
	using Transformable::getScale;
	using Transformable::getOrigin;
	using Transformable::getTransform;
	using Transformable::getInverseTransform;
	sf::Vector2f get_point(std::size_t index) const override;
	
	enum ShapeSize
	{
		Small,
		Medium,
		Big
	};

public:
	const float OUTLINE_THICKNESS = 5.0f;
	const Color OUTLINE_COLOR = Color(0, 255, 255);

private:
	std::list<MyShape*>* composite_shape;
	ShapeSize sh_size;
}; 

