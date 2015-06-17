//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

#include "Entity.h"
#include "Components.h"
#include "Systems.h"
#include <list>
  
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main() 
{ 
    // Create the main window 
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program"); 
	
	//load textures
	sf::Texture textureShip;
	textureShip.loadFromFile("ship.png");
	sf::Texture textureRock;
	textureRock.loadFromFile("rock.png");
	sf::Texture textureBullet;
	textureBullet.loadFromFile("bullet.png");


	std::list<Entity*> entities;

    /*create Player*/
	Entity* player;
	player=new Entity;
	entities.push_back(player);
	player->addComponent(new Drawable(textureShip));
	player->addComponent(new Position(window.getSize().x/2,window.getSize().y/2));
	player->addComponent(new Controllable(200));
	player->addComponent(new Gun(textureBullet,0.25));
	player->addComponent(new Collidable(textureShip.getSize().x/2));
	player->addComponent(new Health(1));
	player->addComponent(new CollisionDamage("rockdamage",0,1));	
	player->addComponent(new Invulnerable(1));


	//add a few rocks
	Entity* rock;
	for(int i=0;i<5;i++){
		rock=new Entity;
		entities.push_back(rock);

		rock->addComponent(new Drawable(textureRock));
		rock->addComponent(new Position(rand()%window.getSize().x,(int)(rand()%window.getSize().y)-(int)(window.getSize().y)));
		rock->addComponent(new Velocity(0,rand()%100));
		rock->addComponent(new Collidable(60));
		rock->addComponent(new CollisionDamage("rockdamage",1,0));
		rock->addComponent(new CollisionDamage("bulletdamage",1,1));
		rock->addComponent(new Health(1));
	}


       


	sf::Clock clock;
    // Start game loop 
    while (window.isOpen()) 
    { 

		sf::Time time = clock.restart();// return time since last restart & restart again

		UserInput(entities,window,time.asSeconds());
		Movement(entities,window,time.asSeconds());
		GunCooldown(entities,window,time.asSeconds());
		CheckForCollisions(entities,window,time.asSeconds());
		CollisionDamageSystem(entities,window,time.asSeconds());
		RemoveDeadEntities(entities,window,time.asSeconds());
		invulnerablity(entities,window,time.asSeconds());

		
		//prepare frame
        window.clear();
		Render(entities,window,time.asSeconds());
		
       
        // Finally, display rendered frame on screen 
        window.display(); 
    } //loop back for next frame
   
    return EXIT_SUCCESS; 
}






