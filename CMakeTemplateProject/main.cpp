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
	std::vector<Vehicle> vehicles;


	//make tasks
	Task task;
	std::vector<Task> currentTasks;
	task.goalPosition.x = 8;
	task.goalPosition.y = 8;
	currentTasks.push_back(task);
	task.goalPosition.x = 1;
	task.goalPosition.y = 1;
	currentTasks.push_back(task);
	task.goalPosition.x = 5;
	task.goalPosition.y = 6;
	currentTasks.push_back(task);

	VehicleManager.addVehicle(1, 2, 1);
	//VehicleManager.addVehicle(5, 2, 1);
	//VehicleManager.addVehicle(1, 2, 0);

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


	//Position dropOff;
	//
	//Vehicle vehicle(3,6);
	//dropOff.x = 9;
	//dropOff.y = 4;
	//
	//std::vector<Position> generatedPath = VehicleManager.createPath(vehicle.getPosition(), dropOff, factory);
	//vehicle.setPath(generatedPath);
	//vehicles.push_back(vehicle);
	
	//Vehicle car(6, 5);
	//dropOff.x = 0;
	//dropOff.y = 2;
	//
	//std::vector<Position> generatedPath1 = VehicleManager.createPath(car.getPosition(), dropOff, factory);
	//car.setPath(generatedPath1);
	//vehicles.push_back(car);
	


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

			VehicleManager.assignPathToVehicle(currentTasks, factory);
			
			//Move all vehicles to the next place on the path
			for (int i = 0; i < VehicleManager.getVehicles().size(); i++) {
				VehicleManager.getVehicles().at(i).moveNextPathPosition();
				std::cout << "move: " << VehicleManager.getVehicles().at(i).getPosition().x <<", "<< VehicleManager.getVehicles().at(i).getPosition().y << "\n";
				std::cout << "work: " << VehicleManager.getVehicles().at(i).checkIfWorking() << "\n";
			}
		}

		factory.printMap(renderer, VehicleManager.getVehicles());

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

