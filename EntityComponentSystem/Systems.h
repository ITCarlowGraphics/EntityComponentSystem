#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

#include "Entity.h"
#include "Components.h"
#include <list>



void Movement(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds);
void Render(std::list<Entity*>& entities,  sf::RenderWindow& window, float seconds);
void UserInput(std::list<Entity*>& entities,sf::RenderWindow& window, float seconds);
void GunCooldown(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds);
void CheckForCollisions(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds);
void CheckForCollisions(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds);
void CollisionDamageSystem(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds);
void RemoveDeadEntities(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds);
void invulnerablity(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds);

void CreateBullet(std::list<Entity*>& entities,Entity* player);
