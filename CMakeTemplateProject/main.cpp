#include <iostream>
#include <vector>
#include <array>
#include "Map.h"
#include "PathManager.h"
#include "Vehicle.h"
#include "Window.h"
#include "SDL.h"
#include <nanogui/nanogui.h>

int main(int argc, char*argv[]){

	Map factory(10, 10);
	PathManager pathManager;

	try {
		factory.getPointOfInterest(0, 5).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(9, 5).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(4, 2).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 3).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 4).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 5).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 6).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 7).setPointOfInterestType(pointOfInterestType::Wall);
	}
	catch (std::exception const& e) {// will be removed later is just for testing exeptions
		std::cout << e.what();
	}

	std::vector<Vehicle> vehicles;
	Vehicle vehicle(1,5);
	vehicles.push_back(vehicle);

	//get start position and dropoff position
	Position startPosition;
	startPosition.x = vehicle.getPosition().x;
	startPosition.y = vehicle.getPosition().y;

	Position dropOff;
	dropOff.x = 9;
	dropOff.y = 6;

	//path finding algorithm (sample algorithm)
	std::vector<Coordinate> generatedPath = pathManager.createPath(startPosition, dropOff, factory);

	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;

	// Create a window, surface and renderer. Continue when no errors occured, otherwise stop the program
	if (!loadWindow(&window, 640, 480, &surface, &renderer))
		return 0;

	/* Draw the Image on rendering surface */
	int done = 0;
	while (!done) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {

			/* Re-create when window has been resized */
			if ((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {

				SDL_DestroyRenderer(renderer);

				surface = SDL_GetWindowSurface(window);
				renderer = SDL_CreateSoftwareRenderer(surface);
				/* Clear the rendering surface with the specified color */
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);
			}

			if (e.type == SDL_QUIT) {
				done = 1;
				return 0;
			}

			if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
				done = 1;
				return 0;
			}
		}

		factory.printMap(renderer, vehicles, generatedPath);

		/* Got everything on rendering surface,
		now Update the drawing image on window screen */
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

