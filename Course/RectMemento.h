#pragma once
#include "ShapeMemento.h"
#include "Rectangle.h"

class RectMemento :	public ShapeMemento
{
public:
	friend class Rectangle; 
	void save_to_file(std::ostream& strm) const override;
	void restore_from_file(std::istream& strm) override;
	 
protected:   
	void set_state(const Color&, const Color&, const Color&, float, float,
		const Vector2f&, const Vector2f&, const Vector2f&, const Vector2f&);  

	const Vector2f& get_size() const;

	MyShape* create_shape() const override;
	const char* shape_id() const override;

private:
	Vector2f size;
};

