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

	
	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();


	bool Save(pugi::xml_node&) const;

	bool Load(pugi::xml_node&);
	
	

public:

	iPoint startPos = { 0, 1000 };
	iPoint position = { 0,0 };
	int speed;
	int cont = 0;
	int cont2 = 0;
	Animation* current_animation = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation run;
	Animation jump;
	Animation climb;
	bool jumping = false;
	bool climbing = false;
	uint gid;
	SDL_RendererFlip flip;
	bool firstUpdate = true;
	//Collider* collider = nullptr;
//	fPoint position;
	
};


#endif
