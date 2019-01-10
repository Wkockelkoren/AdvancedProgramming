#ifndef VEHICLE_H
#define VEHICLE_H

#include "Structures.h"

class Vehicle {
private:
	Position position;
	size_t maxSpeed;
	std::vector<Position> path;

public:
	Vehicle(Position pos = {0,0}, size_t maxSpeed1 = 1);

	bool working = false;

	void printCoords();

	void setPosition(Position pos);

	Position getPosition();

	void printMaxSpeed();

	void setMaxSpeed(size_t maxSpeed1);

	size_t getMaxSpeed();

	bool moveNextPathPosition();

	void setPath(std::vector<Position> &generatedpath);

	std::vector<Position>* getPath();

	bool checkIfWorking();
};

#endif
