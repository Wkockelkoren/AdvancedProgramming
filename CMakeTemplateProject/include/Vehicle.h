#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>
#include "Structures.h"

class Vehicle {
private:
	Position position;
	size_t maxSpeed;
	std::vector<Position> path;
	Task task;

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

	Task* getTask();

	void setTask(Task task1);

	bool isAtTaskGoalPosition();

	bool isAtTaskStartPosition();

	bool hasStartPosition();
};

#endif
