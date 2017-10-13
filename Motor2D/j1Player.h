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

	iPoint startPos = { 20, 1000};
	iPoint position = { 0,0 };
	int speed;
	Animation* current_animation = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation run;
	//Collider* collider = nullptr;
//	fPoint position;

	
};


#endif
