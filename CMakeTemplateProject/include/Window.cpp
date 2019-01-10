#include <iostream>
#include <vector>
#include "Window.h"
#include "PointOfInterest.h"
#include "Map.h"

/**
Is also a nanoGUI class which is used to create the sub windows of the Screen. 
The Window class can be used to draw buttons, input fields and a canvas to draw the map.

*/
bool loadWindow(SDL_Window** window, size_t width, size_t height, SDL_Surface** surface, SDL_Renderer** renderer) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
		return false;
	}

	*window = SDL_CreateWindow(
		"Path Planner",
		50,
		50,
		(int) width,
		(int) height,
		0
	);
	if (!*window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n", SDL_GetError());
		return false;
	}

	*surface = SDL_GetWindowSurface(*window);
	*renderer = SDL_CreateSoftwareRenderer(*surface);
	if (!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n", SDL_GetError());
		return false;
	}

	/* Clear the rendering surface with the specified color */
	SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(*renderer);
	return true;
}

void updateScreen(SDL_Renderer *renderer, SDL_Window *mapWindow, Map &map, std::vector<Vehicle> vehicles) {
	try {
		map.printMap(renderer, vehicles);
		std::cout << "Draw map\n";
	}
	catch (std::exception const& e) {
		std::cout << e.what();
	}

	/* Got everything on rendering surface,
	now Update the drawing image on window screen */
	SDL_UpdateWindowSurface(mapWindow);
}