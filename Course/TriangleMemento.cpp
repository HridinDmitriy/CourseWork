#include "TriangleMemento.h"

void TriangleMemento::set_state(const Color& _f_color, const Color& _b_color, const Color& _out_color,
	float _thickness, float _rotation, const Vector2f& _origin, const Vector2f& _position,
	const Vector2f& _scale, float _radius)
{
	ShapeMemento::set_state(_f_color, _b_color, _out_color, _thickness, _rotation,
		_origin, _position, _scale);
	radius = _radius;
}

float TriangleMemento::get_radius() const
{
	return radius;
}

MyShape* TriangleMemento::create_shape() const
{
	Triangle* tmp_shape = new Triangle();
	tmp_shape->set_fill_color(get_fill_color());
	tmp_shape->set_base_color(get_base_color());
	tmp_shape->set_outline_color(get_outline_color());
	tmp_shape->set_outline_thickness(get_outline_thickness());
	tmp_shape->setRotation(get_rotation());
	tmp_shape->setOrigin(get_origin());
	tmp_shape->setPosition(get_position());
	tmp_shape->setScale(get_scale());
	tmp_shape->set_radius(get_radius());

	return tmp_shape;
}

void TriangleMemento::save_to_file(std::ostream& strm) const
{
	strm << shape_id() << " ";
	ShapeMemento::save_to_file(strm);
	strm << radius << "\n"; 
}

void TriangleMemento::restore_from_file(std::istream& strm)
{
	ShapeMemento::restore_from_file(strm);
	float _radius;
	strm >> _radius;
	radius = _radius;
}

const char* TriangleMemento::shape_id() const
{
	return "triang";
}

