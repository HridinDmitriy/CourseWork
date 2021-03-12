#include "pch.h"
#include <iostream>
#include "Composite.h"

constexpr unsigned WINDOW_WIDTH = 1366;
constexpr unsigned WINDOW_HEIGHT = 768;

int main()
{
	setlocale(LC_ALL, "rus"); 

	std::cout << "Клавиши для управления: \n";
	std::cout << "1 - Добавить круг\n";
	std::cout << "2 - Добавить ромб\n";
	std::cout << "3 - Добавить треугольник\n";
	std::cout << "4 - Добавить Пятиугольник\n";
	std::cout << "W-A-S-D - управление агрегатом\n";
	std::cout << "R - изменить размер фигур\n";
	std::cout << "C - очистить агрегат\n";
	std::cout << "M - вкл/выкл автоматическое движение\n";
	std::cout << "PageUP - увеличить скорость\n";
	std::cout << "PageDown - уменьшить скорость\n";
	std::cout << "ЛКМ - Добавить/удалить фигуру в агрегат\n";
	std::cout << "ПКМ - Вкл/выкл отображение следа\n";

	Composite composite;   
	 
	sf::RenderWindow window({ WINDOW_WIDTH, WINDOW_HEIGHT }, "Lab_4", sf::Style::Default); 
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event; 
		while (window.pollEvent(event))
		{
			if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) ||
				event.type == sf::Event::Closed)
			{
				window.close();
			}
			/*else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::PageUp)
			{
				composite.increase_speed();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::PageDown)
			{
				composite.reduce_speed();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
			{
				composite.clear_composite();
				CircleWithBaseColor* tmp_shape = new CircleWithBaseColor(100, 50);
				tmp_shape->setScale(0.7f, 0.7f);
				tmp_shape->setFillColor(sf::Color(0xff, 0xff, 0xcc));
				tmp_shape->setOrigin(100, 100);
				tmp_shape->setPosition(100, 120);
				tmp_shape->set_base_color(sf::Color(0xff, 0xff, 0xcc));
				composite.add_shape_to_all(tmp_shape);
				composite.add_shape_to_composite(tmp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
			{
				composite.clear_composite();
				CircleWithBaseColor* tmp_shape = new CircleWithBaseColor(100, 4);
				tmp_shape->setScale(0.7f, 0.7f);
				tmp_shape->setFillColor(sf::Color(0xff, 0x00, 0x99));
				tmp_shape->setOrigin(100, 100);
				tmp_shape->setPosition(100, 270);
				tmp_shape->set_base_color(sf::Color(0xff, 0x00, 0x99));
				composite.add_shape_to_all(tmp_shape);
				composite.add_shape_to_composite(tmp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
			{
				composite.clear_composite();
				CircleWithBaseColor* tmp_shape = new CircleWithBaseColor(100, 3);
				tmp_shape->setOutlineColor(sf::Color::Blue);
				tmp_shape->setOutlineThickness(5);
				tmp_shape->setScale(0.7f, 0.7f);
				tmp_shape->setFillColor(sf::Color(0xff, 0xcc, 0x33));
				tmp_shape->setOrigin(100, 100);
				tmp_shape->setPosition(100, 420);
				tmp_shape->set_base_color(sf::Color(0xff, 0xcc, 0x33));
				composite.add_shape_to_all(tmp_shape);
				composite.add_shape_to_composite(tmp_shape);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4)
			{
				composite.clear_composite();
				CircleWithBaseColor* tmp_shape = new CircleWithBaseColor(100, 5);
				sf::Shape* sh = new CircleWithBaseColor(100, 4);
				tmp_shape->setScale(0.7f, 0.7f);
				tmp_shape->setFillColor(sf::Color(0x66, 0x00, 0xcc));
				tmp_shape->setOrigin(100, 100);
				tmp_shape->setPosition(100, 570);
				tmp_shape->set_base_color(sf::Color(0x66, 0x00, 0xcc));
				composite.add_shape_to_all(tmp_shape);
				composite.add_shape_to_composite(tmp_shape);
			}

			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
			{
				composite.change_auto_moving();
			}

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				composite.select_shapes(window);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			{
				composite.change_visible();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				composite.clear_composite();
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::D)
			{
				composite.move(window);
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				composite.resize_shapes();
			}

			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				composite.change_tail_visible();
			}*/
		}

		if (!composite.get_tail_visible())
			;//window.clear();
		//composite.change_color_after_collision();
		//composite.auto_move(window, clock);
		//composite.draw_shapes(window);
		//if (composite.get_visible())
			//window.display();
		//composite.restore_color();
		
	}
	return 0;
} 