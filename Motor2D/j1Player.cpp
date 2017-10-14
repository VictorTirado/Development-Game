#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include "j1Input.h"
#include "j1Window.h"
#include "j1Render.h"



j1Player::j1Player() : j1Module()
{
	//IDLE
	idle.PushBack({ 16,1,75,128 });
	idle.PushBack({ 94,1,75,128 });
	idle.PushBack({ 180,1,75,128 });
	idle.PushBack({ 264,1,75,128 });
	idle.PushBack({ 345,1,75,128 });
	idle.PushBack({ 426,1,75,128 });
	idle.PushBack({ 26,133,75,128 });
	idle.PushBack({ 107,133,75,128 });
	idle.PushBack({ 187,133,75,128 });
	idle.PushBack({ 266,133,75,128 });
	idle.loop = 5.4f;

	//RUN
	run.PushBack({351,133,75,128});
	run.PushBack({ 430,133,75,128 });
	run.PushBack({ 21,266,75,128 });
	run.PushBack({ 100,266,75,128 });
	run.PushBack({ 185,266,75,128 });
	run.PushBack({ 265,266,75,128 });
	run.PushBack({ 346,266,75,128 });
	run.PushBack({ 430,266,75,128 });
	run.PushBack({ 3,408,75,128 });
	run.PushBack({ 118,408,75,128 });

	run.loop = 5.4f;

	//JUMP

	jump.PushBack({ 639,1,75,128});
	jump.PushBack({ 731,1,75,128 });
	jump.PushBack({ 820,1,75,128 });
	jump.PushBack({ 909,1,75,128 });
	jump.PushBack({ 566,137,75,128 });
	jump.PushBack({ 645,137,75,128 });
	jump.PushBack({ 726,137,75,128 });
	jump.PushBack({ 812,137,75,128 });
	jump.PushBack({ 913,137,75,128 });
	
	jump.loop = 0.0f;

}

j1Player::~j1Player()
{}


bool j1Player::Start()
{
	bool ret = true;
	startPos = App->map->spawn;
	LOG("SpawnCoords %d %d",App->map->spawn.x, App->map->spawn.y);
	position = startPos;
	speed = 1;
	LOG("Loading player textures");
	
	graphics = App->tex->Load("player/Player2.png");
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
	prevPos = position;
	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		current_animation = &run;
		position.x -= 2 * speed;
		App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
	}
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		current_animation = &run;
		position.x += 2 * speed;
		App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		jumping = true;
	}

	if (jumping == true) {
		current_animation = &jump;
		if (cont < 50 && cont2!=1) {
			position.y = position.y - speed*3;
			App->render->camera.y = App->render->camera.y + speed*3;
			if (cont == 49) {
				cont2 = 1;
			}
			cont++;
		}
		if (cont > 0 && cont2 != 0) {
			position.y = position.y + speed*3;
			App->render->camera.y = App->render->camera.y - speed*3;
			LOG("funciona ya pls");
			if (cont == 1) {
				cont2 = 0;
				jump.Reset();
				jumping = false;
			}
			cont--;
		}
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

