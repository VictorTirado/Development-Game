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
#include "j1Scene.h"
#include "j1FadeToBlack.h"


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
	return ret;
}

bool j1Player::PreUpdate()
{
	bool ret = true;
	return ret;
}

bool j1Player::Update(float dt)
{
	startPos.x = App->map->spawn.x;
	startPos.y = App->map->spawn.y;
	if (firstUpdate == true) {
		position = startPos;
		App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		App->render->camera.y = startPos.y - (App->win->screen_surface->h*2.5);
		firstUpdate = false;
	}
	gid=App->map->Get_gid(position.x-75, position.y);
	bool ret = true;
	current_animation = &idle;
	flip = SDL_FLIP_NONE;
	
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		current_animation = &run;
		if (App->map->data.maplayers.end->data->data[gid - 1] != 38) {
			position.x -= 3 * speed;
			App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		}
		flip = SDL_FLIP_HORIZONTAL;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		current_animation = &run;
		if (App->map->data.maplayers.end->data->data[gid+1]!=38) {
			position.x += 3 * speed;
			App->render->camera.x = -position.x + (App->win->screen_surface->w / 2);
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->map->data.maplayers.end->data->data[gid-49] == 56)
	{
		climbing = true;
		if (App->map->data.maplayers.end->data->data[gid - 49] == 56) {
			position.y = position.y - speed * 4;
			App->render->camera.y = App->render->camera.y + speed * 4;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && current_animation != &jump)
	{
		jumping = true;
	}
	if (App->map->data.maplayers.end->data->data[gid - 49] != 56 && climbing==true) {
		climbing = false;
	}
	if (jumping == true) {
		current_animation = &jump;
		if (cont < 50 && cont2!=1) {
			position.y = position.y - speed*4;
			App->render->camera.y = App->render->camera.y + speed*4;
			if (cont == 49) {
				cont2 = 1;
			}
			cont++;
		}
		if (cont > 0 && cont2 != 0) {
			if (App->map->data.maplayers.end->data->data[gid+50+1] != 38) {
				position.y = position.y + speed * 4;
				App->render->camera.y = App->render->camera.y - speed * 4;
				if (App->map->data.maplayers.end->data->data[gid + 50 + 1] == 55) {
					position = startPos;
				}
			}
			if (App->map->data.maplayers.end->data->data[gid + 50+1] == 38) {
				cont = 0;
				cont2 = 0;
				jump.Reset();
				jumping = false;
			}
		}
	}


	if (App->map->data.maplayers.end->data->data[gid + 50+1] != 38 && jumping == false && climbing==false) {
		current_animation = &jump;
		position.y = position.y + speed * 4;
		App->render->camera.y = App->render->camera.y - speed * 4;
		if (App->map->data.maplayers.end->data->data[gid + 50 + 1] == 55) {
			firstUpdate = true;
		}
	}
	jump.Reset();

	if (App->map->data.maplayers.end->data->data[gid] == 55) {
		firstUpdate = true;
	}

	if (App->map->data.maplayers.end->data->data[gid + 1] == 54) {
		if (App->scene->map == 1)
		{
			App->map->CleanUp();
			App->fade->FadeToBlack(1);
			App->map->Load("Level2.tmx");
			firstUpdate = true;
			App->scene->map = 0;
		}
		else
		{
			App->map->CleanUp();
			App->fade->FadeToBlack(1);
			App->map->Load("Level1.tmx");
			firstUpdate = true;
			App->scene->map = 1;
		}
	}

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()),1, flip);

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

