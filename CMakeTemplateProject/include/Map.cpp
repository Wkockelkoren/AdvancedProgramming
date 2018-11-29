
#include <iostream>
#include <vector>
#include "Map.h"
#include "PointOfInterest.h"
#include "Vehicle.h"



Map::Map(int width, int height) : width(width), height(height) {
	map = new PointOfInterest[width*height];

	// Iterate over each position and fill in the coordinates in the point of interest
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			map[y * width + x].x = x;
			map[y * width + x].y = y;
		}
	}
}

Map::~Map() {
	delete[] map;
}


PointOfInterest& Map::getPointOfInterest(int x, int y) {
	//Check wether the requested point is within the map
	if (!(x < width) || !(x >= 0)) {
		throw std::runtime_error("Requested point of interest is not within the map - class Map getPointOfInterest()\n");
	}
	if (!(y < height) || !(y >= 0)) {
		throw std::runtime_error("Requested point of interest is not within the map - class Map getPointOfInterest()\n");
	}

	// Get point of interest and return it
	PointOfInterest& pointOfInterest = map[y * width + x];
	return pointOfInterest;
}

// TODO: find a method that we dont need to use multiple fuctions
void Map::printMap() {
	// If we have no vehicles we send an empty vector to the function
	std::vector<Vehicle> vehicles{};
	printMap(vehicles);
}

void Map::printMap(std::vector<Vehicle> vehicles ) {

	// Pre allocate memory for variables used in the function
	bool v = false;
	pointOfInterestType type = pointOfInterestType::Floor;
	Position pos = { 0,0 };

	// Iteration over each row
	for (int y = 0; y < height; y++) {
		// Iteration over each column
		for (int x = 0; x < width; x++) {
			type = map[y * width + x].getPointOfInterestType(); // Get the type of the point of interest
			v = false; // Variable to keep track whether to print the vehicle or point of interest type

			// Iterate over all the vehicles in the vector
			for (Vehicle vehicle : vehicles) {
				pos = vehicle.getPosition(); // Get the position of the vehicle
				if (pos.x == x && pos.y == y) { // Check whether the position of the vehicle is equal to the current map position in the iteration
					std::cout << "V ";  // Print that there is a Vehicle 
					v = true; // There is a vehicle, so we don't want to print the point of interest type
					break; // Stop the for loop because there shouldn't be multiple vehicles on a position.
				}
			}

			if (v == false) { // If there is no vehicle on the current position, then we print the point of interest type
				if (type == pointOfInterestType::Floor) {
					std::cout << "_ ";
				}
				else if (type == pointOfInterestType::Wall) {
					std::cout << "X ";
				}
				else if (type == pointOfInterestType::DropOff) {
					std::cout << "D ";
				}
				else { // if the point of interest type is unknown we throw an exception
					throw std::runtime_error("Requested type can't be printed - class Map PrintMap()\n");
				}
			}
			
			if (x == width - 1) { // If end of the rows we start printing on the next line
				std::cout << "\n";
			}
		}
	}
}