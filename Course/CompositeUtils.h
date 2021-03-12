#pragma once
#include "CompositeMemento.h"
#include "Composite.h"
#include <fstream>
#include <iostream>

class CompositeUtils
{
public:
	CompositeUtils();
	~CompositeUtils();
	CompositeUtils(const CompositeUtils& composite) = delete;
	CompositeUtils& operator=(const CompositeUtils& composite) = delete;
	void save_state(const Composite& composite);
	void load_state(Composite& composite);
	void clear();

private:
	const std::string file_name = "state.txt";
	CompositeMemento* memento;
	std::fstream strm;
};

