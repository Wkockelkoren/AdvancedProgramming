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
#include "SDL.h"
#include "time.h"

void updateScreen(SDL_Renderer *renderer, SDL_Window *mapWindow, Map &map, std::vector<Vehicle> vehicles);

int main() {

	/**
	Unbelievebly great.
	*/

	// Timing stuff
	clock_t this_time = clock();
	clock_t last_time = this_time;

	// Creating the managers and map
	Map factory(10, 10);
	VehicleManager vehicleManager;
	TaskManager taskManager;

	//make vehicles
	vehicleManager.addVehicle({ 9,9 }, 1);

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

	updateScreen(renderer, mapWindow, factory, vehicleManager.getVehicles());

	/* Draw the Image on rendering surface */
	size_t done = 0;
	size_t menuMode = 0;
	size_t subMenuMode = 0;
	size_t userInputX = 0;
	size_t userInputY = 0;
	bool error = false;
	bool Go = false;
	while (!done) {

		if (Go == false) {
			switch (menuMode) {
			case 1: /* Task Manager*/
				std::cout << "--- Task Manager ---\n";
				std::cout << "Options:\n";
				std::cout << "1. Add Task\n";
				std::cout << "2. Back\n";
				std::cin >> subMenuMode;

				switch (subMenuMode) {
				case 1: /* Add Task */
					std::cout << "Add Task:\n";

					error = true;
					while (error) {
						std::cout << "Give an X-position within the range 0 to " << (factory.width - 1) << ":\n";
						std::cin >> userInputX;
						if (userInputX < 0 || userInputX > factory.width - 1) {
							std::cout << "Given X-position is out of range \n";
							error = true;
							continue;
						}
						error = false;
					}

					error = true;
					while (error) {
						std::cout << "Give an Y-position within the range 0 to " << (factory.height - 1) << ":\n";
						std::cin >> userInputY;
						if (userInputY < 0 || userInputY > factory.height - 1) {
							std::cout << "Given Y-position is out of range \n";
							error = true;
							continue;
						}
						error = false;
					}


					taskManager.createTask({ userInputX, userInputY });

					break;
				case 2: /* Go back to main menu */
					menuMode = 0;
					break;
				default:
					menuMode = 1;
					break;
				}
				break;

			case 2: /* Vehicle Manager */
				std::cout << "--- Vehicle Manager ---\n";
				std::cout << "1. Add Vehicle \n";
				std::cout << "0. Back \n";
				std::cin >> subMenuMode;
				switch (subMenuMode) {
				case 1:
					std::cout << "Give an X-postion within the range 0 to " << (factory.width - 1) << "\n";
					std::cin >> userInputX;
					if (userInputX < 0 || userInputX > factory.width - 1) {
						std::cout << "Given X-position is out of range \n";
						break;
					}
					std::cout << "Give a Y-postion within the range 0 to " << (factory.height - 1) << "\n";
					std::cin >> userInputY;
					if (userInputY < 0 || userInputY > factory.width - 1) {
						std::cout << "Given Y-position is out of range \n";
						break;
					}
					vehicleManager.addVehicle({ userInputX, userInputY }, 1);
					break;
				case 0:

				default:
					std::cout << "Invalid input";
					break;
				}
				break;
			case 3: /*Map Editor*/
				std::cout << "--- Map Editor ---\n";
				break;

			case 4: /* Go */
				std::cout << "--- Go ---\n";
				Go = true;
				break;

			default: /* Main */
				std::cout << "--- Main ---\n";
				std::cout << "Select Menu Mode:\n";
				std::cout << "1. Task Manager\n";
				std::cout << "2. Vehicle Manager\n";
				std::cout << "3. Map Editor\n";
				std::cout << "4. Go\n";
				std::cin >> menuMode;
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
					}
					catch (std::exception const& e) {
						std::cout << e.what();
					}
				}

				//Screen is updated after making changes
				updateScreen(renderer, mapWindow, factory, vehicleManager.getVehicles());
			}
		}

		SDL_DestroyWindow(mapWindow);
		SDL_Quit();

		return 0;
	}
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