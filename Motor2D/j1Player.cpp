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
	idle.PushBack({ 2,1,75,128});
	idle.PushBack({ 80,1,75,128 });
	idle.PushBack({ 165,1,75,128 });
	idle.PushBack({ 250,1,75,128 });
	idle.PushBack({ 331,1,75,128 });
	idle.PushBack({ 413,1,75,128 });
	idle.PushBack({ 12,133,75,128 });
	idle.PushBack({ 93,133,75,128 });
	idle.PushBack({ 173,133,75,128 });
	idle.PushBack({ 251,133,75,128 });
	idle.loop = 0.4f;

	run.PushBack({345,133,75,128});
	run.PushBack({ 424,133,75,128 });
	/*run.PushBack({ 345,133,75,128 });
	run.PushBack({ 345,133,75,128 });
	run.PushBack({ 345,133,75,128 });*/

	run.loop = 0.4f;

}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	bool ret = true;
	position = startPos;
	speed = 1;
	LOG("Loading player textures");
	
	graphics = App->tex->Load("player/Player.png");
	//collider = App->collision->AddCollider({ position.x, position.y, 27, -48 }, COLLIDER_PLAYER, this);
	return ret;
}

bool j1Player::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Player::Update(float dt)
{
	bool ret = true;
	current_animation = &idle;
	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= 2 * speed;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		current_animation = &run;
		position.x += 2 * speed;
	}
	
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return ret;
}

bool j1Player::PostUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Player::CleanUp()
{
	LOG("Unloading player");
	SDL_DestroyTexture(graphics);
	//App->textures->Unload(graphics);
	//App->collision->EraseCollider(collider);

	return true;
}

