#include "Composite.h"
#include <unordered_map>

Composite::Composite()
	: sh_size(ShapeSize::Medium)
{ 
	composite_shape = new std::list<MyShape*>(); 
}

Composite::~Composite() 
{
	clear(); 
	delete composite_shape;
	composite_shape = nullptr;
}

Composite::Composite(const Composite& composite)
{
	composite_shape = ((Composite*)composite.clone())->composite_shape; 
	sh_size = composite.sh_size;
}

Composite& Composite::operator=(const Composite& composite)
{
	if (this != &composite)
	{
		this->~Composite(); 
		composite_shape = ((Composite*)composite.clone())->composite_shape;
		sh_size = composite.sh_size;
	}
	return *this;
}

void Composite::add_shape(MyShape* shape)
{
	composite_shape->push_back(shape);
}

void Composite::remove_selected_shapes()
{
	for (auto iter = composite_shape->begin(); iter != composite_shape->end();)  
	{
		if ((*iter)->get_outline_color() == OUTLINE_COLOR &&
			(*iter)->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			delete *iter; 
			iter = composite_shape->erase(iter);  
		}
		else
		{
			++iter;
		}
	}
}

void Composite::select_shape(sf::Vector2i mouse_position)
{
	for (auto shape : *composite_shape)
	{
		if (shape->contains(Vector2f((float)mouse_position.x, (float)mouse_position.y))) 
		{
			if (shape->get_outline_thickness() == OUTLINE_THICKNESS &&
				shape->get_outline_color() == OUTLINE_COLOR)
			{
				shape->set_outline_thickness(0.0f); 
			} 
			else if (shape->get_outline_thickness() == OUTLINE_THICKNESS)
			{
				shape->set_outline_color(OUTLINE_COLOR);
			}
			else if (shape->get_outline_color() == OUTLINE_COLOR)
			{
				shape->set_outline_thickness(OUTLINE_THICKNESS);
			}
			else
			{
				shape->set_outline_thickness(OUTLINE_THICKNESS);
				shape->set_outline_color(OUTLINE_COLOR);
			}
			break;
		}
	}
}

void Composite::compose_selected_shapes()
{
	Composite* new_composite = new Composite();

	for (auto iter = composite_shape->begin(); iter != composite_shape->end();)
	{
		if ((*iter)->get_outline_color() == OUTLINE_COLOR &&
			(*iter)->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			new_composite->add_shape(*iter); 
			iter = composite_shape->erase(iter);
		}
		else
		{
			++iter;
		}
	}

	if (new_composite->size())
	{
		add_shape(new_composite);
	}
	else
	{
		delete new_composite;
	}
}

void Composite::change_color_after_collision()
{
	std::unordered_map<MyShape*, FloatRect> bounds;
	for (auto shape : *composite_shape)
	{
		bounds.insert(std::make_pair(shape, shape->get_global_bounds())); 
	}

	for (auto shp1 : *composite_shape)
	{
		for (auto shp2 : *composite_shape)
		{
			if (shp1 != shp2 && bounds[shp1].intersects(bounds[shp2]))  
			{
				shp2->set_fill_color(sf::Color::Red); 
			}
		}
	}
}

void Composite::resize_shapes()
{
	switch (sh_size)
	{
	case ShapeSize::Small:
		for (auto shape : *composite_shape)
		{
			if (shape->get_outline_color() == OUTLINE_COLOR &&
				shape->get_outline_thickness() == OUTLINE_THICKNESS)
			{
				shape->setScale(1.2f, 1.2f);
			}
		}
		sh_size = ShapeSize::Big;
		break;
	case ShapeSize::Medium:
		for (auto shape : *composite_shape)
		{
			if (shape->get_outline_color() == OUTLINE_COLOR &&
				shape->get_outline_thickness() == OUTLINE_THICKNESS)
			{
				shape->setScale(0.3f, 0.3f);
			}
		}
		sh_size = ShapeSize::Small;
		break;
	case ShapeSize::Big:
		for (auto shape : *composite_shape)
		{
			if (shape->get_outline_color() == OUTLINE_COLOR &&
				shape->get_outline_thickness() == OUTLINE_THICKNESS)
			{
				shape->setScale(0.7f, 0.7f);
			}
		}
		sh_size = ShapeSize::Medium;
		break;
	}
}

void Composite::remove_selecting()
{
	for (auto shape : *composite_shape)
	{
		shape->set_outline_thickness(0.0f);
	}
}

MyShape* Composite::get_selected_shape() const
{
	for (auto shape : *composite_shape)
	{
		if (shape->get_outline_color() == OUTLINE_COLOR &&
			shape->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			return shape;
		}
	}
	return nullptr;
}

void Composite::set_fill_color(const Color& color)
{
	for (auto shape : *composite_shape)
	{
		shape->set_fill_color(color);
	}
}

void Composite::set_outline_color(const Color& color)
{
	for (auto shape : *composite_shape)
	{
		shape->set_outline_color(color);
	}
}

