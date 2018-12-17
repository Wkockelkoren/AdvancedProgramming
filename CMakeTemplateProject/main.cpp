 /*! \mainpage Installation of software
  * \section install_sec1 Installation Windows
  *
  * \subsection step1 Step 1:
  * Install CMake and add it to your system path variable.

  * \subsection step2 Step 2:
	* Make sure you have installed Visual Studio 2017.

  * \subsection step3 Step 3:
	* Run the “build_Windows.bat” file to generate a Visual Studio 2017 project (double-click).

  * \subsection step4 Step 4:
	* Start the “PathPlanner.sln” from the build directory (32-bit version or 64-bit version).

  * \subsection step5 Step 5:
	* Set the “PathPlanner” project as StartUp project by right clicking on it.

  * \subsection step6 Step 6:
	* Build and run the program.Install CMake and add it to your system path variable.


  * \section install_sec2 Installation Linux
  * \subsection step1 Step 1: 
	* Install CMake:	

*			sudo apt install cmake libsdl2-dev g++
  * 
  *  \subsection step2 Step 2: run build

	* Run the build file:

*			build_Linux.sh
  *	To compile the program bash

*			 ./build_Linux.sh
  *
  *	 \subsection step3 Step 3: 

	 *Run the program using:

*			./ build/PathPlanner
 
 */

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

#include <nanogui/nanogui.h>

// https://github.com/wjakob/nanogui/issues/47

int main(int argc, char*argv[]){

	/**
	Unbelievebly great.
	*/

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
	VehicleManager VehicleManager;
	//std::vector<Vehicle> vehicles;


	//make tasks
	Task task;
	std::vector<Task> currentTasks;

	task.goalPosition.x = 1;
	task.goalPosition.y = 1;
	currentTasks.push_back(task);

	task.goalPosition.x = 5;
	task.goalPosition.y = 1;
	currentTasks.push_back(task);

	task.goalPosition.x = 9;
	task.goalPosition.y = 9;
	currentTasks.push_back(task);

	task.goalPosition.x = 2;
	task.goalPosition.y = 9;
	currentTasks.push_back(task);

	task.goalPosition.x = 5;
	task.goalPosition.y = 6;
	currentTasks.push_back(task);

	VehicleManager.addVehicle(1, 2, 1);
	VehicleManager.addVehicle(5, 2, 1);
	//VehicleManager.addVehicle(1, 2, 0);

	try {
		factory.getPointOfInterest(0, 0).setPointOfInterestType(pointOfInterestType::DropOff);
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

			VehicleManager.assignPathToVehicle(currentTasks, factory);
			
			//Move all vehicles to the next place on the path
			for (int i = 0; i < VehicleManager.getVehicles().size(); i++) {
				std::vector< Position> test = *VehicleManager.getVehicles().at(i).getPath();
				//std::cout << "test: ";
				//for ( Position path :  test) {
				//	std::cout << "(" << path.x << "," << path.y << ") ";
				//}
				//std::cout << "\n";
				VehicleManager.getVehicles().at(i).moveNextPathPosition();
				//std::cout << "move: " << VehicleManager.getVehicles().at(i).getPosition().x <<", "<< VehicleManager.getVehicles().at(i).getPosition().y << "\n";
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

