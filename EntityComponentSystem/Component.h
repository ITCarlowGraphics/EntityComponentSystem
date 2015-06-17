#pragma once
#include<string>

//base for all components
class Component
{
public:
	Component(void){};
	~Component(void){};

	std::string name; //components have unique names
};

