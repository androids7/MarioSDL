#include <iostream>
#include <SDL2/SDL.h>

#include "player.h"
#include "block.h"

using namespace std;

int main(int argc, char *argv[])
{
	bool running = true;
	SDL_Window *win;
	SDL_Renderer *ren;

	player pmain;
	block barr(10,600 - 50);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	win = SDL_CreateWindow("Mario", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	while(running)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT) running = false;
			else if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_LEFT:
						pmain.set_status(player::move_left);
						break;
					case SDLK_RIGHT:
						pmain.set_status(player::move_right);
						break;
					case SDLK_LALT:
						pmain.jump();
						break;
				}
			}
			else if(e.type == SDL_KEYUP)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_LEFT:
						pmain.set_status(player::stand_still);
						break;
					case SDLK_RIGHT:
						pmain.set_status(player::stand_still);
						break;
				}
			}

		}

		pmain.move();

		SDL_RenderClear(ren);

		SDL_RenderDrawRect(ren, pmain.get_drect());
		SDL_RenderDrawRect(ren, barr.get_drect());

		SDL_RenderPresent(ren);
		SDL_Delay(1000/60);
	}

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}