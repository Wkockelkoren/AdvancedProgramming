#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <memory>
#include "PointOfInterest.h"
#include "Vehicle.h"
#include "SDL.h"
#include "Structures.h"
#undef main 

class Map {
private:
	std::unique_ptr<PointOfInterest[]> map;

public:
	const size_t width;
	const size_t height;

	Map(size_t width, size_t height);

	~Map();

	PointOfInterest& getPointOfInterest(size_t x, size_t y);

	void printMap(SDL_Renderer * renderer, std::vector<Vehicle> vehicles);
};

#endif