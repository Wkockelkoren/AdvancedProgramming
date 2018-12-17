#include <iostream>
#include <vector>
#include <array>
#include "Map.h"
#include "PathManager.h"
#include "Vehicle.h"
#include "Window.h"
#include "SDL.h"
#include "time.h"

#include <nanogui/nanogui.h>
#include <nanogui/opengl.h>
#include <nanogui/glutil.h>

// Includes for the GLTexture class.
#include <cstdint>
#include <memory>
#include <utility>

#if defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
#if defined(_WIN32)
#  pragma warning(push)
#  pragma warning(disable: 4457 4456 4005 4312)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#if defined(_WIN32)
#  pragma warning(pop)
#endif
#if defined(_WIN32)
#  if defined(APIENTRY)
#    undef APIENTRY
#  endif
#  include <windows.h>
#endif

int main(int argc, char*argv[]) {

	/* initialize nanogui */
	nanogui::init();

	/* define the screen size based on your screen resolution*/
	nanogui::Screen screen{ {900, 650}, "Path Planner", false };
	screen.setSize({ 900 / screen.pixelRatio(), 650 / screen.pixelRatio() });

	/* define the button window */
	nanogui::Window window{ &screen, "Window" };
	window.setPosition({ 0, 0 });
	window.setLayout(new nanogui::GroupLayout());

	/* define the map window */
	nanogui::Window mapWindow{ &screen, "Map" };
	mapWindow.setPosition({ 100, 0 });
	mapWindow.setLayout(new nanogui::GroupLayout());
	mapWindow.setFixedSize({ 300, 300 });
	
	nanogui::GLCanvas *mapCanvas1 = new nanogui::GLCanvas(&mapWindow);
	nanogui::GLCanvas *mapCanvas2 = new nanogui::GLCanvas(&mapWindow);
	nanogui::GLCanvas *mapCanvas3 = new nanogui::GLCanvas(&mapWindow);
	nanogui::GLCanvas *mapCanvas4 = new nanogui::GLCanvas(&mapWindow);

	mapCanvas1->setFixedSize({ 100, 100 });
	mapCanvas2->setFixedSize({ 100, 100 });
	mapCanvas3->setFixedSize({ 100, 100 });
	mapCanvas4->setFixedSize({ 100, 100 });

	mapCanvas1->setBackgroundColor({ 0, 0, 256, 255 });
	mapCanvas2->setBackgroundColor({ 100, 100, 0, 255 });
	mapCanvas3->setBackgroundColor({ 0, 100, 0, 255 });
	mapCanvas4->setBackgroundColor({ 100, 0, 0, 255 });	

	/* create some buttons on the window */
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
	dropOff.y = 4;

	//path finding algorithm (sample algorithm)
	std::vector<Coordinate> generatedPath = pathManager.createPath(startPosition, dropOff, factory);

	SDL_Window* sdlWindow;
	SDL_Surface* surface;
	SDL_Renderer* renderer;

	// Create a window, surface and renderer. Continue when no errors occured, otherwise stop the program
	if (!loadWindow(&sdlWindow, 640, 480, &surface, &renderer))
		return 0;

	int X_Map = 0;
	int Y_Map = 0;

	/* Draw the Image on rendering surface */
	int done = 0;
	while (!done) {

		/* Draw nanogui window */
		screen.drawAll();

		SDL_Event e;
		while (SDL_PollEvent(&e)) {

			/* Re-create when window has been resized */
			if ((e.type == SDL_WINDOWEVENT) && (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)) {

				SDL_DestroyRenderer(renderer);

				surface = SDL_GetWindowSurface(sdlWindow);
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
		SDL_UpdateWindowSurface(sdlWindow);
	}

	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

	nanogui::shutdown();
	exit(EXIT_SUCCESS);

	return 0;
}

