#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>
#include "Structures.h"
/**
* Has a position on the Map and contains a path that was generated
* by the VehicleManager. A Path consists out of multiple Positions (vector of Positions)
* where the first element in the vector will be the start position and the last element
* the end position. In the Editor view it is possible to add and edit multiple vehicles
* with each a different start and end position.
* @endcode
*/
class Vehicle {
private:
	Position position;
	std::vector<Position> path;
	Task task;
	bool working = false;

public:
	/**
	Constructor for map
	*/
	Vehicle(Position pos = {0,0});	

	/**
	Get the current position of the Vehicle on the Map
	*/
	Position getPosition();

	/**
	A vehicle uses this function to change its position by usage of an assigned path
	*/
	void moveNextPathPosition();

	/**
	Pass generated path to vehicle
	*/
	void setPath(std::vector<Position> &generatedpath);

	/**
	Returns path assigned to current vehicle
	*/
	std::vector<Position>* getPath();

	/**
	Pass generated path to vehicle
	*/
	void setWorking(bool isWorking);

	/**
	Check whether a Vehicle is working (driving)
	*/
	bool getWorking();

	/**
	Get the task that is currently assigned to the vehicle
	*/
	Task* getTask();

	/**
	Pass a task to the vehicle
	*/
	void setTask(Task task1);

	/**
	Check whether the vehicle position is equal to the goal position of the task
	*/
	bool isAtTaskGoalPosition();

	/**
	Check whether the vehicle position is equal to the start position of the task
	*/
	bool isAtTaskStartPosition();

	/**
	Check whether the task of the vehicle has a start position
	*/
	bool hasStartPosition();
};

#endif
