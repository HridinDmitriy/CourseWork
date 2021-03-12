#include "GameManager.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

GameManager* GameManager::get_instance()
{
	static GameManager instance;
	return &instance; 
} 

void GameManager::change_tail_visible()
{
	tail_visible = !tail_visible;  
}

bool GameManager::get_tail_visible() const
{
	return tail_visible;
}

void GameManager::change_visible()
{
	visible = !visible;
}

bool GameManager::get_visible() const
{
	return visible;
}

void GameManager::change_auto_moving()
{
	auto_moving = !auto_moving;
}

bool GameManager::get_auto_moving() const
{
	return auto_moving;
}

void GameManager::print_menu() const
{
	cout << ">>������� ��� ���������� �����:\n";
	cout << "\t1 - ����\n";
	cout << "\t2 - �������������\n";
	cout << "\t3 - �����������\n";
	cout << "\t4 - ������������\n\n";
	cout << ">>������� ���������� ��������:\n";
	cout << "\t- ��� - ������� ������\n";
	cout << "\t- Delete - ������� ������\n\n";
	cout << ">>������� ������������:\n";
	cout << "\t- ��������� - �������� ����������\n";
	cout << "\t- M - �������������� ��������\n\n";
	cout << ">>������� ���������:\n";
	cout << "\t- T - ���/���� ����\n";
	cout << "\t- V - ���/���� ����������� �����\n";
	cout << "\t- R - ��������� �������\n\n";
	cout << ">>������� ����������/��������������:\n";
	cout << "\t- S - ��������� ��������� �����\n";
	cout << "\t- L - ��������� ����������� �����\n\n";
	cout << ">>������� ��� ���������� ����������:\n";
	cout << "\t- P - �������� ������ � ���������\n";
	cout << "\t- I - �������� �������� ����������\n";
	cout << "\t- G - �������� ����� ���������\n";
	cout << "\t- D - ������� ��������\n\n";
	cout << ">>������� ��� ����������:\n";
	cout << "\t- C - �������������� ��������� ������\n\n";
	cout << ">> Esc - ����� � ���������\n\n\n";
}