void Composite::set_outline_thickness(float thickness)
{
	for (auto shape : *composite_shape)
	{
		shape->set_outline_thickness(thickness); 
	}
}

const Color& Composite::get_outline_color() const
{
	if (size())
	{
		return composite_shape->front()->get_outline_color();
	}
	else throw std::string("The composite does not contain any shapes.");
}

float Composite::get_outline_thickness() const
{
	if (size())
	{
		return composite_shape->front()->get_outline_thickness();
	}
	else throw std::string("The composite does not contain any shapes.");
}

void Composite::restore_color()
{
	for (auto shape : *composite_shape)
	{
		shape->restore_color();
	}
}

bool Composite::contains(const Vector2f& point) const
{
	for (auto shape : *composite_shape)
	{
		if (shape->contains(point))
		{
			return true;
		}
	}
	return false;
}

FloatRect Composite::get_global_bounds() const
{
	if (size())
	{
		float shape_left, shape_top, shape_width, shape_heigth;
		float left = 100000, top = 100000, right = -100000, bottom = -100000; 
		FloatRect bounds;
		
		for (auto shape : *composite_shape)
		{
			bounds = shape->get_global_bounds();

			shape_left = bounds.left;
			shape_top = bounds.top;
			shape_width = bounds.width;
			shape_heigth = bounds.height;

			if (shape_left < left)
				left = shape_left;
			if (shape_left + shape_width > right)
				right = shape_left + shape_width;
			if (shape_top < top)
				top = shape_top;
			if (shape_top + shape_heigth > bottom)
				bottom = shape_top + shape_heigth;
		}
		return FloatRect(left, top, right - left, bottom - top);
	}
	else throw std::string("The composite does not contain any shapes.");
}

void Composite::setRotation(float angle)
{
	for (auto shape : *composite_shape)
	{
		if (shape->get_outline_color() == OUTLINE_COLOR &&
			shape->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			shape->setRotation(angle);
		}
	}
}

void Composite::setScale(float factorX, float factorY)
{
	for (auto shape : *composite_shape)
	{
		if (shape->get_outline_color() == OUTLINE_COLOR &&
			shape->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			shape->setScale(factorX, factorY);
		}
	}
}

void Composite::setScale(const Vector2f& factors)
{
	setScale(factors.x, factors.y);
}

void Composite::rotate(float angle)
{
	for (auto shape : *composite_shape)
	{
		if (shape->get_outline_color() == OUTLINE_COLOR &&
			shape->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			shape->rotate(angle); 
		}
	}
}

void Composite::scale(float factorX, float factorY)
{
	for (auto shape : *composite_shape)
	{
		if (shape->get_outline_color() == OUTLINE_COLOR &&
			shape->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			shape->scale(factorX, factorY); 
		}
	}
}

void Composite::scale(const Vector2f& factor)
{
	scale(factor.x, factor.y); 
}

void Composite::move(float offsetX, float offsetY)
{
	for (auto shape : *composite_shape)
	{
		if (shape->get_outline_color() == OUTLINE_COLOR && 
			shape->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			shape->move(offsetX, offsetY);  
		}
	}
}

void Composite::move(const Vector2f& offset)
{
	move(offset.x, offset.y);
}

void Composite::auto_move(float speed, Clock & clock)
{
	for (auto shape : *composite_shape)
	{
		if (shape->get_outline_color() == OUTLINE_COLOR &&
			shape->get_outline_thickness() == OUTLINE_THICKNESS)
		{
			shape->auto_move(speed, clock);
		}
	}
}

void Composite::draw(sf::RenderWindow& window) const
{
	for (auto shape : *composite_shape)
	{
		shape->draw(window); 
	}
}

MyShape* Composite::clone() const
{
	Composite* composite_copy = new Composite();   
	for (auto shape : *composite_shape)
	{
		composite_copy->add_shape(shape->clone()); 
	}
	composite_copy->sh_size = sh_size;

	return composite_copy; 
}

std::size_t Composite::get_point_count() const
{
	std::size_t point_count = 0;
	for (auto shape : *composite_shape)
	{
		point_count += shape->get_point_count();
	}
	return point_count;
}

size_t Composite::size() const
{
	return composite_shape->size();
}

void Composite::clear()
{
	for (MyShape* shape : *composite_shape) 
	{
		delete shape;
	}
	composite_shape->clear();
}

sf::Vector2f Composite::get_point(std::size_t index) const
{
	return sf::Vector2f();
}

ShapeMemento* Composite::create_memento() const
{
	CompositeMemento* tmp_memento = new CompositeMemento();  
	for (MyShape* shape : *composite_shape)
	{
		tmp_memento->add_memento(shape->create_memento());
	}
	return tmp_memento;
}

void Composite::set_memento(const ShapeMemento* memento)
{
	clear();
	CompositeMemento* comp_memento = (CompositeMemento*)memento;

	for (auto tmp_memento : *(comp_memento->mementos))
	{
		composite_shape->push_back(tmp_memento->create_shape()); 
	}
}
