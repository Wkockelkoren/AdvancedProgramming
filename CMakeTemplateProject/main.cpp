#include <iostream>
#include <vector>
#include <array>
#include "Map.h"
#include "Vehicle.h"
#include "SDL.h"
#undef main

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
int done;

void DrawChessBoard(SDL_Renderer * renderer)
{
	int row = 0, column = 0, x = 0;
	SDL_Rect rect, darea;

	/* Get the Size of drawing surface */
	SDL_RenderGetViewport(renderer, &darea);

	for (; row < 8; row++)
	{
		column = row % 2;
		x = column;
		for (; column < 4 + (row % 2); column++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

			rect.w = darea.w / 8;
			rect.h = darea.h / 8;
			rect.x = x * rect.w;
			rect.y = row * rect.h;
			x = x + 2;
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}

void loop()
{
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
			return;
		}

		if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_ESCAPE)) {
			done = 1;
			return;
		}
	}

	DrawChessBoard(renderer);

	/* Got everything on rendering surface,
	now Update the drawing image on window screen */
	SDL_UpdateWindowSurface(window);
}

struct Boundary {
	int xUpper = 0;
	int xLower = 0;
	int yUpper = 0;
	int yLower = 0;
} boundary;

std::vector<Coordinate> generateListOfPaths(Map *map, Position startPosition, Position endPosition, Boundary boundary);
std::vector<Coordinate> GeneratePath(std::vector<Coordinate> &pathList, Position &start);

int main() {

	Map factory(10, 10);

	try {
		factory.getPointOfInterest(0, 5).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(9, 6).setPointOfInterestType(pointOfInterestType::DropOff);
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

	factory.printMap();

	std::vector<Vehicle> vehicles;
	Vehicle vehicle(1,4);
	vehicles.push_back(vehicle);

	factory.printMap();


	//get start position and dropoff position
	Position startPosition;
	startPosition.x = vehicle.getPosition().x;
	startPosition.y = vehicle.getPosition().y;

	Position dropOff;
	dropOff.x = 9;
	dropOff.y = 4;

	//define boundary
	boundary.xUpper = factory.width - 1; //upper bound is biggest permissable x coordinate
	boundary.xLower = 0;
	boundary.yUpper = factory.height - 1;
	boundary.yLower = 0;

	//path finding algorithm (sample algorithm)
	std::vector<Coordinate>	listOfPaths = generateListOfPaths(&factory, dropOff, startPosition, boundary);
	std::vector<Coordinate> generatedPath = GeneratePath(listOfPaths, startPosition);

	//print start and dropoff location
	std::cout << "start (" << startPosition.x << "," << startPosition.y << ")\n";
	std::cout << "dropoff (" << dropOff.x << "," << dropOff.y << ")\n";

	//print coordinates and map
	for (int i = 0; i < generatedPath.size(); i++) {
		std::cout << "coordinate: " << i;
		std::cout << "\n\tx: " << generatedPath[i].x;
		std::cout << "\n\ty: " << generatedPath[i].y;
		std::cout << "\n\tcounter: " << generatedPath[i].counter;
		std::cout << "\n";
	}

	factory.printMap(vehicles,generatedPath);
	//factory.printMap();

	std::cout << "Press enter to continue ...";
	std::cin.get();

	std::cout << SDL_INIT_VIDEO;

	std::cout << "Press enter to continue ...";
	std::cin.get(); 

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
		"Path Planner",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		0
	);
	if (!window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n", SDL_GetError());
		return 1;
	}

	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateSoftwareRenderer(surface);
	if (!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n", SDL_GetError());
		return 1;
	}

	/* Clear the rendering surface with the specified color */
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	/* Draw the Image on rendering surface */
	done = 0;
	while (!done) {
		loop();
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

std::vector<Coordinate> generateListOfPaths(Map *map, Position startCoordinate, Position endCoordinate, Boundary boundary) {
	/*This function generates a vector of coordinates. It starts with the start coordinate and
	then it checks every coordinate adjacent to the start coordinate. If the coordinate is no
	obstacle and within boundaries it adds the coordinate to a list. Next, this action also happens
	with every new coordinate in the list untill the end position is found.
	*/
	std::vector<Coordinate> pathList;
	Coordinate coordinate;

	//control variables
	int startPointReached = false;
	int highestCounter = 0;
	bool coordinateAdded = false;
	bool noPathPossible = false;
	bool existsAlready = false;

	//Place startCoordinate in list
	coordinate.x = startCoordinate.x;
	coordinate.y = startCoordinate.y;
	coordinate.counter = 0;
	pathList.push_back(coordinate);

	std::cout << "generating path\n";

	while ((startPointReached == false) && (noPathPossible ==false)) { //loop as long a the start point is nog reached
		int listSize = pathList.size(); // get the list size in order to loop through every index
		coordinateAdded = false;

		for (int i = 0; i < listSize; i++) { //loop through every index in the pathlist
			if (pathList[i].counter == highestCounter) { //only add coordinates add the 'newest' coordinates

				//obtain new coordinate to the right of current coordinate
				if ((pathList[i].x + 1) <= boundary.xUpper) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x + 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					for (int it = 0; it < pathList.size(); it++) {
						if ((coordinate.x == pathList[i].x) && (coordinate.y == pathList[i].y)) {
							existsAlready = true;
						}
					}
					//now check if there is no obstacle at the new coordinate on the map
					for (int it = 0; it < pathList.size(); it++) {
						if ((coordinate.x == pathList[it].x) && (coordinate.y == pathList[it].y)) {
							existsAlready = true;
						}
					}
					if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false && existsAlready == false) {
						pathList.push_back(coordinate);
						coordinateAdded = true;
						//stop looping when the right location is found
						if ((coordinate.x == endCoordinate.x) && (coordinate.y == endCoordinate.y)) {
							startPointReached = true;
						}
					}
					existsAlready = false;
				}
				//obtain new coordinate above current coordinate
				if ((pathList[i].y + 1) <= boundary.yUpper) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x;
					coordinate.y = pathList[i].y + 1;
					coordinate.counter = highestCounter + 1;
					//now check if there is no obstacle at the new coordinate on the map
					for (int it = 0; it < pathList.size(); it++) {
						if ((coordinate.x == pathList[it].x) && (coordinate.y == pathList[it].y)) {
							existsAlready = true;
						}
					}
					if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false && existsAlready == false) {
						pathList.push_back(coordinate);
						coordinateAdded = true;
						//stop looping when the right location is found
						if ((coordinate.x == endCoordinate.x) && (coordinate.y == endCoordinate.y)) {
							startPointReached = true;
						}
					}
					existsAlready = false;
				}
				//obtain new coordinate left to current coordinate
				if ((pathList[i].x - 1) >= boundary.xLower) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x - 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					//now check if there is no obstacle at the new coordinate on the map
					for (int it = 0; it < pathList.size(); it++) {
						if ((coordinate.x == pathList[it].x) && (coordinate.y == pathList[it].y)) {
							existsAlready = true;
						}
					}
					if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false && existsAlready == false) {
						pathList.push_back(coordinate);
						coordinateAdded = true;
						//stop looping when the right location is found
						if ((coordinate.x == endCoordinate.x) && (coordinate.y == endCoordinate.y)) {
							startPointReached = true;
						}
					}
					existsAlready = false;
				}
				//obtain new coordinae beneath the current coordinate
				if ((pathList[i].y - 1) >= boundary.yLower) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x;
					coordinate.y = pathList[i].y - 1;
					coordinate.counter = highestCounter + 1;
					//now check if there is no obstacle at the new coordinate on the map
					for (int it = 0; it < pathList.size(); it++) {
						if ((coordinate.x == pathList[it].x) && (coordinate.y == pathList[it].y)) {
							existsAlready = true;
						}
					}
					if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false && existsAlready == false) {
						pathList.push_back(coordinate);
						coordinateAdded = true;
						//stop looping when the right location is found
						if ((coordinate.x == endCoordinate.x) && (coordinate.y == endCoordinate.y)) {
							startPointReached = true;
						}
					}
					existsAlready = false;
				}
				//clean map
			}
		}
		highestCounter++;
	//	if (coordinateAdded == false) {
