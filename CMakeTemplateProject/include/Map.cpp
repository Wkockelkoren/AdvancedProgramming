#include <iostream>
#include <vector>
#include <memory>
#include "Map.h"
#include "PointOfInterest.h"
#include "Vehicle.h"
#include "VehicleManager.h"

/**
	Contains the classes Map and PointOfInterest.
*/
Map::Map(const size_t width,const size_t height) : width(width), height(height) {
	/**
	Constructor for map
	*/

	//map = new PointOfInterest[width*height];
	map = std::make_unique<PointOfInterest[]>(width*height);
	
	// Iterate over each position and fill in the coordinates in the point of interest
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			map[y * width + x].setPosition({x,y});
		}
	}
}

Map::~Map() {
	/**
	Destructor for map
	*/
}


PointOfInterest& Map::getPointOfInterest(size_t x, size_t y) {
	/***
	Get point of interest from position on map
	*/


	//Check wether the requested point is within the map
	if (!(x < width)) {
		throw std::runtime_error("Requested point of interest is not within the map - class Map getPointOfInterest()\n");
	}
	if (!(y < height)) {
		throw std::runtime_error("Requested point of interest is not within the map - class Map getPointOfInterest()\n");
	}

	// Get point of interest and return it
	PointOfInterest& pointOfInterest = map[y * width + x];
	return pointOfInterest;
}


void Map::printMap(SDL_Renderer * renderer, std::vector<Vehicle> vehicles) {
	/**
	Prints Points of Interests and vehicles
	*/

	// Pre allocate memory for variables used in the function
	bool v = false;
	pointOfInterestType type = pointOfInterestType::Floor;
	Position pos;
	std::vector<Position> path;
	pos.x = 0;
	pos.y = 0;

	SDL_Rect rect, darea;

	/* Get the Size of drawing surface */
	SDL_RenderGetViewport(renderer, &darea);

	// Iteration over each row
	for (size_t y = 0; y < height; y++) {
		// Iteration over each column
		for (size_t x = 0; x < width; x++) {
			type = map[y * width + x].getPointOfInterestType(); // Get the type of the point of interest
			v = false; // Variable to keep track whether to print the vehicle or point of interest type

			// Iterate over all the vehicles in the vector
			for (Vehicle vehicle : vehicles) {
				pos = vehicle.getPosition(); // Get the position of the vehicle
				if (pos.x == x && pos.y == y) { // Check whether the position of the vehicle is equal to the current map position in the iteration
					SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);  // Print that there is a Vehicle
					v = true; // There is a vehicle, so we don't want to print the point of interest type
					break; // Stop the for loop because there shouldn't be multiple vehicles on a position.
				}

				// Iterate over all the paths in the vector
				if (v == false) {
					path = *vehicle.getPath();
					for (Position coordinate : path) {
						if (coordinate.x == x && coordinate.y == y) { // Check whether the position of the path is equal to the current map position in the iteration
							SDL_SetRenderDrawColor(renderer, 200, 160, 40, 0xFF);  // Print that there is a path
							v = true; // There is a path, so we don't want to print the point of interest type
							break; // Stop the for loop because there shouldn't be multiple paths on a position.
						}
					}
				}
			}



			if (v == false) { // If there is no vehicle on the current position, then we print the point of interest type
				if (type == pointOfInterestType::Floor) {
					SDL_SetRenderDrawColor(renderer, 126, 110, 90, 0xFF);
				}
				else if (type == pointOfInterestType::Wall) {
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
				}
				else if (type == pointOfInterestType::DropOff) {
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0xFF);
				}
				else { // if the point of interest type is unknown we throw an exception
					throw std::runtime_error("Requested type can't be printed - class Map PrintMap()\n");
				}
			}

			rect.w = darea.w / (int) width;
			rect.h = darea.h / (int) height;
			rect.x = (int) x * rect.w;
			rect.y = (int) y * rect.h;
			SDL_RenderFillRect(renderer, &rect);
		}
	}
}
