#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Input.h"



j1Player::j1Player() : j1Module()
{
	
}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->tex->Load("Game/player/Player.png");
	//collider = App->collision->AddCollider({ position.x, position.y, 27, -48 }, COLLIDER_PLAYER, this);
	return ret;
}

bool j1Player::PreUpdate()
{
}

bool j1Player::Update(float dt)
{
	if (App->input->GetKey[SDL_SCANCODE_W] == j1KeyState::KEY_REPEAT)
	{
	}
	if (App->input->GetKey[SDL_SCANCODE_A] == j1KeyState::KEY_REPEAT)
	{
	}
	if (App->input->GetKey[SDL_SCANCODE_S] == j1KeyState::KEY_REPEAT)
	{
	}
	if (App->input->GetKey[SDL_SCANCODE_D] == j1KeyState::KEY_REPEAT)
	{
	}


}

bool j1Player::PostUpdate()
{
}

bool j1Player::CleanUp()
{
	LOG("Unloading player");
	SDL_DestroyTexture(graphics);
	//App->textures->Unload(graphics);
	//App->collision->EraseCollider(collider);

	return true;
}

