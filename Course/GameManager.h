#pragma once
#include "Composite.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Pentagon.h"
#include "PrototypeManager.h"
#include "CompositeUtils.h"
#include "SFML/Window/Event.hpp"
 
class GameManager
{
public:
	static GameManager* get_instance();
	void init();
	void print_menu() const;
	void start();

private:
	GameManager() = default;
	GameManager(const GameManager&) = default; 
	void change_tail_visible();
	bool get_tail_visible() const;
	void change_visible();
	bool get_visible() const;
	void change_auto_moving();
	bool get_auto_moving() const;
	void refresh_frame();

private:
	const float offset = 4.0f; 
	const float auto_offset = 1.0f;

	Composite composite;
	RenderWindow window; 
	Clock clock;
	ContextSettings settings; 
	PrototypeManager* prototypes; 
	CompositeUtils caretaker;
	bool tail_visible;
	bool visible;
	bool auto_moving;
};

