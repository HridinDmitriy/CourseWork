#include "CircleMemento.h"

void CircleMemento::set_state(const Color& _f_color, const Color& _b_color, const Color& _out_color,
		float _thickness, float _rotation, const Vector2f& _origin, const Vector2f& _position,
		const Vector2f& _scale, float _radius, size_t _point_count)
{
	ShapeMemento::set_state(_f_color, _b_color, _out_color, _thickness, _rotation, 
		_origin, _position, _scale);  
	radius = _radius;
	point_count = _point_count;
}

float CircleMemento::get_radius() const
{
	return radius;
}

size_t CircleMemento::get_point_count() const
{
	return point_count;
}

MyShape* CircleMemento::create_shape() const
{
	Circle* tmp_shape = new Circle(); 
	tmp_shape->set_fill_color(get_fill_color());
	tmp_shape->set_base_color(get_base_color());
	tmp_shape->set_outline_color(get_outline_color());
	tmp_shape->set_outline_thickness(get_outline_thickness());
	tmp_shape->setRotation(get_rotation());
	tmp_shape->setOrigin(get_origin());
	tmp_shape->setPosition(get_position());
	tmp_shape->setScale(get_scale());
	tmp_shape->set_radius(get_radius());
	tmp_shape->set_point_count(get_point_count());

	return tmp_shape;
}

void CircleMemento::save_to_file(std::ostream& strm) const
{
	strm << shape_id() << " ";
	ShapeMemento::save_to_file(strm);
	strm << radius << " " << point_count << "\n";
}

void CircleMemento::restore_from_file(std::istream& strm)
{
	ShapeMemento::restore_from_file(strm);
	float _radius;
	size_t _point_count;
	strm >> _radius;
	strm >> _point_count;
	radius = _radius;
	point_count = _point_count;
}

const char* CircleMemento::shape_id() const
{
	return "circle";  
}