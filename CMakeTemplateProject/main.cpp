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

int main(){

	/**
	Unbelievebly great.
	*/

	// Timing stuff
	clock_t this_time = clock();
	clock_t last_time = this_time;
	//


	Map factory(10, 10);
	VehicleManager vehicleManager;
	TaskManager taskManager;

	//make tasks
	taskManager.createTask({ 1,1 });
	taskManager.createTask({ 5,1 });
	taskManager.createTask({ 9,9 });
	taskManager.createTask({ 2,9 });
	taskManager.createTask({ 5,6 }, { 9,9 });

	//make vehicles
	vehicleManager.addVehicle({2,2}, 1);
	vehicleManager.addVehicle({5,2}, 1);
	

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

	/* Draw the Image on rendering surface */
	size_t done = 0;
	while (!done) {

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
				}
				catch (std::exception const& e) {
					std::cout << e.what();
				}
			}
		}

		try {
			factory.printMap(renderer, vehicleManager.getVehicles());
		}
		catch (std::exception const& e) {
			std::cout << e.what();
		}

		/* Got everything on rendering surface,
		now Update the drawing image on window screen */
		SDL_UpdateWindowSurface(mapWindow);
	}

	SDL_DestroyWindow(mapWindow);
	SDL_Quit();

	return 0;
}
