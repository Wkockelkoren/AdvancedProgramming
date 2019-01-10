#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <vector>
#include "Map.h"
#include "SDL.h"

bool loadWindow(SDL_Window** window, size_t width, size_t height, SDL_Surface** surface, SDL_Renderer** renderer);

void updateScreen(SDL_Renderer *renderer, SDL_Window *mapWindow, Map &map, std::vector<Vehicle> vehicles);

/*
*Create buttons and give them functionality
*/

#endif