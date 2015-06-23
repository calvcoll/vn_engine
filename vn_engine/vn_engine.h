#ifndef VN_ENGINE_H
#define VN_ENGINE_H

#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <thread>

#include "Event.h"
#include "ResizeEvent.h"
#include "LuaInterface.h"

#undef main

int DEFAULT_WIDTH = 1280;
int DEFAULT_HEIGHT = 720;
int FRAME_RATE = 60;

bool DEBUG = false;
bool game_finished = false;

std::vector <Event> eventQueue;

int main();
void gameLoop(SDL_Renderer* renderer);
void eventLoop(SDL_Renderer* renderer);
void renderLoop(SDL_Renderer* renderer);

#endif