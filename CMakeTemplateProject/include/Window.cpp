#include "Window.h"

bool loadWindow(SDL_Window** window, size_t width, size_t height, SDL_Surface** surface, SDL_Renderer** renderer) {
	
	// Initialize SDL2
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
		return false;
	}

	// Create a SDL window
	*window = SDL_CreateWindow(
		"Path Planner",
		50,
		50,
		(int) width,
		(int) height,
		0
	);
	if (!*window) /* Check whether creating SDL window was successful */
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n", SDL_GetError());
		return false;
	}

	// Create a SDL surface and renderer
	*surface = SDL_GetWindowSurface(*window);
	*renderer = SDL_CreateSoftwareRenderer(*surface);
	if (!renderer) /* Check whether creating the render was successful */
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n", SDL_GetError());
		return false;
	}

	// Clear the rendering surface with the specified color
	SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(*renderer);
	return true;
}

void updateScreen(SDL_Renderer *renderer, SDL_Window *mapWindow, Map &map, std::vector<Vehicle> vehicles) {
	
	// Update the map
	try {
		map.printMap(renderer, vehicles);
	} /* Catch possible exceptions */
	catch (std::exception const& e) {
		std::cout << e.what();
	}

	/* Got everything on rendering surface,
	now Update the drawing image on window screen */
	SDL_UpdateWindowSurface(mapWindow);
}