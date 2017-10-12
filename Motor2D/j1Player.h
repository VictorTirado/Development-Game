#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	//void OnCollision(Collider* c1, Collider* c2);
	

public:

	SDL_Texture* graphics = nullptr;
	//Collider* collider = nullptr;
	fPoint position;

	
};


#endif
