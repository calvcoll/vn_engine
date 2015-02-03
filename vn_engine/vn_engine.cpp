/*
I dedicate this engine to the great Monty Oum, who sadly passed away 01/02/2015
He was a flame that burnt brightly but too shortly, and who always be remembered.

"	I believe that the human spirit is indomitable.
	If you endeavor to achieve, it will happen given enough resolve.
	It may not be immediate, and often your greater dreams is something you will not achieve within your own lifetime.
	The effort you put forth to anything transcends yourself, for there is no futility even in death.	"
*/

#include "vn_engine.h"

int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* win = SDL_CreateWindow("vn-engine", 20, 20, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	new_width = DEFAULT_WIDTH;
	new_height = DEFAULT_HEIGHT;

	bool done = false;
	SDL_Event event;
	while (!done && SDL_WaitEvent(&event)) {
		if (event.type == SDL_WINDOWEVENT) {
			switch (event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				old_width = new_width;
				old_height = new_height;
				new_width = event.window.data1;
				new_height = event.window.data2;
				printf("x: %d y:%d", new_width, new_height);
				break;
			}
		}
		switch (event.type) {
		case SDL_QUIT:
			done = true;
			break;
		}
	}
	SDL_Quit();

	return 0;
}