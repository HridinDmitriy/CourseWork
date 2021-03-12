#pragma once
#include <list>
#include <cmath>
#include "CircleWithBaseColor.h"

class Composite
{
public:
	Composite();
	~Composite();
	void move(sf::RenderWindow& window);
	/**/void auto_move(sf::RenderWindow& window, sf::Clock& clock);
	/**/void change_auto_moving();
	void resize_shapes();             
	void add_shape_to_all(CircleWithBaseColor* shape);
	void add_shape_to_composite(CircleWithBaseColor* shape);
	void select_shapes(sf::RenderWindow& window);
	void change_color_after_collision();
	void restore_color();
	void change_visible();
	bool get_visible();
	/**/void change_tail_visible();
	/**/bool get_tail_visible();
	void increase_speed();
	void reduce_speed();
	void draw_shapes(sf::RenderWindow& window);
	void clear_composite();

private:      
	float amplitudeY = 1.0f;  
	float periodY = 3.0f;
	float composite_shape_speed_auto = 0.03f;

	bool auto_moving = false;
	bool visible = true;       
	bool tail_visible = false;
	int size_condition;      
	float scale = 1.0f;
	float composite_shape_speed_hand = 0.15f; 
	sf::Keyboard::Key last_direction = sf::Keyboard::A;
	std::list<CircleWithBaseColor*> all_shapes;
	std::list<CircleWithBaseColor*> composite_shape;
};

