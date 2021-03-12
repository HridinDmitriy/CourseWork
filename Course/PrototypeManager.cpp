#include "PrototypeManager.h"
#include <iostream>

PrototypeManager::~PrototypeManager()
{
	for(auto &pair : prototypes) 
	{
		delete pair.second; 
	}
	prototypes.clear(); 
}

PrototypeManager* PrototypeManager::get_instance() 
{ 
	static PrototypeManager instance; 
	return &instance;
}

void PrototypeManager::add_pair(std::pair<std::string, MyShape*> pair)
{
	prototypes.insert(pair);        
}

void PrototypeManager::remove_pair(std::string key)
{
	delete prototypes.at(key);
	prototypes.erase(key); 
}

MyShape* PrototypeManager::get_prototype(std::string key) const 
{
	MyShape* prototype = prototypes.at(key); 
	return prototype->clone(); 
}

std::size_t PrototypeManager::count() const
{
	return prototypes.size();
}

void PrototypeManager::print_prototype() const
{
	for (auto prot : prototypes)
	{
		std::cout << "    " << prot.first << std::endl;
	}
}

bool PrototypeManager::contains(std::string key) const
{
	return prototypes.count(key) ? true : false;
}