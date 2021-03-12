#pragma once
#include "CircleMemento.h"
#include "RectMemento.h"
#include "TriangleMemento.h"
#include "PentagonMemento.h"
#include "Composite.h"
#include <list>
#include <iostream>
#include <string>

class CompositeMemento : public ShapeMemento 
{
public:
	friend class Composite;
	CompositeMemento();
	~CompositeMemento();
	CompositeMemento(const CompositeMemento& composite) = delete;
	CompositeMemento& operator=(const CompositeMemento& composite) = delete;
	void save_to_file(std::ostream& strm) const override;
	void restore_from_file(std::istream& strm) override;

protected:
	void add_memento(ShapeMemento* sh_memento);
	MyShape* create_shape() const override;
	void clear();
	const char* shape_id() const override;

private:
	std::list<ShapeMemento*>* mementos; 
};

