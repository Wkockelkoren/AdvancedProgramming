#ifndef VEHICLE_H
#define VEHICLE_H

#include "Structures.h"



class Vehicle {
private:
	size_t x;
	size_t y;
	size_t maxSpeed;
	std::vector<Position> path;
public:
	Vehicle(size_t x1 = 0, size_t y1 = 0, size_t maxSpeed1 = 1);
	
	bool working = false;

	void printCoords();

	void setPosition(size_t x1, size_t y1);

	Position getPosition();

	void printMaxSpeed();

	void setMaxSpeed(size_t maxSpeed1);

	size_t getMaxSpeed();

	void moveNextPathPosition();

	void setPath(std::vector<Position> &generatedpath);

	std::vector<Position>* getPath();

	bool checkIfWorking();

};

#endif
