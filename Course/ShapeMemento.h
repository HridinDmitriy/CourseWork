#pragma once
#include "SFML/Graphics/Color.hpp" 
#include "SFML/Graphics.hpp" 
#include <fstream>
using namespace sf;

class MyShape;

class ShapeMemento
{
public:
	virtual ~ShapeMemento();
	virtual void save_to_file(std::ostream& strm) const;  
	virtual void restore_from_file(std::istream& strm);
	friend class MyShape;
	friend class Composite;
	friend class CompositeMemento;

protected:
	void set_state(const Color&, const Color&, const Color&, 
		float, float, const Vector2f&, const Vector2f&, const Vector2f&); 

	const Color& get_fill_color() const;
	const Color& get_base_color() const;
	const Color& get_outline_color() const;
	float get_outline_thickness() const;
	float get_rotation() const;
	const Vector2f& get_origin() const;
	const Vector2f& get_position() const;
	const Vector2f& get_scale() const;

	virtual MyShape* create_shape() const = 0;
	virtual const char* shape_id() const = 0;

private:
	Color fill_color;
	Color base_color;
	Color outline_color;
	float outline_thickness;
	float rotation;
	Vector2f origin;
	Vector2f position;                                   
	Vector2f scale;
};

