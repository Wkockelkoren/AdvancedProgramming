#include <iostream>
#include <vector>
#include <array>
#include "Map.h"

struct Coordinate {
	int x;
	int y;
	int counter;
} coordinate;

std::vector<Coordinate> pathList;

int main()
{
	printf("Hello World!\n");
	printf("\n");

	Map factory(10,10);

	factory.getPointOfInterest(0, 5).setPointOfInterestType(pointOfInterestType::DropOff);
	factory.getPointOfInterest(9, 6).setPointOfInterestType(pointOfInterestType::DropOff);
	factory.getPointOfInterest(4, 2).setPointOfInterestType(pointOfInterestType::Wall);
	factory.getPointOfInterest(4, 3).setPointOfInterestType(pointOfInterestType::Wall);
	factory.getPointOfInterest(4, 4).setPointOfInterestType(pointOfInterestType::Wall);
	factory.getPointOfInterest(4, 5).setPointOfInterestType(pointOfInterestType::Wall);
	factory.getPointOfInterest(4, 6).setPointOfInterestType(pointOfInterestType::Wall);
	factory.getPointOfInterest(4, 7).setPointOfInterestType(pointOfInterestType::Wall);

	factory.printMap();

	//build empty map
	int xUpperBound = factory.width - 1; //upper bound is biggest permissable x coordinate
	int xLowerBound = 0;
	int yUpperBound = factory.height - 1;
	int yLowerBound = 0;

	//get PoI locations
	PointOfInterest start = factory.getPointOfInterest(1, 0);
	PointOfInterest end = factory.getPointOfInterest(3, 0);

	PointOfInterest wall1 = factory.getPointOfInterest(2, 0);
	PointOfInterest wall2 = factory.getPointOfInterest(2, 1);
	PointOfInterest wall3 = factory.getPointOfInterest(2, 2);

	//set PoI
	start.setPointOfInterestType(DropOff); //StartPoint was changed to DropOff !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	end.setPointOfInterestType(DropOff);
	wall1.setPointOfInterestType(Wall);
	wall1.setIsObstacle(true);
	wall2.setPointOfInterestType(Wall);
	wall2.setIsObstacle(true);
	wall3.setPointOfInterestType(Wall);
	wall3.setIsObstacle(true);


	//path finding algorithm (sample algorithm) 
	//set startpoint
	coordinate.x = end.x;
	coordinate.y = end.y;
	coordinate.counter = 0;

	int highestCounter = 0;
	pathList.push_back(coordinate);

	bool startPointReached = false;

	// denk er aan, jullie zetten dubbele coordinaten neer vanwege het doorschrijven
	// jullie hebben nu een error die aan het de vorige bug van de jacco en wouter kan liggen

	while (startPointReached == false) { //loop as long a the start point is nog reached
		int listSize = pathList.size(); // get the list size in order to loop through every index 

		for (int i = 0; i < listSize; i++) { //loop through every index in the pathlist
			if (pathList[i].counter == highestCounter) { //only add coordinates add the 'newest' coordinates
				//every if statements first:
					// check if neighbour is within the map boundaries
					// save new coordinate
					// if coordinate is no obstacle, add it and check if startpoint
				if ((pathList[i].x + 1) <= xUpperBound) {
					coordinate.x = pathList[i].x + 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					if (factory.getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						if ((coordinate.x == start.x) && (coordinate.y == start.y)) {
							startPointReached = true;
						}
					}
				}
				if ((pathList[i].y + 1) <= yUpperBound) {
					coordinate.x = pathList[i].x;
					coordinate.y = pathList[i].y + 1;
					coordinate.counter = highestCounter + 1;
					if (factory.getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						if ((coordinate.x == start.x) && (coordinate.y == start.y)) {
							startPointReached = true;
						}
					}
				}
				if ((pathList[i].x - 1) >= xLowerBound) {
					coordinate.x = pathList[i].x - 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					if (factory.getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						if ((coordinate.x == start.x) && (coordinate.y == start.y)) {
							startPointReached = true;
						}
					}
				}
				if ((pathList[i].y - 1) >= yLowerBound) {
					coordinate.x = pathList[0].x;
					coordinate.y = pathList[0].y - 1;
					coordinate.counter = highestCounter + 1;
					if (factory.getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						if ((coordinate.x == start.x) && (coordinate.y == start.y)) {
							startPointReached = true;
						}
					}
				}

			}

		}
		highestCounter++;
	}

	//print PoI
	std::cout << "start (" << start.x << "," << start.y << ")\n";
	std::cout << "dropoff (" << end.x << "," << end.y << ")\n";

	//print if start pointed reached
	if (startPointReached) {
		std::cout << "start point reached \n";
	}
	else {
		std::cout << "no start point found \n";
	}

	//print coordinates and map
	int vectorSize = pathList.size();
	for (int i = 0; i < vectorSize; i++) {
		std::cout << "coordinate: " << i;
		std::cout << "\n\tx: " << pathList[i].x;
		std::cout << "\n\ty: " << pathList[i].y;
		std::cout << "\n\tcounter: " << pathList[i].counter;
		std::cout << "\n";
	}
	factory.printMap();
	system("pause");

}