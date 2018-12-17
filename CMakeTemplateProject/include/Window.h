#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <nanogui/nanogui.h>

bool loadWindow(SDL_Window** window, int width, int height, SDL_Surface** surface, SDL_Renderer** renderer);

/*
*Create buttons and give them functionality
*/
void createMainButtons(nanogui::Screen* screen, nanogui::Window* mainWindow, int &menuMode);
void createMapEditButtons(nanogui::Screen* screen, nanogui::Window* mapEditorWindow, int &menuMode, int &buttonMode, int &xField, int &yField);
void createVehicleEditButtons(nanogui::Screen* screen, nanogui::Window* vehicleEditorWindow, int &mapEditmenuModeMode, bool &vehicleAdded, int &vehicleXField, int &vehicleYField);
void createTaskManagerButtons(nanogui::Screen* screen, nanogui::Window* taskManagerWindow, int &menuMode, bool &taskAdded, int &newTaskXField, int &newTaskYField);

#endif