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
#include "ModuleCollision.h"


j1Player::j1Player() : j1Module()
{

	name.create("player");
	//IDLE
	idle.PushBack({ 70,17,46,69 });

	
	idle.loop = 5.4f;

	//RUN
	
	//run.PushBack({ 146,17,46,69 });
	//run.PushBack({ 221,17,47,69 });
	//run.PushBack({ 47,107,39,68 });
	//run.PushBack({ 127,106,43,69 });
	//run.PushBack({ 208,106,45,68 });
	//run.PushBack({ 287,105,43,69 });
	run.PushBack({ 127,106,46,69 });
	run.PushBack({ 208,106,46,69 });
	run.PushBack({ 287,105,46,69 });
	

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
	
	jump.loop = 5.4f;

	//Levitate
	levitate.PushBack({ 622,241,46,78 });
	levitate.PushBack({ 689,240,46,79 });
	levitate.PushBack({ 767,221,46,104 });
	levitate.PushBack({833,200,45,166});
	levitate.loop = 5.4f;

	//CLIMB
	climb.PushBack({550,272,75,128});
	climb.PushBack({ 642,272,75,128 });
	climb.PushBack({ 723,272,75,128 });
	climb.PushBack({ 803,272,75,128 });
	climb.PushBack({ 884,272,75,128 });
	climb.PushBack({ 559,413,75,128 });
	climb.PushBack({ 634,413,75,128 });
	climb.PushBack({ 713,413,75,128 });
	climb.PushBack({ 801,413,75,128 });
	climb.PushBack({ 894,413,75,128 });
	climb.loop = 5.4f;
	


	/*attack.PushBack({ 29,377,49,69 });
	attack.PushBack({ 84,377,49,69 });
	attack.PushBack({ 149,377,49,71 });*/

	/*attack.PushBack({ 257,377,49,71});
	attack.PushBack({ 331,388,130,66 });
	attack.PushBack({ 445,383,130,61 });
	attack.PushBack({ 589,382,130,61 });
*/
	attack.PushBack({11,467,131,61});
	attack.PushBack({ 186,467,131,61 });
	attack.PushBack({ 336,467,131,61 });
	attack.PushBack({ 499,465,133,62 });
	attack.PushBack({ 648,464,135,61 });
	attack.PushBack({ 814,465,135,61 });
	attack.PushBack({ 967,467,148,61 });


	melee.PushBack({ 442,98,46,69 });
	melee.PushBack({ 501,98,55,69 });
	melee.PushBack({ 558,98,100,69 });
	melee.PushBack({ 675,104,127,69 });
	melee.PushBack({ 821,109,100,69 });



	shot.PushBack({ 22,550,46,69 });
	shot.PushBack({ 83,551,49,70 });
	shot.PushBack({ 152,553,59,71 });
	shot.PushBack({ 232,554,56,70 });
	shot.PushBack({ 315,555,49,69 });
	shot.PushBack({ 385,556,46,69 });

	death.PushBack({ 38,282,46,69 });
	death.PushBack({ 93,289,45,62 });
	death.PushBack({ 147,315,45,62 });
	death.PushBack({ 230,315,45,62 });
	death.PushBack({ 314,312,75,38 });
	
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
	
	graphics = App->tex->Load("player/Player.png");
	collider = App->collision->AddCollider({ position.x, position.y, 46, 69 }, COLLIDER_PLAYER, this);
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
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{
		current_animation = &attack;
	}
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_REPEAT)
	{
		current_animation = &melee;
	}
	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_REPEAT)
	{
		current_animation = &shot;
	}
	if (App->input->GetKey(SDL_SCANCODE_U) == KEY_REPEAT)
	{
		current_animation = &death;
	}
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT)
	{
		current_animation = &levitate;
	}
	

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && App->map->data.maplayers.end->data->data[gid-49] == 56)
	{
		current_animation = &climb;
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
	if (App->map->data.maplayers.end->data->data[gid - 49] == 56) {
		current_animation = &climb;
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
	App->collision->EraseCollider(collider);

	return true;
}

bool j1Player::Save(pugi::xml_node& save) const
{
	bool ret = false;
	if (save.child("pos") == NULL) {
		save.append_child("pos").append_attribute("x") = position.x;
		save.child("pos").append_attribute("y") = position.y;
	}
	else {
		save.child("pos").attribute("x") = position.x;
		save.child("pos").attribute("y") = position.y;
	}

	ret = true;
	return ret;
}

bool j1Player::Load(pugi::xml_node& save)
{
	bool ret = false;

	if (save.child("pos") != NULL) {
		position.x = save.child("pos").attribute("x").as_float();
		position.y = save.child("pos").attribute("y").as_float();
	}
	ret = true;
	return ret;	
}

