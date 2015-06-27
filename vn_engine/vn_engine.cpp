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

template <typename SDL_Thread>
void waitThreads(SDL_Thread thread) {
	SDL_WaitThread(thread, NULL);
}

template <typename SDL_Thread, typename... Args>
void waitThreads(SDL_Thread thread, Args... args) {
	SDL_WaitThread(thread, NULL);
	waitThreads(args...);
}

int main() {
	DEBUG = true;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("vn-engine", 20, 20, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	renderMutex = SDL_CreateMutex();
	SDL_Thread* luaThread = SDL_CreateThread(lua, "luaThread", (void*) NULL);
	SDL_Thread* renderThread = SDL_CreateThread(renderLoop, "renderloop", (void*) NULL);
	eventLoop();

	waitThreads(renderThread, luaThread);
	return shutdown();
}

int shutdown() {
	SDL_DestroyWindow(window);
	SDL_DestroyMutex(renderMutex);
	SDL_Quit();

	return 0;
}

int lua(void* data) {
	printf("Lua init\n");
	lua_State* state = initLuaScript("script.lua");
	killLuaState(state);
	printf("\nLua dead.\n");
	return 0;
}

void eventLoop() {
	SDL_Init(SDL_INIT_EVENTS);
	int old_width;
	int old_height;
	int new_width = DEFAULT_WIDTH;
	int new_height = DEFAULT_HEIGHT;
	double scaleX = 1;
	double scaleY = 1;
	SDL_Event event;
	SDL_WaitEvent(&event);

	while (!game_finished) {
		SDL_LockMutex(renderMutex);
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
				//eventQueue.push_back(ResizeEvent(old_width, old_height, new_width, new_height, scaleX, scaleY));
				break;
			default:
				break;
			}
		}
		switch (event.type) {
		case SDL_QUIT:
			game_finished = true;
			printf("%s", "Quitting on SDL Quit");
			break;
		default:
			break;
		}
		if (!game_finished) {
			SDL_WaitEvent(&event);
			SDL_UnlockMutex(renderMutex);
		}
		SDL_Delay(1000 / FRAME_RATE);
	}
	SDL_UnlockMutex(renderMutex);
}

int times = 0;
double sum = 0;

void printfps(double fps) {
	times++;
	times %= 60;
	if (times == 0)	{
		printf("\nfps:%.2f", sum / 60); sum = 0;
	}
	else {
		sum += fps;
	}
}

int renderLoop(void* data) {
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	unsigned int time_current = SDL_GetTicks();
	unsigned int last_time = SDL_GetTicks();
	while (!game_finished) {
		//fps
		time_current = SDL_GetTicks();
		unsigned int delta = time_current - last_time;
		double fps = 1000.f / delta;
		last_time = SDL_GetTicks();
		printfps(fps);
		//end fps
		int error = SDL_TryLockMutex(renderMutex);
		if (!error) {
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
			SDL_UnlockMutex(renderMutex);
		}		
		SDL_Delay(1000 / FRAME_RATE);
	}
	SDL_DestroyRenderer(renderer);
	return 0;
}