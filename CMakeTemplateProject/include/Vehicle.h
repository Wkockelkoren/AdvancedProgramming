#ifndef VEHICLE_H
#define VEHICLE_H

#include "Structures.h"



class Vehicle {
private:
	Position position;
	double maxSpeed;
	std::vector<Position> path;
public:
	Vehicle(Position pos = {0,0}, double maxSpeed1 = 1);
	
	bool working = false;

	void printCoords();

	void setPosition(Position pos);

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
