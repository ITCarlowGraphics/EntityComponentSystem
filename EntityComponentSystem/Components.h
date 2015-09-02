#pragma once
#include "Component.h"
#include <list>
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"




class Position : public Component
{
public:
	Position(float a, float b){name="position";x=a;y=b;};
	float x,y;
};

class Drawable: public Component{
public:
	sf::Sprite sprite;
	bool visible;

	Drawable(sf::Texture& texture){ 
		name="drawable";
		sprite.setTexture(texture,true);
		sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
		visible=true;
	}
};

class Velocity : public Component
{
public:
	Velocity(float a, float b){name="velocity";x=a;y=b;ax=0;ay=0;};
	float x,y;
	float ax,ay;
};

class Gun : public Component
{
public:
	Gun(sf::Texture& t, float cdt){name="gun";bulletImage=t,coolDownTime=cdt;readyToFire=0;};
	float coolDownTime;
	float readyToFire;
	sf::Texture bulletImage;
};


class Health : public Component
{
public:
	Health(float h){name="health";health=h;};
	float health;
};


class CollisionDamage : public Component
{
public:
	CollisionDamage(std::string n,float gives, bool receives){name=n;givesDamage=gives;receivesDamage=receives;};

	float givesDamage;
	bool receivesDamage;

};



class Collidable : public Component
{
public:
	Collidable(float r){name="collidable";radius=r;collideable=true;};
	float radius;
	bool collideable;

	std::list<Entity*> collidingWith;
};


class Controllable : public Component
{
public:
	Controllable(float s){name="controllable";speed=s;};
	float speed;
};

class Invulnerable : public Component
{
public:
	Invulnerable(float t){name="Invulnerable";time=t; invulnerable=false;reset=false;};
	float time;
	float remainingtime;
	bool invulnerable;
	bool reset;
};