#pragma once
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "Transformable.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "WindowSize.h"
#include "ShapeMemento.h"
using namespace sf;

class SFML_GRAPHICS_API MyShape : public Drawable, public ::Transformable
{ 
public: 
	virtual ~MyShape();
	virtual void set_fill_color(const Color& color);  
	virtual void set_outline_color(const Color& color);
	virtual void set_outline_thickness(float thickness);
	void set_base_color(const Color& color);

	const Color& get_fill_color() const;
	virtual const Color& get_outline_color() const;
	virtual float get_outline_thickness() const;
	FloatRect get_local_bounds() const;
	virtual FloatRect get_global_bounds() const;

	virtual void restore_color();
	virtual bool contains(const Vector2f& point) const; 

	virtual void draw(RenderWindow& window) const = 0;
	virtual std::size_t get_point_count() const = 0;
	virtual Vector2f get_point(std::size_t index) const = 0;
	virtual MyShape* clone() const = 0;

	virtual void set_memento(const ShapeMemento* memento);
	virtual ShapeMemento* create_memento() const = 0; 

protected:
	MyShape();   
	void update_all();
	const Color& get_base_color() const;

private:
	virtual void draw(RenderTarget& target , RenderStates states) const;
	void update_fill_colors();
	void update_outline();
	void update_outline_colors();

private:
	Color          fill_color;    
	Color          base_color;
	Color          outline_color;     
	float          outline_thickness; 
	VertexArray    vertices;        
	VertexArray    outline_vertices;  
	FloatRect      inside_bounds;     
	FloatRect      bounds;
};

