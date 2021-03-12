#include "RectMemento.h"

void RectMemento::set_state(const Color& _f_color, const Color& _b_color, const Color& _out_color,
	float _thickness, float _rotation, const Vector2f& _origin, const Vector2f& _position,
	const Vector2f& _scale, const Vector2f& _size)
{
	ShapeMemento::set_state(_f_color, _b_color, _out_color, _thickness, _rotation,
		_origin, _position, _scale);
	size = _size;
}

const Vector2f& RectMemento::get_size() const
{
	return size;
}

MyShape* RectMemento::create_shape() const
{
	Rectangle* tmp_shape = new Rectangle();
	tmp_shape->set_fill_color(get_fill_color());
	tmp_shape->set_base_color(get_base_color());
	tmp_shape->set_outline_color(get_outline_color());
	tmp_shape->set_outline_thickness(get_outline_thickness());
	tmp_shape->setRotation(get_rotation());
	tmp_shape->setOrigin(get_origin());
	tmp_shape->setPosition(get_position());
	tmp_shape->setScale(get_scale());
	tmp_shape->set_size(get_size());

	return tmp_shape;
}

void RectMemento::save_to_file(std::ostream& strm) const
{
	strm << shape_id() << " ";
	ShapeMemento::save_to_file(strm);
	strm << size.x << " " << size.y << "\n";
}

void RectMemento::restore_from_file(std::istream& strm)
{
	ShapeMemento::restore_from_file(strm);
	float x;
	float y;
	strm >> x >> y;
	size = Vector2f(x, y);
}

const char* RectMemento::shape_id() const
{
	return "rect";
}
