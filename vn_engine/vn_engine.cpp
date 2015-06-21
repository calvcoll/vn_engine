/*
I dedicate this engine to the great Monty Oum, who sadly passed away 01/02/2015
He was a flame that burnt brightly but too shortly, and who always be remembered.

"	I believe that the human spirit is indomitable.
	If you endeavor to achieve, it will happen given enough resolve.
	It may not be immediate, and often your greater dreams is something you will not achieve within your own lifetime.
	The effort you put forth to anything transcends yourself, for there is no futility even in death.	"
*/

#include "vn_engine.h"

/*
This engine has been designed to overwrite some of the events that fire from SDL, this is to make the use a lot easier.
*/

int main() {
	DEBUG = true;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win = SDL_CreateWindow("vn-engine", 20, 20, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	lua_State* state = initLuaScript("script.lua");
	eventLoop(renderer);
	gameLoop(renderer);

	SDL_DestroyWindow(win);
	SDL_Quit();
	killLuaState(state);

	return 0;
}

void eventLoop(SDL_Renderer* renderer) {
	int old_width;
	int old_height;
	int new_width = DEFAULT_WIDTH;
	int new_height = DEFAULT_HEIGHT;
	double scaleX = 1;
	double scaleY = 1;
	SDL_Event event;
	SDL_WaitEvent(&event);

	while (!game_finished) {
		SDL_RenderClear(renderer);
		if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				old_width = new_width;
				old_height = new_height;
				new_width = event.window.data1;
				new_height = event.window.data2;
				scaleX = (double)new_width / old_width;
				scaleY = (double)new_height / old_height;
				if (DEBUG) {
					printf("x: %d y:%d scaleX:%.2f scaleY:%.2f \n", new_width, new_height, scaleX, scaleY);
				}
				eventQueue.push_back(ResizeEvent(old_width, old_height, new_width, new_height, scaleX, scaleY));
			}
		}
		switch (event.type) {
		case SDL_QUIT:
			game_finished = true;
			printf("%s", "Quitting on SDL Quit");
			break;
		}

		SDL_RenderPresent(renderer);
		SDL_WaitEvent(&event);
	}
}

void gameLoop(SDL_Renderer* renderer) {
	while (!game_finished) {
		SDL_Delay(1000/FRAME_RATE);
	}
}