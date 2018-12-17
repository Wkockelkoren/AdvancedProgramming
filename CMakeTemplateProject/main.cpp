#include <iostream>
#include <vector>
#include <array>
#include "Map.h"
#include "PathManager.h"
#include "Vehicle.h"
#include "Window.h"
#include "SDL.h"
#include "time.h"

#include <nanogui/screen.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/button.h>

#include <nanogui/nanogui.h>

// https://github.com/wjakob/nanogui/issues/47

int main(int argc, char*argv[]){
	int menuMode = 0;
	
	int buttonMode = 0;
	int poiXField = 0;
	int poiYField = 0;
	
	bool vehicleAdded = false;
	int vehicleXField = 0;
	int vehicleYFIeld = 0;

	bool taskAdded = false;
	int newTaskXField = 0;
	int newTaskYField = 0;

	nanogui::init();

	nanogui::Screen screen{{900, 650}, "Screen", false};
	screen.setSize({ 900 / screen.pixelRatio(), 650 / screen.pixelRatio() });
	
	nanogui::Window mainWindow{ &screen, "Main Window" };
	mainWindow.setPosition({ 15, 15 });
	mainWindow.setLayout(new nanogui::GroupLayout());

	nanogui::Window mapEditorWindow{ &screen, "Map-Editor Window" };
	mapEditorWindow.setPosition({ 15, 15 });
	mapEditorWindow.setLayout(new nanogui::GroupLayout());
	mapEditorWindow.setVisible(false);

	nanogui::Window vehicleEditorWindow{ &screen, "Vehicle-Editor Window" };
	vehicleEditorWindow.setPosition({ 15, 15 });
	vehicleEditorWindow.setLayout(new nanogui::GroupLayout());
	vehicleEditorWindow.setVisible(false);

	nanogui::Window taskManagerWindow{ &screen, "Task-Manager Window" };
	taskManagerWindow.setPosition({ 15, 15 });
	taskManagerWindow.setLayout(new nanogui::GroupLayout());
	taskManagerWindow.setVisible(false);

	createMainButtons(&screen, &mainWindow, menuMode);
	createMapEditButtons(&screen, &mapEditorWindow, menuMode, buttonMode, poiXField, poiYField);
	createVehicleEditButtons(&screen, &vehicleEditorWindow, menuMode, vehicleAdded, vehicleXField, vehicleYFIeld);
	createTaskManagerButtons(&screen, &taskManagerWindow, menuMode, taskAdded, newTaskXField, newTaskYField);

    screen.performLayout();

    screen.drawAll();
    screen.setVisible(true);


	// Timing stuff
		clock_t this_time = clock();
		clock_t last_time = this_time;
	//

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
	Vehicle vehicle(0,4);
	vehicles.push_back(vehicle);

	//get start position and dropoff position
	Position startPosition;
	startPosition.x = vehicle.getPosition().x;
	startPosition.y = vehicle.getPosition().y;

	Position dropOff;
	dropOff.x = 9;
	dropOff.y =4;

	//path finding algorithm (sample algorithm)
	std::vector<Coordinate> generatedPath = pathManager.createPath(startPosition, dropOff, factory);

	SDL_Window* mapWindow;
	SDL_Surface* surface;
	SDL_Renderer* renderer;

	// Create a window, surface and renderer. Continue when no errors occured, otherwise stop the program
	if (!loadWindow(&mapWindow, 640, 480, &surface, &renderer))
		return 0;

	/* Draw the Image on rendering surface */
	int done = 0;
	while (!done) {		
		/*Switch cases for button actions, not nice code look further into closures, button functionality should be fully in buttoncallback*/
		switch (menuMode) {
			case 1:
				mapEditorWindow.setVisible(false);
				vehicleEditorWindow.setVisible(false);
				taskManagerWindow.setVisible(false);
				mainWindow.setVisible(true);
				break;
			case 2:
				mainWindow.setVisible(false);
				vehicleEditorWindow.setVisible(false);
				taskManagerWindow.setVisible(false);
				mapEditorWindow.setVisible(true);
				switch (buttonMode) {
					case 1: //NewFLoorButton
						factory.getPointOfInterest(poiXField, poiYField).setPointOfInterestType(pointOfInterestType::Floor);
						buttonMode = 0;
						break;
					case 2: //NewWallButton
						factory.getPointOfInterest(poiXField, poiYField).setPointOfInterestType(pointOfInterestType::Wall);
						buttonMode = 0;
						break;
					case 3: //NewDropOffButton
						factory.getPointOfInterest(poiXField, poiYField).setPointOfInterestType(pointOfInterestType::DropOff);
						buttonMode = 0;
						break;
					case 4: //New MapButton
						//Empty for now
						buttonMode = 0;
						break;
					default:
						break;
				}
				break;
			case 3:
				mainWindow.setVisible(false);
				mapEditorWindow.setVisible(false);
				taskManagerWindow.setVisible(false);
				vehicleEditorWindow.setVisible(true);
				if (vehicleAdded == true) {
					//newvehicle met vehX en Yfield
					vehicleAdded = false;
				}
				break;
			case 4:
				mainWindow.setVisible(false);
				mapEditorWindow.setVisible(false);
				vehicleEditorWindow.setVisible(false);
				taskManagerWindow.setVisible(true);
				if (taskAdded == true) {
					//add task met X en Y fields
					taskAdded = false;
				}
				break;
			default:
				mapEditorWindow.setVisible(false);
				vehicleEditorWindow.setVisible(false);
				taskManagerWindow.setVisible(false);
				mainWindow.setVisible(true);
				break;
		}
	
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

			//Move all vehicles to the next place on the path
			for (int i = 0; i < vehicles.size(); i++) {
				vehicles.at(i).moveNextPathPosition(generatedPath);
			}
		}

		factory.printMap(renderer, vehicles, generatedPath);

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

