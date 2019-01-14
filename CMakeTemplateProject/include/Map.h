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
/**
	Contains the classes Map and PointOfInterest.
*/
class Map {
private:
	std::unique_ptr<PointOfInterest[]> map;

public:
	const size_t width;
	const size_t height;

	/**
	Constructor for map
	*/
	Map(size_t width, size_t height);

	/**
	Destructor for map
	*/
	~Map();

	/**
	Get point of interest from position on map
	*/
	PointOfInterest& getPointOfInterest(size_t x, size_t y);

	/**
	Prints Points of Interests and vehicles
	*/
	void printMap(SDL_Renderer * renderer, std::vector<Vehicle> vehicles);
};

#endif