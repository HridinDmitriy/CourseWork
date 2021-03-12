#include "CompositeMemento.h"

CompositeMemento::CompositeMemento()
{
	mementos = new std::list<ShapeMemento*>; 
}

CompositeMemento::~CompositeMemento()
{
	clear();
	delete mementos;
	mementos = nullptr;
}

void CompositeMemento::clear()
{
	for (ShapeMemento* shape : *mementos)
	{
		delete shape;
	}
	mementos->clear();
}

void CompositeMemento::add_memento(ShapeMemento* sh_memento)
{
	mementos->push_back(sh_memento);
}

MyShape* CompositeMemento::create_shape() const
{
	Composite* tmp_shape = new Composite();

	for (auto shape : *mementos)
	{
		tmp_shape->add_shape(shape->create_shape()); 
	}  
	return tmp_shape;
}

void CompositeMemento::save_to_file(std::ostream& strm) const
{
	strm << shape_id() << "\n";
	for (ShapeMemento* shape : *mementos)
	{
		shape->save_to_file(strm); 
	}
	strm << "/" << shape_id() << "\n";
}

void CompositeMemento::restore_from_file(std::istream& strm) 
{
	clear();  
	std::string shape_id;
	
	while (true)
	{
		strm >> shape_id;
		if (shape_id == "composite")
		{
			CompositeMemento* comp_memento = new CompositeMemento();
			comp_memento->restore_from_file(strm);
			mementos->push_back(comp_memento);   
		}
		else if (shape_id == "circle")
		{
			CircleMemento* circle_memento = new CircleMemento();
			circle_memento->restore_from_file(strm);
			mementos->push_back(circle_memento);
		}
		else if (shape_id == "rect")
		{
			RectMemento* rect_memento = new RectMemento();
			rect_memento->restore_from_file(strm);
			mementos->push_back(rect_memento);
		}
		else if (shape_id == "triang")
		{
			TriangleMemento* triang_memento = new TriangleMemento();
			triang_memento->restore_from_file(strm);
			mementos->push_back(triang_memento);
		}
		else if (shape_id == "pent")
		{
			PentagonMemento* pent_memento = new PentagonMemento();
			pent_memento->restore_from_file(strm);
			mementos->push_back(pent_memento);
		}
		else if (shape_id == "/composite")
		{
			break;
		}
		else
		{
			std::cout << "\n>>> ÁÛË ÂÑÒĞÅ×ÅÍ ÍÅÈÇÂÅÑÒÛÉ ÈÄÅÍÒÈÔÈÊÀÒÎĞ ÔÈÃÓĞÛ!\n\n";
			// ïğîïóñêàåì ñòğîêó
			std::getline(strm, shape_id);
		}
	} 
}

const char* CompositeMemento::shape_id() const
{
	return "composite";
}