#ifndef __j1PLAYER_H__
#define __j1PLAYER_H__

#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"
#include "Animation.h"

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	//bool Awake(pugi::xml_node&);
	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	//void OnCollision(Collider* c1, Collider* c2);
	

public:

	iPoint startPos = { 0,0 };
	iPoint position = { 0,0 };

	SDL_Texture* graphics = nullptr;
	Animation idle;
	//Collider* collider = nullptr;
//	fPoint position;

	
};


#endif
