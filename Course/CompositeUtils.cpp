#include "CompositeUtils.h"

CompositeUtils::CompositeUtils()
{
	memento = nullptr;
}

CompositeUtils::~CompositeUtils()
{
	clear();
}

void CompositeUtils::save_state(const Composite& composite)
{
	clear();
	memento = (CompositeMemento*)composite.create_memento();
	strm.open(file_name, std::ios::out | std::ios::trunc);
	if (strm.is_open())
	{
		memento->save_to_file(strm);
		std::cout << "\n>>> ��������� �������� � ����!\n\n";
		strm.close();
	}
	else
	{
		std::cout << "\n>>> �� ������� ������� ����!\n\n"; 
	}
}

void CompositeUtils::load_state(Composite& composite)
{
	if (memento == nullptr)
	{
		strm.open(file_name, std::ios::in);
		if (strm.is_open())
		{
			std::string shape_id;
			strm >> shape_id;
			std::cout << shape_id << std::endl;
			if (shape_id == "composite")
			{
				memento = new CompositeMemento();
				memento->restore_from_file(strm);   
				std::cout << "\n>>> ��������� ������������� � �����!\n\n";
			}
			else
			{
				std::cout << "\n>>> ������������� ������ ����� �������������!\n\n";
				return;
			}
			strm.close();
		}
		else
		{
			std::cout << "\n>>> �� ������� ������� ����!\n\n";
			return;
		}
	}
	
	composite.set_memento(memento);
	std::cout << "\n>>> �������������� ����� ������ �������!\n\n";
}

void CompositeUtils::clear()
{
	delete memento; 
	memento = nullptr;
}