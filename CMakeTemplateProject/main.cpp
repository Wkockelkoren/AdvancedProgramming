#include <iostream>
#include <vector>
#include <array>
#include "Map.h"
#include "VehicleManager.h"
#include "structures.h"
#include "Vehicle.h"
#include "Window.h"
#include "SDL.h"
#include "time.h"

#include <nanogui/screen.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/button.h>

// https://github.com/wjakob/nanogui/issues/47

int main(int argc, char*argv[]){

	nanogui::init();

	nanogui::Screen screen{{600, 420}, "Screen"};
	nanogui::Window window{&screen, "Window"};
    window.setPosition({15, 15});
    window.setLayout(new nanogui::GroupLayout());

	nanogui::Button *butStart = new nanogui::Button(&window, "Start");
	nanogui::Button *butStop = new nanogui::Button(&window, "Stop");

	butStart->setCallback([] { 
		std::cout << "Start" << std::endl;
	});

	butStop->setCallback([] { 
		std::cout << "Stop" << std::endl;
	});

    screen.performLayout();

    screen.drawAll();
    screen.setVisible(true);


	// Timing stuff
		clock_t this_time = clock();
		clock_t last_time = this_time;
	//

	Map factory(10, 10);
	VehicleManager VehicleManager;

	//make tasks
	Task task;
	std::vector<Task> currentTasks;
	task.goalPosition.x = 9;
	task.goalPosition.y = 9;
	currentTasks.push_back(task);
	task.goalPosition.x = 0;
	task.goalPosition.y = 0;
	currentTasks.push_back(task);

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
	VehicleManager.addVehicle(0, 2, 0);
	VehicleManager.addVehicle(0, 2, 6);
	VehicleManager.addVehicle(1, 2, 0);

	
	std::vector<Vehicle> vehicles;
	Vehicle vehicle(3,6);
	vehicles.push_back(vehicle);
	

	Position dropOff;
	dropOff.x = 9;
	dropOff.y =4;
	
	//path finding algorithm (sample algorithm)
	VehicleManager.assignPathToVehicle(currentTasks, dropOff, factory);
	std::vector<Position> generatedPath;

	SDL_Window* mapWindow;
	SDL_Surface* surface;
	SDL_Renderer* renderer;

	// Create a window, surface and renderer. Continue when no errors occured, otherwise stop the program
	if (!loadWindow(&mapWindow, 640, 480, &surface, &renderer))
		return 0;

	/* Draw the Image on rendering surface */
	int done = 0;
	while (!done) {
		screen.drawAll();

		SDL_Event e;
		while (SDL_PollEvent(&e)) {

			/* Re-create when window has been resized */
			if ((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {

				SDL_DestroyRenderer(renderer);

				surface = SDL_GetWindowSurface(mapWindow);
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

		//program functions that are time based and need to be repeated
		this_time = clock();

		//every second the following if statement will be triggered
		if ((this_time - last_time) >= 1000) {
			last_time = this_time;

			//assign vehicle to pointer
			//if task and vehicle available
		//	Vehicle availableVehicle = VehicleManager.getAvailableVehicle();
		//	VehicleManager.createPath()
		//	VehicleManager.assignPathToVehicle(currentTasks,)
			
			//Move all vehicles to the next place on the path
			for (int i = 0; i < vehicles.size(); i++) {
				vehicles.at(i).moveNextPathPosition();
			}
		}

		factory.printMap(renderer, vehicles);

		/* Got everything on rendering surface,
		now Update the drawing image on window screen */
		SDL_UpdateWindowSurface(mapWindow);
	}

	SDL_DestroyWindow(mapWindow);
	SDL_Quit();

	nanogui::shutdown();
	exit(EXIT_SUCCESS);

	return 0;
}

