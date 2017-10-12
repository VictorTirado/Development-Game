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

	bool Start();
	//update_status Update();
	bool CleanUp();

	

public:

	SDL_Texture* graphics = nullptr;
	//Collider* collider = nullptr;
	iPoint position;

	
};


#endif
