#ifndef MAP_H
#define MAP_H

#include "PointOfInterest.h"
#include "Vehicle.h"
#include "SDL.h"
#include "Structures.h"
#undef main



class Map {
private:
	PointOfInterest *map;

public:
	const int width;
	const int height;

	Map(int width, int height);

	~Map();

	PointOfInterest& getPointOfInterest(int x, int y);

	void printMap(SDL_Renderer * renderer, std::vector<Vehicle> vehicles);
};

#endif