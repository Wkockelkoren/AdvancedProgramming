#include <iostream>
#include <vector>
#include "Window.h"
#include "PointOfInterest.h"
#include "Map.h"

bool loadWindow(SDL_Window** window, size_t width, size_t height, SDL_Surface** surface, SDL_Renderer** renderer) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
		return false;
	}

	*window = SDL_CreateWindow(
		"Path Planner",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
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
