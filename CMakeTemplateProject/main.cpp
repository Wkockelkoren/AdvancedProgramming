 /*! \mainpage Installation of software
  * \section install_sec1 Installation Windows
  *
  * \subsection step1_1 Step 1:
  * Install CMake and add it to your system path variable.

  * \subsection step1_2 Step 2:
	* Make sure you have installed Visual Studio 2017.

  * \subsection step1_3 Step 3:
	* Run the build_Windows.bat file to generate a Visual Studio 2017 project (double-click).

  * \subsection step1_4 Step 4:
	* Start the PathPlanner.sln from the build directory (32-bit version or 64-bit version).

  * \subsection step1_5 Step 5:
	* Set the PathPlanner project as StartUp project by right clicking on it.

  * \subsection step1_6 Step 6:
	* Build and run the program


  * \section install_sec2 Installation Linux
  * \subsection step2_1 Step 1:
	* Install CMake:

	*			sudo apt install cmake libsdl2-dev g++
  *
  * \subsection step2_2 Step 2:

	* Run the build file build_Linux.sh to compile the program:

	*			bash ./build_Linux.sh
  *
  * \subsection step2_3 Step 3:

	* Run the program using:

	*			./build/PathPlanner

  * \section install_sec3 Installation MacOS
    * \subsection step3_1 Step 1:
	* Install Brew:

	*			 /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

  * \subsection step3_2 Step 2:
	* Install CMake, SDL2 and gcc:

	*			brew install cmake sdl2 gcc
  *
  * \subsection step3_3 Step 3:

	* Run the build file build_MacOS.sh to compile the program:

	*			bash ./build_MacOS.sh
  *
  * \subsection step3_4 Step 4:

	* Run the program using:

	*			./build/PathPlanner

 */

#include <iostream>
#include <vector>
#include <array>
#include "Map.h"
#include "TaskManager.h"
#include "VehicleManager.h"
#include "SampleAlgorithm.h"
#include "Structures.h"
#include "Vehicle.h"
#include "Window.h"
#include "Menu.h"
#include "SDL.h"
#include "time.h"

#ifdef _WIN32 /* Windows */
#include <windows.h>
#endif

int main() {
	// Timing stuff
	clock_t this_time = clock();
	clock_t last_time = this_time;

	// Creating the managers and map
	Map factory(20, 20);
	VehicleManager vehicleManager;
	TaskManager taskManager;

	// Some standard tasks
	taskManager.createTask({ 1, 18 }, { 16, 9 });
	taskManager.createTask({ 5,  2 }, {  9, 18 });
	taskManager.createTask({ 16, 9 }, {  5, 18 });
	taskManager.createTask({ 9, 18 }, {  1, 18 });
	taskManager.createTask({ 5, 2 }, { 16, 9 });
	taskManager.createTask({ 2, 2 });

	// One standard vehicle
	vehicleManager.addVehicle({ 17, 14 });
	vehicleManager.addVehicle({  2, 10 });
	vehicleManager.addVehicle({ 10,  1 });


	try {
		factory.getPointOfInterest(8, 0).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 1).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 3).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 4).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 5).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 6).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 7).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 9).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 10).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 11).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(8, 12).setPointOfInterestType(pointOfInterestType::Wall);

		factory.getPointOfInterest(12, 0).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 1).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 3).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 4).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 5).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 6).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 7).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 9).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 10).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 11).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 12).setPointOfInterestType(pointOfInterestType::Wall);

		factory.getPointOfInterest(0, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(1, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(2, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(3, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(5, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(6, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(7, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(9, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(11, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(13, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(14, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(15, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(16, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(17, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(18, 12).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(19, 12).setPointOfInterestType(pointOfInterestType::Wall);

		factory.getPointOfInterest( 0, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest( 2, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest( 3, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest( 4, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest( 6, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest( 7, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest( 8, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest( 9, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(10, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(11, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(12, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(13, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(14, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(15, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(16, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(18, 16).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(19, 16).setPointOfInterestType(pointOfInterestType::Wall);

		factory.getPointOfInterest(3, 17).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(3, 18).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(3, 19).setPointOfInterestType(pointOfInterestType::Wall);

		factory.getPointOfInterest(7, 17).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(7, 18).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(7, 19).setPointOfInterestType(pointOfInterestType::Wall);

		factory.getPointOfInterest(3, 5).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 5).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(5, 5).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(6, 5).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(7, 5).setPointOfInterestType(pointOfInterestType::Wall);

		factory.getPointOfInterest(5, 2).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(16, 9).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(1, 18).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(5, 18).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(9, 18).setPointOfInterestType(pointOfInterestType::DropOff);
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

	#ifdef _WIN32 /* Windows */
		/* Nicely place the command window next to the SDL window for Windows */
		HWND consoleWindow = GetConsoleWindow();
		SetWindowPos(consoleWindow, 0, 700, 25, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	#endif

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

			case 4: /* Settings */
				MenuSettings(&menuMode,vehicleManager);
				break;

			case 5: /* Go */
				std::cout << "--- Go ---\n";
				Go = true;
				break;

			case 6: /* Exit */
				done = 1;
				return 0;

			default: /* Main */
				MenuMain(&menuMode);
				break;
			}
		}
		else {
			if (vehicleManager.countVehicles() == 0)
			{
				std::cout << "No vehicles available\n\n";
				menuMode = 0;
				Go = false;
			}

			//program functions that are time based and need to be repeated
			this_time = clock();

			//every second the following if statement will be triggered
			if ((this_time - last_time) >= CLOCKS_PER_SEC) {
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
				if (taskManager.getTaskList().size() == 0 && vehicleManager.allVehiclesAtGoalPosition()) {
					menuMode = 0;
					Go = false;
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
