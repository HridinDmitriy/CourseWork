#include "ShapeMemento.h"

ShapeMemento::~ShapeMemento()
{
}

void ShapeMemento::set_state(const Color& _f_color, const Color& _b_color, const Color& _out_color, 
		float _thickness, float _rotation, const Vector2f& _origin, 
		const Vector2f& _position, const Vector2f& _scale) 
{
	fill_color = _f_color;
	base_color = _b_color;
	outline_color = _out_color;
	outline_thickness = _thickness; 
	rotation = _rotation;
	origin = _origin;
	position = _position;
	scale = _scale;
}

const Color& ShapeMemento::get_fill_color() const
{
	return fill_color;
}

const Color& ShapeMemento::get_base_color() const
{
	return base_color;
}

const Color& ShapeMemento::get_outline_color() const
{
	return outline_color;
}

float ShapeMemento::get_outline_thickness() const
{
	return outline_thickness;
}

float ShapeMemento::get_rotation() const
{
	return rotation;
}

const Vector2f& ShapeMemento::get_origin() const
{
	return origin;
}

const Vector2f& ShapeMemento::get_position() const
{
	return position;
}

const Vector2f& ShapeMemento::get_scale() const
{
	return scale;
}

void ShapeMemento::save_to_file(std::ostream& ostrm) const
{
	using uint = unsigned int;
	ostrm << (uint)fill_color.r << " " << (uint)fill_color.g << " " << (uint)fill_color.b << " "
		<< (uint)base_color.r << " " << (uint)base_color.g << " " << (uint)base_color.b << " "
		<< (uint)outline_color.r << " " << (uint)outline_color.g << " " << (uint)outline_color.b << " "
		<< outline_thickness << " " << rotation << " " << origin.x << " " << origin.y << " "
		<< position.x << " " << position.y << " " << scale.x << " " << scale.y << " ";
}

void ShapeMemento::restore_from_file(std::istream& strm)
{
	unsigned int r, g, b;
	float _thickness;
	float _rotation;
	float x, y;

	strm >> r >> g >> b;
	fill_color = Color(r, g, b);

	strm >> r >> g >> b;
	base_color = Color(r, g, b);

	strm >> r >> g >> b;
	outline_color = Color(r, g, b);

	strm >> _thickness;
	outline_thickness = _thickness;

	strm >> _rotation;
	rotation = _rotation;

	strm >> x >> y;
	origin = Vector2f(x, y);

	strm >> x >> y;
	position = Vector2f(x, y);

	strm >> x >> y;
	scale = Vector2f(x, y);
}