#pragma once
#include "component.h"
#include "SFML\System.hpp"

class Controllable : public Component
{
public:
	Controllable(float s){name="controllable";speed=s;};
	float speed;
};


