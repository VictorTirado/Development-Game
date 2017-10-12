#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"



j1Player::j1Player() : j1Module()
{
	
}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	//graphics = App->textures->Load("Game/player/Player.png");
	//collider = App->collision->AddCollider({ position.x, position.y, 27, -48 }, COLLIDER_PLAYER, this);
	return ret;
}

bool j1Player::CleanUp()
{
	LOG("Unloading player");
	//App->textures->Unload(graphics);
	//App->collision->EraseCollider(collider);

	return true;
}