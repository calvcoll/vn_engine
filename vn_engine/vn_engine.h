#ifndef VN_ENGINE_H
#define VN_ENGINE_H

#include <SDL.h>
#include <stdio.h>
#include <vector>

#include "Event.h"
#include "ResizeEvent.h"

#undef main

int DEFAULT_WIDTH = 1280;
int DEFAULT_HEIGHT = 720;

bool DEBUG = false;

std::vector <Event> eventQueue;

int main();
void gameLoop();

#endif