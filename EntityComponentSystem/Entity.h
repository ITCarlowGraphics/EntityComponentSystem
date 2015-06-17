#pragma once

#include "Component.h"
#include <map>
#include <string>


class Entity
{
	static int lastID;
public:

	int id;
	std::map<std::string,Component*> components;


	Entity(void){
		id=lastID;
		lastID++;
	};
	~Entity(void){
		components.clear();
	};




	void addComponent(Component* c){
		components[ c->name]= c;
	}

	void removeComponent(std::string name){
		components.erase(name);
	}

	Component* getComponent(std::string name){
		std::map<std::string,Component*>::iterator it;
		it=components.find(name);
		
		if (it != components.end() )
		{
			return it->second;
		}
		return NULL;
	}

};

