 /*! \mainpage Installation of software
  * \section install_sec1 Installation Windows
  *
  * \subsection step1_1 Step 1:
  * Install CMake and add it to your system path variable.

  * \subsection step1_2 Step 2:
	* Make sure you have installed Visual Studio 2017.

  * \subsection step1_3 Step 3:
	* Run the �build_Windows.bat� file to generate a Visual Studio 2017 project (double-click).

  * \subsection step1_4 Step 4:
	* Start the �PathPlanner.sln� from the build directory (32-bit version or 64-bit version).

  * \subsection step1_5 Step 5:
	* Set the �PathPlanner� project as StartUp project by right clicking on it.

  * \subsection step1_6 Step 6:
	* Build and run the program.Install CMake and add it to your system path variable.


  * \section install_sec2 Installation Linux
  * \subsection step2_1 Step 1:
	* Install CMake:

	*			sudo apt install cmake libsdl2-dev g++
  *
  * \subsection step2_2 Step 2: run build

	* Run the build file build_Linux.sh to compile the program:

	*			bash ./build_Linux.sh
  *
  * \subsection step2_3 Step 3:

	* Run the program using:

	*			./ build/PathPlanner

 */

#include <iostream>
#include <vector>
#include <array>
#include "Map.h"
#include "TaskManager.h"
#include "VehicleManager.h"
#include "Structures.h"
#include "Vehicle.h"
#include "Window.h"
#include "Menu.h"
#include "SDL.h"
#include "time.h"

#ifdef _WIN32 /* Windows */
#include <windows.h>
#endif

#ifdef __linux__ /* Linux */

#endif

#ifdef __APPLE__ /* MacOS */

#endif

int main() {

	


	// Timing stuff
	clock_t this_time = clock();
	clock_t last_time = this_time;

	// Creating the managers and map
	Map factory(10, 10);
	VehicleManager vehicleManager;
	TaskManager taskManager;

	// Create some tasks
	taskManager.createTask({ 1,1 });
	taskManager.createTask({ 5,1 });
	taskManager.createTask({ 9,9 });
	taskManager.createTask({ 2,9 });
	taskManager.createTask({ 5,6 }, { 9,9 });

	// Create some vehicles
	vehicleManager.addVehicle({ 2,2 }, 1);
	//vehicleManager.addVehicle({5,2}, 1);


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
	catch (std::exception const& e) {
		std::cout << e.what();
	}

	SDL_Window* mapWindow;
	SDL_Surface* surface;
	SDL_Renderer* renderer;

	// Create a window, surface and renderer. Continue when no errors occured, otherwise stop the program
	if (!loadWindow(&mapWindow, 640, 480, &surface, &renderer))
		return 0;

	/* Load initial screen/map */
	updateScreen(renderer, mapWindow, factory, vehicleManager.getVehicles());

	HWND consoleWindow = GetConsoleWindow();

	SetWindowPos(consoleWindow, 0, 700, 25, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	/* Draw the Image on rendering surface */
	size_t done = 0;
	size_t menuMode = 0;
	bool Go = false;

	while (!done) {

		if (Go == false) {
			switch (menuMode) {
			case 1: /* Task Manager*/

				MenuTaskManager(&menuMode, factory, taskManager);
				break;

			case 2: /* Vehicle Manager */
				MenuVehicleManager(&menuMode, factory, vehicleManager);
				updateScreen(renderer, mapWindow, factory, vehicleManager.getVehicles());

				break;
			case 3: /*Map Editor*/
				MenuMapEditor(&menuMode, factory);
				updateScreen(renderer, mapWindow, factory, vehicleManager.getVehicles());
				break;

			case 4: /* Go */
				std::cout << "--- Go ---\n";
				Go = true;
				break;

			case 5: /* Exit */
				done = 1;
				return 0;

			default: /* Main */
				MenuMain(&menuMode);
				break;
			}
		}
		else {
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

				vehicleManager.assignPathToVehicle(taskManager.getTaskList(), factory);

				//Move all vehicles to the next place on the path

				for (size_t i = 0; i < vehicleManager.getVehicles().size(); i++) {
					try {
						vehicleManager.getVehicles().at(i).moveNextPathPosition();
						std::cout << "Move next position\n";
						if (taskManager.getTaskList().size() == 0 && vehicleManager.allVehiclesAtGoalPosition()) {
							menuMode = 0;
							Go = false;
						}
					}
					catch (std::exception const& e) {
						std::cout << e.what();
					}
				}

				//Screen is updated after making changes
				updateScreen(renderer, mapWindow, factory, vehicleManager.getVehicles());
			}
		}
	}

	SDL_DestroyWindow(mapWindow);
	SDL_Quit();
    
	return 0;
}