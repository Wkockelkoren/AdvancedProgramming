#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "nanogui/nanogui.h"

bool loadWindow(SDL_Window** sdlWindow, int width, int height, SDL_Surface** surface, SDL_Renderer** renderer);

#endif