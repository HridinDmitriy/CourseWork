#include "pch.h"
#include "Composite.h"

Composite::Composite()
	: auto_moving(false), visible(true), tail_visible(false), scale(1.0f), 
	  composite_shape_speed_hand(0.15f), last_direction(sf::Keyboard::A)
{ }

Composite::~Composite() 
{
	for (auto shape : all_shapes)
	{
		if (shape) delete shape; 
	}
}

void Composite::move(sf::RenderWindow& window)  
{
	for (auto shape : composite_shape)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			shape->move(-composite_shape_speed_hand * 30, 0.0f);
			if (shape->getPosition().x <= 0)  
				shape->setPosition(window.getSize().x, shape->getPosition().y);
			last_direction = sf::Keyboard::A;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			shape->move(composite_shape_speed_hand * 30, 0.0f);
			if (shape->getPosition().x >= window.getSize().x)
				shape->setPosition(0, shape->getPosition().y);
			last_direction = sf::Keyboard::D;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			shape->move(0.0f, -composite_shape_speed_hand * 30);
			if (shape->getPosition().y <= 0)
				shape->setPosition(shape->getPosition().x, window.getSize().y);   
			last_direction = sf::Keyboard::W;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			shape->move(0.0f, composite_shape_speed_hand * 30);
			if (shape->getPosition().y >= window.getSize().y)
				shape->setPosition(shape->getPosition().x, 0); 
			last_direction = sf::Keyboard::S;
		}
	}
}

void Composite::auto_move(sf::RenderWindow& window, sf::Clock& clock)
{
	if (auto_moving)
	{
		float time, wavePhase, x, y;

		for (auto shape : composite_shape)
		{
			if (last_direction == sf::Keyboard::A)
			{
				time = clock.getElapsedTime().asSeconds();
				wavePhase = time * (float)(2 * 3.14);
				x = composite_shape_speed_auto * time;
				y = amplitudeY * std::sin(wavePhase / periodY);
				sf::Vector2f offset = { x, y };
				shape->setPosition(shape->getPosition() - offset);
				if (shape->getPosition().x <= 0)
					shape->setPosition(window.getSize().x, shape->getPosition().y);
			}
			if (last_direction == sf::Keyboard::D)
			{
				time = clock.getElapsedTime().asSeconds();
				wavePhase = time * (float)(2 * 3.14);
				x = composite_shape_speed_auto * time;
				y = amplitudeY * std::sin(wavePhase / periodY);
				sf::Vector2f offset = { x, y };
				shape->setPosition(shape->getPosition() + offset);
				if (shape->getPosition().x >= window.getSize().x)
					shape->setPosition(0, shape->getPosition().y);
			}
			if (last_direction == sf::Keyboard::W)
			{
				time = clock.getElapsedTime().asSeconds();
				wavePhase = time * (float)(2 * 3.14);
				y = composite_shape_speed_auto * time;
				x = amplitudeY * std::sin(wavePhase / periodY);
				sf::Vector2f offset = { x, y };
				shape->setPosition(shape->getPosition() - offset);
				if (shape->getPosition().y <= 0)
					shape->setPosition(shape->getPosition().x, window.getSize().y);
			}
			if (last_direction == sf::Keyboard::S)
			{
				time = clock.getElapsedTime().asSeconds();
				wavePhase = time * (float)(2 * 3.14);
				y = composite_shape_speed_auto * time;
				x = amplitudeY * std::sin(wavePhase / periodY);
				sf::Vector2f offset = { x, y };
				shape->setPosition(shape->getPosition() + offset);
				if (shape->getPosition().y >= window.getSize().y)
					shape->setPosition(shape->getPosition().x, 0);
			}
		}
	}
}

void Composite::change_auto_moving()
{
	auto_moving = !auto_moving;
}

void Composite::resize_shapes()
{
	switch (size_condition)
	{
	case 0:
		for (auto shape : composite_shape) 
		{
			shape->setScale(1.2f, 1.2f);
			scale = 1.2f;
		}
		size_condition++; 
		break;  
	case 1:
		for (auto shape : composite_shape)
		{
			shape->setScale(0.3f, 0.3f);
			scale = 0.3f;
		}
		size_condition++;
		break;
	default:
		for (auto shape : composite_shape)
		{
			shape->setScale(0.7f, 0.7f);
			scale = 0.7f;
		}
		size_condition = 0;
		break;
	}
}

void Composite::add_shape_to_all(CircleWithBaseColor* shape)
{
	all_shapes.push_back(shape);
}

void Composite::add_shape_to_composite(CircleWithBaseColor* shape)
{
	composite_shape.push_back(shape);
}

void Composite::select_shapes(sf::RenderWindow& window)
{
	sf::Vector2f mouse_position;
	mouse_position.x = sf::Mouse::getPosition(window).x;
	mouse_position.y = sf::Mouse::getPosition(window).y;
	bool already_in_composite = false;

	for (auto shape_in_all : all_shapes)
	{
		if (shape_in_all && shape_in_all->getGlobalBounds().contains(mouse_position))
		{
			for (auto shape_in_composite : composite_shape)
			{
				if (shape_in_composite == shape_in_all)
				{
					already_in_composite = true;
					break;
				}
			}
			if (already_in_composite)
				composite_shape.remove(shape_in_all);
			else
				composite_shape.push_back(shape_in_all);
		}
	}
}

void Composite::change_color_after_collision()
{
	for (auto shp1 : composite_shape)
	{
		for (auto shp2 : composite_shape)
		{
			if (shp1->getGlobalBounds().intersects(shp2->getGlobalBounds()) && shp1 != shp2)
			{
				shp2->setFillColor(sf::Color::Red);
			}
		}
	}
}

void Composite::restore_color()
{
	for (auto shp1 : composite_shape)
	{
		shp1->setFillColor(shp1->get_base_color()); 
	}
}

bool Composite::get_visible()
{
	return visible; 
}

bool Composite::get_tail_visible()
{
	return tail_visible;
}

void Composite::draw_shapes(sf::RenderWindow& window)
{
	for (auto shape : composite_shape)
	{
		window.draw(*shape);
	}
}

void Composite::change_visible()
{
	visible = !visible;
}

void Composite::change_tail_visible()
{
	tail_visible = !tail_visible;
}

void Composite::increase_speed()
{
	composite_shape_speed_hand += 0.1;
}

void Composite::reduce_speed()
{
	composite_shape_speed_hand -= 0.1f;
	if (composite_shape_speed_hand < 0.0)
	{
		composite_shape_speed_hand = 0.0;
	}
}
 
void Composite::clear_composite()
{
	composite_shape.clear();
}