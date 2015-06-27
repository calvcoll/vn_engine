#ifndef VN_ENGINE_H
#define VN_ENGINE_H

#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <math.h>

#include "Event.h"
#include "ResizeEvent.h"
#include "LuaInterface.h"

#undef main

int DEFAULT_WIDTH = 1280;
int DEFAULT_HEIGHT = 720;
int FRAME_RATE = 60;

bool DEBUG = false;
bool game_finished = false;
bool refresh_screen = false;

SDL_Window* window;
SDL_mutex* renderMutex;

std::vector <Event> eventQueue;

template <typename SDL_Thread> void waitThreads(SDL_Thread thread);
template <typename SDL_Thread, typename... Args> void waitThreads(SDL_Thread thread, Args... args);

int main();
int shutdown();
int lua(void* data);
void eventLoop();
int renderLoop(void* data);

#endif