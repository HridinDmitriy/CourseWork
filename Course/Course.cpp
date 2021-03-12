#include <iostream>
#include "GameManager.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	GameManager* g_mng = GameManager::get_instance();
	g_mng->init();
	g_mng->print_menu();
	g_mng->start();  
}