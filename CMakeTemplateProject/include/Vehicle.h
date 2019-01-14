#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>
#include "Structures.h"

class Vehicle {
private:
	Position position;
	std::vector<Position> path;
	Task task;

public:
	Vehicle(Position pos = {0,0});

	bool working = false;

	Position getPosition();

	void moveNextPathPosition();

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
