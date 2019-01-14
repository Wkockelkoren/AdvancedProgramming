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
	Contains the class Map.
*/
class Map {
private:
	std::unique_ptr<PointOfInterest[]> map;

public:
	/**
		Width of the Map
	*/
	const size_t width;

	/**
		Height of the Map
	*/
	const size_t height;

	/**
		Constructor for Map
	*/
	Map(size_t width, size_t height);

	/**
		Destructor for Map
	*/
	~Map();

	/**
		Get point of interest from position on Map
	*/
	PointOfInterest& getPointOfInterest(size_t x, size_t y);

	/**
		Prints Points of Interests and Vehicles
	*/
	void printMap(SDL_Renderer * renderer, std::vector<Vehicle> vehicles);
};

#endif