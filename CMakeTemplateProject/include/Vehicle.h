#ifndef VEHICLE_H
#define VEHICLE_H

#include "Structures.h"



class Vehicle {
private:
	int x;
	int y;
	double maxSpeed;
	std::vector<Position> path;
public:
	Vehicle(int x1 = 0, int y1 = 0, double maxSpeed1 = 1);
	
	bool working = false;

	void printCoords();

	void setPosition(int x1, int y1);

	Position getPosition();

	void printMaxSpeed();

	void setMaxSpeed(int maxSpeed1);

	double getMaxSpeed();

	void moveNextPathPosition();

	void setPath(std::vector<Position> &generatedpath);

	std::vector<Position>* getPath();

	bool checkIfWorking();

};

#endif
