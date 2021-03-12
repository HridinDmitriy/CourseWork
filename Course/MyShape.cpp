#include "MyShape.h"
#include <cmath>

sf::Vector2f compute_normal(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	sf::Vector2f normal(p1.y - p2.y, p2.x - p1.x);
	float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
	if (length != 0.f)
		normal /= length;
	return normal;
} 

float get_scalar_product(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return p1.x * p2.x + p1.y * p2.y;
}


MyShape::MyShape() : 
	fill_color(255, 255, 255),
	base_color(fill_color),
	outline_color(255, 255, 255),
	outline_thickness(0),
	vertices(TriangleFan),
	outline_vertices(TriangleStrip),
	inside_bounds(),
	bounds()
{ }

MyShape::~MyShape()
{ }

void MyShape::set_fill_color(const Color& color)
{
	fill_color = color;
	update_fill_colors();
}

void MyShape::set_outline_color(const Color& color)
{
	outline_color = color;
	update_outline_colors();
}

void MyShape::set_outline_thickness(float thickness)
{
	outline_thickness = thickness;
	update_all(); 
}

const Color& MyShape::get_fill_color() const
{
	return fill_color;
}

const Color& MyShape::get_outline_color() const
{
	return outline_color;
}

float MyShape::get_outline_thickness() const
{
	return outline_thickness;
}

FloatRect MyShape::get_local_bounds() const
{
	return bounds;
}

FloatRect MyShape::get_global_bounds() const
{
	return getTransform().transformRect(get_local_bounds());
}

void MyShape::restore_color()
{
	set_fill_color(get_base_color());
}

bool MyShape::contains(const Vector2f& point) const
{
	return get_global_bounds().contains(point);
}

const Color& MyShape::get_base_color() const
{
	return base_color;
}

void MyShape::set_base_color(const Color& color)
{
	base_color = color;
}

void MyShape::update_all()
{
	// Get the total number of points of the shape
	std::size_t count = get_point_count();
	if (count < 3)
	{
		vertices.resize(0);
		outline_vertices.resize(0);
		return;
	}

	vertices.resize(count + 2); // + 2 for center and repeated first point

	// Position
	for (std::size_t i = 0; i < count; ++i)
		vertices[i + 1].position = get_point(i);
	vertices[count + 1].position = vertices[1].position;

	// Update the bounding rectangle
	vertices[0] = vertices[1]; // so that the result of getBounds() is correct
	inside_bounds = vertices.getBounds();

	// Compute the center and make it the first vertex
	vertices[0].position.x = inside_bounds.left + inside_bounds.width / 2;
	vertices[0].position.y = inside_bounds.top + inside_bounds.height / 2;

	// Color
	update_fill_colors();

	// Outline
	update_outline();
}

void MyShape::update_outline()
{
	// Return if there is no outline
	if (outline_thickness == 0.f)
	{
		outline_vertices.clear();
		bounds = inside_bounds;
		return;
	}

	std::size_t count = vertices.getVertexCount() - 2;
	outline_vertices.resize((count + 1) * 2);

	for (std::size_t i = 0; i < count; ++i)
	{
		std::size_t index = i + 1;

		// Get the two segments shared by the current point
		Vector2f p0 = (i == 0) ? vertices[count].position : vertices[index - 1].position;
		Vector2f p1 = vertices[index].position;
		Vector2f p2 = vertices[index + 1].position;

		// Compute their normal 
		Vector2f n1 = compute_normal(p0, p1);
		Vector2f n2 = compute_normal(p1, p2);

		// Make sure that the normals point towards the outside of the shape
		// (this depends on the order in which the points were defined)
		if (get_scalar_product(n1, vertices[0].position - p1) > 0)
			n1 = -n1;
		if (get_scalar_product(n2, vertices[0].position - p1) > 0)
			n2 = -n2;

		// Combine them to get the extrusion direction
		float factor = 1.f + (n1.x * n2.x + n1.y * n2.y);
		Vector2f normal = (n1 + n2) / factor;

		// Update the outline points
		outline_vertices[i * 2 + 0].position = p1;
		outline_vertices[i * 2 + 1].position = p1 + normal * outline_thickness;
	}

	// Duplicate the first point at the end, to close the outline
	outline_vertices[count * 2 + 0].position = outline_vertices[0].position;
	outline_vertices[count * 2 + 1].position = outline_vertices[1].position;

	// Update outline colors
	update_outline_colors();

	// Update the shape's bounds
	bounds = outline_vertices.getBounds();
}

void MyShape::update_fill_colors()
{
	for (std::size_t i = 0; i < vertices.getVertexCount(); ++i)
		vertices[i].color = fill_color;
}

void MyShape::update_outline_colors()
{
	for (std::size_t i = 0; i < outline_vertices.getVertexCount(); ++i)
		outline_vertices[i].color = outline_color;
}

void MyShape::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL; 
	target.draw(vertices, states);

	if (outline_thickness != 0)
	{
		states.texture = NULL;
		target.draw(outline_vertices, states);
	}
}

void MyShape::set_memento(const ShapeMemento* memento)
{
	set_fill_color(memento->fill_color);
	set_base_color(memento->base_color);
	set_outline_color(memento->outline_color);
	set_outline_thickness(memento->outline_thickness);
	setRotation(memento->rotation);
	setOrigin(memento->origin);
	setPosition(memento->position);
	setScale(memento->scale);
}