//			noPathPossible = true;
	//		throw std::runtime_error("No path found");
	//	}
	}
	return pathList;
}

std::vector<Coordinate> GeneratePath(std::vector<Coordinate> &pathList, Position &start) {
	//Reduce the pathList to list with steps to take
	int currentCounter;
	bool added = false;
	Coordinate currentCoordinate;
	std::vector<Coordinate> generatedPath;

	//Find startposition and counter by looping through pathList and comparing to startposition
	for (int i = 0; i < pathList.size(); i++) {
		if (pathList[i].x == start.x) {
			if (pathList[i].y == start.y) {
				currentCounter = pathList[i].counter;
				currentCoordinate = pathList[i];
				generatedPath.push_back(currentCoordinate);
			}
		}
	}

	while (currentCounter != 0) {
		for (int i = 0; i < pathList.size(); i++) {
			added = false;
			if (pathList[i].counter < currentCounter) {
				if ((pathList[i].x == (currentCoordinate.x + 1)) && (pathList[i].y == currentCoordinate.y) && added == false) {
					currentCoordinate.x = pathList[i].x;
					currentCoordinate.y = pathList[i].y;
					currentCoordinate.counter = pathList[i].counter;
					currentCounter = pathList[i].counter;
					generatedPath.push_back(currentCoordinate);
					added = true;
				}
				if ((pathList[i].x == (currentCoordinate.x - 1)) && (pathList[i].y == currentCoordinate.y) && added == false) {
					currentCoordinate.x = pathList[i].x;
					currentCoordinate.y = pathList[i].y;
					currentCoordinate.counter = pathList[i].counter;
					currentCounter = pathList[i].counter;
					generatedPath.push_back(currentCoordinate);
					added = true;
				}
				if ((pathList[i].y == (currentCoordinate.y + 1)) && (pathList[i].x == currentCoordinate.x) && added == false) {
					currentCoordinate.x = pathList[i].x;
					currentCoordinate.y = pathList[i].y;
					currentCoordinate.counter = pathList[i].counter;
					currentCounter = pathList[i].counter;
					generatedPath.push_back(currentCoordinate);
					added = true;
				}
				if ((pathList[i].y == (currentCoordinate.y - 1)) && (pathList[i].x == currentCoordinate.x) && added == false) {
					currentCoordinate.x = pathList[i].x;
					currentCoordinate.y = pathList[i].y;
					currentCoordinate.counter = pathList[i].counter;
					currentCounter = pathList[i].counter;
					generatedPath.push_back(currentCoordinate);
					added = true;
				}
			}
		}
	}
	return generatedPath;
}
