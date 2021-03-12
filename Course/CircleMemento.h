#pragma once
#include "ShapeMemento.h"
#include "Circle.h"

class CircleMemento : public ShapeMemento
{
public:
	friend class Circle;
	void save_to_file(std::ostream& strm) const override;
	void restore_from_file(std::istream& strm) override;

protected:
	void set_state(const Color&, const Color&, const Color&, float, float,
		const Vector2f&, const Vector2f&, const Vector2f&, float, size_t); 

	float get_radius() const;
	size_t get_point_count() const;

	MyShape* create_shape() const override;
	const char* shape_id() const override;

private:
	float radius;
	size_t point_count;
};

