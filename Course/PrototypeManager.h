#pragma once
#include <unordered_map>
#include <string>
#include "MyShape.h"

class PrototypeManager
{
public:
	~PrototypeManager();
	static PrototypeManager* get_instance();
	void add_pair(std::pair<std::string, MyShape*> pair); 
	void remove_pair(std::string key);     
	MyShape* get_prototype(std::string key) const;  
	std::size_t count() const;  
	void print_prototype() const;
	bool contains(std::string key) const;

private:
	PrototypeManager() = default;
	PrototypeManager(const PrototypeManager&) = default;
private:
	std::unordered_map<std::string, MyShape*> prototypes;    
};

