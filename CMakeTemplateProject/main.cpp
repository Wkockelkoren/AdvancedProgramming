#include <iostream>
#include <vector>
#include <array>
#include "Map.h"

struct Position {
	double x = 0;
	double y = 0;
};
struct Coordinate {
	int x =0;
	int y =0;
	int counter=0;
};
struct Boundary {
	int xUpper = 0;
	int xLower = 0;
	int yUpper = 0;
	int yLower = 0;
} boundary;

std::vector<Coordinate> getListOfPaths(Map map, Position startPosition, Position endPosition, Boundary boundary);


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
	
	//get start position and dropoff position
	Position startPosition;
	startPosition.x = 1;
	startPosition.y = 0;

	Position dropOff;
	dropOff.x = 3;
	dropOff.y = 0;

	//build empty map
//edit this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	boundary.xUpper = factory.width - 1; //upper bound is biggest permissable x coordinate
	boundary.xLower = 0;
	boundary.yUpper = factory.height - 1;
	boundary.yLower = 0;

	//path finding algorithm (sample algorithm) 
	getListOfPaths(factory,dropOff,startPosition,boundary)





	// denk er aan, jullie zetten dubbele coordinaten neer vanwege het doorschrijven
	// jullie hebben nu een error die aan het de vorige bug van de jacco en wouter kan liggen

	

	//print PoI
	std::cout << "start (" << start.x << "," << start.y << ")\n";
	std::cout << "dropoff (" << end.x << "," << end.y << ")\n";

	//print coordinates and map
//	int vectorSize = pathList.size();
//	for (int i = 0; i < vectorSize; i++) {
//		std::cout << "coordinate: " << i;
//		std::cout << "\n\tx: " << pathList[i].x;
//		std::cout << "\n\ty: " << pathList[i].y;
//		std::cout << "\n\tcounter: " << pathList[i].counter;
//		std::cout << "\n";
//	}
	
	//factory.printMap();
	system("pause");

}

std::vector<Coordinate> getListOfPaths(Map map, Position startCoordinate, Position endCoordinate, Boundary boundary) {
	std::vector<Coordinate> pathList;
	Coordinate coordinate;

	//control variables
	int startPointReached = false;
	int highestCounter = 0;

	//Place startCoordinate in list
	coordinate.x = endCoordinate.x;
	coordinate.y = endCoordinate.y;
	coordinate.counter = 0;
	pathList.push_back(coordinate);

	while (startPointReached == false) { //loop as long a the start point is nog reached
		int listSize = pathList.size(); // get the list size in order to loop through every index 

		for (int i = 0; i < listSize; i++) { //loop through every index in the pathlist
			if (pathList[i].counter == highestCounter) { //only add coordinates add the 'newest' coordinates

				//obtain new coordinate to the right of current coordinate
				if ((pathList[i].x + 1) <= boundary.xUpper) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x + 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					//now check if there is no obstacle at the new coordinate on the map
					if (map.getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						//stop looping when the right location is found
						if ((coordinate.x == startCoordinate.x) && (coordinate.y == startCoordinate.y)) {
							startPointReached = true;
						}
					}
				}
				//obtain new coordinate above current coordinate
				if ((pathList[i].y + 1) <= boundary.yUpper) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x;
					coordinate.y = pathList[i].y + 1;
					coordinate.counter = highestCounter + 1;
					//now check if there is no obstacle at the new coordinate on the map
					if (map.getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						//stop looping when the right location is found
						if ((coordinate.x == startCoordinate.x) && (coordinate.y == startCoordinate.y)) {
							startPointReached = true;
						}
					}
				}
				//obtain new coordinate left to current coordinate
				if ((pathList[i].x - 1) >= boundary.xLower) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x - 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					//now check if there is no obstacle at the new coordinate on the map
					if (map.getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						//stop looping when the right location is found
						if ((coordinate.x == startCoordinate.x) && (coordinate.y == startCoordinate.y)) {
							startPointReached = true;
						}
					}
				}
				//obtain new coordinae beneath the current coordinate
				if ((pathList[i].y - 1) >= boundary.yLower) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x;
					coordinate.y = pathList[i].y - 1;
					coordinate.counter = highestCounter + 1;
					//now check if there is no obstacle at the new coordinate on the map
					if (map.getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						//stop looping when the right location is found
						if ((coordinate.x == startCoordinate.x) && (coordinate.y == startCoordinate.y)) {
							startPointReached = true;
						}
					}
				}

			}

		}
		highestCounter++;
	}
	return pathList;
}