void GameManager::init()
{
	tail_visible = false; 
	visible = true;
	auto_moving = false;
	settings.antialiasingLevel = 4;
	clock.restart();
	window.create(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SimpleShapes", Style::Default, settings);
	prototypes = PrototypeManager::get_instance();

	Circle* circle_prt = new Circle(100, 50); 
	circle_prt->setScale(0.7f, 0.7f);
	circle_prt->setOrigin(100, 100);
	circle_prt->setPosition(100, 120);
	circle_prt->set_fill_color(sf::Color(0xff, 0xff, 0xcc));
	circle_prt->set_base_color(sf::Color(0xff, 0xff, 0xcc));
	circle_prt->set_outline_color(composite.OUTLINE_COLOR);
	circle_prt->set_outline_thickness(composite.OUTLINE_THICKNESS);
	
	prototypes->add_pair(std::make_pair("circle", circle_prt));

	Rectangle* rect_prt = new Rectangle(Vector2f(200, 100)); 
	rect_prt->setScale(0.7f, 0.7f);
	rect_prt->set_fill_color(sf::Color(0xff, 0x00, 0x99));
	rect_prt->setOrigin(100, 100);
	rect_prt->setPosition(100, 305);
	rect_prt->set_base_color(sf::Color(0xff, 0x00, 0x99));
	rect_prt->set_outline_color(composite.OUTLINE_COLOR);
	rect_prt->set_outline_thickness(composite.OUTLINE_THICKNESS);
	
	prototypes->add_pair(std::make_pair("rect", rect_prt));

	Pentagon* pent_prt = new Pentagon(100);
	pent_prt->setScale(0.7f, 0.7f);
	pent_prt->set_fill_color(sf::Color(0x66, 0x00, 0xcc));
	pent_prt->setOrigin(100, 100);
	pent_prt->setPosition(100, 570);
	pent_prt->set_base_color(sf::Color(0x66, 0x00, 0xcc));
	pent_prt->set_outline_color(composite.OUTLINE_COLOR);
	pent_prt->set_outline_thickness(composite.OUTLINE_THICKNESS);

	prototypes->add_pair(std::make_pair("pent", pent_prt));

	Triangle* triangle_prt = new Triangle(100); 
	triangle_prt->setScale(0.7f, 0.7f);
	triangle_prt->setOrigin(100, 100);
	triangle_prt->setPosition(100, 420);
	triangle_prt->set_fill_color(sf::Color(0xff, 0xcc, 0x33));
	triangle_prt->set_base_color(sf::Color(0xff, 0xcc, 0x33));
	triangle_prt->set_outline_color(composite.OUTLINE_COLOR);
	triangle_prt->set_outline_thickness(composite.OUTLINE_THICKNESS);

	prototypes->add_pair(std::make_pair("triang", triangle_prt));
}

void GameManager::start()
{
	while (window.isOpen())
	{
		Event event; 
		while (window.pollEvent(event))
		{
			if ((event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Escape) ||
				event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
			{
				composite.move(-offset, 0.0f);
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
			{
				composite.move(offset, 0.0f);
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
			{
				composite.move(0.0f, -offset);
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
			{
				composite.move(0.0f, offset); 
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num1)
			{
				composite.remove_selecting();
				composite.add_shape(prototypes->get_prototype("circle")); 
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num2)
			{
				composite.remove_selecting();
				composite.add_shape(prototypes->get_prototype("rect"));
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num3)
			{
				composite.remove_selecting();
				composite.add_shape(prototypes->get_prototype("triang"));
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Num4)
			{
				composite.remove_selecting();
				composite.add_shape(prototypes->get_prototype("pent"));
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				composite.select_shape(Vector2i(Mouse::getPosition().x, Mouse::getPosition().y));
			}
			else if (event.type == Event::KeyReleased && event.key.code == sf::Keyboard::T)
			{
				change_tail_visible();
			}
			else if (event.type == Event::KeyReleased && event.key.code == sf::Keyboard::V)
			{
				change_visible();
			}
			else if (event.type == Event::KeyReleased && event.key.code == sf::Keyboard::M)
			{
				change_auto_moving();
			}
			else if (event.type == Event::KeyReleased && event.key.code == sf::Keyboard::R)
			{
				composite.resize_shapes();
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::Delete)
			{
				composite.remove_selected_shapes();
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::C)
			{
				composite.compose_selected_shapes(); 
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::P)
			{
				MyShape* tmp = composite.get_selected_shape();

				cout << "\n>>> ������ �� ���������� ������ � ��������� ����������...\n\n";

				if (tmp != nullptr)
				{
					string str; 
					cout << "[\n\n    ������� ����, ��� ������� ������ ����� ���������: ";
					cin >> str;
					prototypes->add_pair(std::make_pair(str, tmp->clone()));
					cout << "\n]\n\n>>> �������� ��� ������� ��������!\n";
				}
				else
				{
					cout << "\n>>> �� ������ ������ �� ���� �������!\n";
				}
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::I)
			{
				cout << "\n>>> ������ �� ����� ������ ����������...\n\n";
				cout << "[\n\n";
				if (prototypes->count())
				{
					prototypes->print_prototype();
				}
				else
				{
					cout << "    ������ ����!\n";
				}
				cout << "\n]\n\n>>> ���� �������� " << prototypes->count() << " ����������.\n";
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::G)
			{
				string str;
				cout << "\n>>> ������ �� ����������� ������ �� ��������� ����������...\n\n";
				cout << "[\n\n    ������� ����, ��� ������� ������ ��������: ";
				cin >> str;
				try
				{
					composite.remove_selecting();
					composite.add_shape(prototypes->get_prototype(str));
					cout << "\n]\n\n>>> ������ ������� ��������� �� �����!\n";
				}
				catch (...)
				{
					cout << "\n]\n\n>>> ������ � ����� ������ �� ���� �������!\n";
				}
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::D)
			{
				string str;
				cout << "\n>>> ������ �� �������� ������ �� ��������� ����������...\n\n";
				cout << "[\n\n    ������� ����, ��� ������� ������ ��������: ";
				cin >> str;
				if (prototypes->contains(str) && str != "circle" && str != "rect")
				{
					prototypes->remove_pair(str);
					cout << "\n]\n\n>>> ������ ������� ������� � ��������� ����������!\n";
				}
				else
				{
					cout << "\n]\n\n>>> ������ � ����� ������ �� ���� ������� ��� �� ������ �������!\n";
				}
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::S)
			{
				caretaker.save_state(composite);
			}
			else if (event.type == Event::KeyReleased && event.key.code == Keyboard::L)
			{
				caretaker.load_state(composite);
			}
		}
		refresh_frame();
	}
}

void GameManager::refresh_frame()
{
	if (!get_tail_visible())
		window.clear();
	composite.change_color_after_collision();
	if (get_auto_moving())
		composite.auto_move(auto_offset, clock);
	if (get_visible())
		composite.draw(window);
	window.display();
	composite.restore_color();
}
