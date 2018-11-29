
#include <iostream>
#include <vector>
#include "Map.h"
#include "PointOfInterest.h"



Map::Map(int width, int height) : width(width), height(height) {
	map = new PointOfInterest[width*height];

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			map[y * width + x].x = x;
			map[y * width + x].y = y;
		}
	}

	width;
	height;
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

	PointOfInterest& pointOfInterest = map[y * width + x];
	return pointOfInterest;
}

void Map::printMap() {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			pointOfInterestType type = map[y * width + x].getPointOfInterestType();

			if (type == pointOfInterestType::Path) {
				std::cout << "_ ";
			}
			else if (type == pointOfInterestType::Wall) {
				std::cout << "X ";
			}
			else if (type == pointOfInterestType::DropOff) {
				std::cout << "D ";
			}
			else {
				throw std::runtime_error("Requested type can't be printed - class Map PrintMap()\n");
			}

			if (x == width - 1) {
				std::cout << "\n";
			}
		}
	}
}