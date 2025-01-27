#ifndef _J1FADETOBLACK_
#define _J1FADETOBLACK_	

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"


class j1FadeToBlack : public j1Module
{
public:
	j1FadeToBlack();
	~j1FadeToBlack();

	bool Start();
	bool Update(float dt);
	bool FadeToBlack(/*j1Module* module_off, j1Module* module_on,*/ float time = 2.0f);
	bool IsFading() const;

private:
	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;
	//j1Module* on = nullptr;
	//j1Module* off = nullptr;

};

#endif