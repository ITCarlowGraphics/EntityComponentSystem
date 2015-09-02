#pragma once
#include "stdafx.h" 
#include "Systems.h"



void Render(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds){
	for(Entity* e: entities)
    {
       Drawable* d =(Drawable*)e->getComponent("drawable");
	   Position* p =(Position*)e->getComponent("position");
	
	   if(d!=NULL){
			if(p!=NULL)
				d->sprite.setPosition(p->x,p->y);
			
			if(d->visible)			
				window.draw(d->sprite);
	   }

    }
}

void Movement(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds){
	for(Entity* e: entities)
    {
       Velocity* v =(Velocity*)e->getComponent("velocity");
	   Position* p =(Position*)e->getComponent("position");
	   if(v!=NULL && p!=NULL){
			v->x+=v->ax*seconds;
		    v->x+=v->ax*seconds;

			p->x+=v->x*seconds;
			p->y+=v->y*seconds;
	   }

	 
	}
}


void UserInput(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds){
	// Process events 
    sf::Event Event; 
    while (window.pollEvent(Event)) 
    { 
        // Close window : exit 
        if (Event.type == sf::Event::Closed) 
            window.close(); 
   
        // Escape key : exit 
        if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
            window.close(); 
	}
             
	Entity* player=NULL;
	Controllable* controllable=NULL;
	//find controllable entity
	for(Entity* e: entities)
	{
		controllable =(Controllable*)e->getComponent("controllable");
		if(controllable!=NULL){
			player=e;
			Position* p =(Position*)player->getComponent("position");
			if(p!=NULL){
				float distance =controllable->speed*seconds;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					p->x-=distance;
			
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					p->x+=distance;
			
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
					p->y-=distance;
			
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
					p->y+=distance;
			
				}

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				CreateBullet(entities, player);
			}
		}
	}
		
           
}

//todo merge cooldown/create bullet & gun systems
void GunCooldown(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds){
	for(Entity* e: entities)
	{
		Gun* gun =(Gun*)e->getComponent("gun");
		if(gun!=NULL){
			if(gun->readyToFire>0)
				gun->readyToFire-=seconds;
		}
	}
}

//createBullet
void CreateBullet(std::list<Entity*>& entities,Entity* player){
	
	Gun* fb =(Gun*)player->getComponent("gun");
	Position* p =(Position*)player->getComponent("position");

	if(fb==NULL || p==NULL) return;

	if(fb->readyToFire>0)
		return; //not ready to fire yet

	fb->readyToFire=fb->coolDownTime; //reset cooldown clock
	//create a bullet entity

	Entity* entity;

	entity=new Entity;
	entities.push_back(entity);

	entity->addComponent(new Drawable(fb->bulletImage));
	entity->addComponent(new Position(p->x,p->y));
	entity->addComponent(new Velocity(0,-1000));
	entity->addComponent(new CollisionDamage("bulletdamage",1,true));
	entity->addComponent(new CollisionDamage("rockdamage",0,true));
	entity->addComponent(new Collidable(50));
	entity->addComponent(new Health(1));




}

void CheckForCollisions(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds){
	for(Entity* e: entities)
    {
		Collidable* c =(Collidable*)e->getComponent("collidable");
		Position* p =(Position*)e->getComponent("position");
		if(c!=NULL && p!=NULL){//this entity can collide with things
			c->collidingWith.clear();

			for(Entity* other: entities)
			{
				if(e==other) continue;

				Collidable* otherc =(Collidable*)other->getComponent("collidable");  
				Position* otherp =(Position*)other->getComponent("position");
				if(otherc==NULL&&otherp!=NULL) continue;

				float distance=sqrt((p->x - otherp->x)*(p->x - otherp->x)+(p->y - otherp->y)*(p->y - otherp->y));

				if(distance<=c->radius+otherc->radius){//colliding
					c->collidingWith.push_back(other);
				}
			}
		}
	}
}

void CollisionDamageSystem(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds){
	for(Entity* e: entities)
    {
		Collidable* c =(Collidable*)e->getComponent("collidable");
		Health* h =(Health*)e->getComponent("health");
		

		//Position* p =(Position*)e->getComponent("position");
		if(c!=NULL && h!=NULL){
			
			for(Entity* other: c->collidingWith)
			{
				if(e==other) continue; //can't damage oneself

				// check for rock damage
				CollisionDamage* rcd=(CollisionDamage*)e->getComponent("rockdamage");
				CollisionDamage* gcd=(CollisionDamage*)other->getComponent("rockdamage");

				if(rcd!=NULL && gcd!=NULL && rcd->receivesDamage){
					
						h->health-=gcd->givesDamage;
						Invulnerable* inv =(Invulnerable*)e->getComponent("Invulnerable");
						if(inv)
							inv->reset=true;

					

				}

				//check for bullet damage
				rcd=(CollisionDamage*)e->getComponent("bulletdamage");
				gcd=(CollisionDamage*)other->getComponent("bulletdamage");

 				if(rcd!=NULL && gcd!=NULL &&   rcd->receivesDamage){
					
						h->health-=gcd->givesDamage;

				}

			
			}
		}
	}
}

void RemoveDeadEntities(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds){
	
	for(auto i = entities.begin(); i != entities.end();)
    {	
		bool removed=false;
		Health* h =(Health*)(*i)->getComponent("health");
		if(h!=NULL){
			if(h->health<=0){
				i=entities.erase(i);
				removed=true;
				
			}
		}
		if(!removed){
			i++;
		}
	}

}


void invulnerablity(std::list<Entity*>& entities, sf::RenderWindow& window, float seconds){

	for(Entity* e: entities)
	{
		Invulnerable* inv =(Invulnerable*)e->getComponent("Invulnerable");
		Drawable* draw =(Drawable*)e->getComponent("drawable");
		Collidable* c =(Collidable*)e->getComponent("collidable");
		if(inv==NULL || draw==NULL || c==NULL) continue;
		if(inv->reset){
			inv->remainingtime=inv->time;
			inv->invulnerable=true;
			inv->reset=false;
			c->collideable=false;
			draw->visible=false;
		}

			
		if(inv->invulnerable==true){
			inv->remainingtime-=seconds;
			//flicker the visibility while invulnerable	
			draw->visible=(int)(inv->remainingtime*500)%2;
			if(inv->remainingtime<0){
				inv->invulnerable=false;
				draw->visible=true;
				c->collideable=true;
			}
				
				
			
			
		}
	}
}
