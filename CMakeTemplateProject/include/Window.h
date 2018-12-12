#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <nanogui/nanogui.h>

bool loadWindow(SDL_Window** window, int width, int height, SDL_Surface** surface, SDL_Renderer** renderer);
void createButtons(nanogui::Screen* screen, nanogui::Window* mainWindow, nanogui::Window* mapEditorWindow, bool &mapEditMode);

#endif