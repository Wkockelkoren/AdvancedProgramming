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

std::vector<Coordinate> generateListOfPaths(Map *map, Position startPosition, Position endPosition, Boundary boundary);


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

	//define boundary
	boundary.xUpper = factory.width - 1; //upper bound is biggest permissable x coordinate
	boundary.xLower = 0;
	boundary.yUpper = factory.height - 1;
	boundary.yLower = 0;

	//path finding algorithm (sample algorithm) 
	std::vector<Coordinate>	listOfPaths = generateListOfPaths(&factory, dropOff, startPosition, boundary);
	

	//print start and dropoff location
	std::cout << "start (" << startPosition.x << "," << startPosition.y << ")\n";
	std::cout << "dropoff (" << dropOff.x << "," << dropOff.y << ")\n";

	//print coordinates and map
	int vectorSize = listOfPaths.size();
	for (int i = 0; i < vectorSize; i++) {
		std::cout << "coordinate: " << i;
		std::cout << "\n\tx: " << listOfPaths[i].x;
		std::cout << "\n\ty: " << listOfPaths[i].y;
		std::cout << "\n\tcounter: " << listOfPaths[i].counter;
		std::cout << "\n";
	}
	
	//factory.printMap();
	system("pause");

}

std::vector<Coordinate> generateListOfPaths(Map *map, Position startCoordinate, Position endCoordinate, Boundary boundary) {
	/*This function generates a vector of coordinates. It starts with the start coordinate and 
	then it checks every coordinate adjacent to the start coordinate. If the coordinate is no 
	obstacle and within boundaries it adds the coordinate to a list. Next, this action also happens
	with every new coordinate in the list untill the end position is found.
	*/
	std::vector<Coordinate> pathList;
	Coordinate coordinate;

	//control variables
	int startPointReached = false;
	int highestCounter = 0;
	bool coordinateAdded = false;
	bool noPathPossible = false;
	//Place startCoordinate in list
	coordinate.x = startCoordinate.x;
	coordinate.y = startCoordinate.y;
	coordinate.counter = 0;
	pathList.push_back(coordinate);

	std::cout << "generating path\n";

	while ((startPointReached == false) && (noPathPossible ==false)) { //loop as long a the start point is nog reached
		int listSize = pathList.size(); // get the list size in order to loop through every index 
		coordinateAdded = false;

		for (int i = 0; i < listSize; i++) { //loop through every index in the pathlist
			if (pathList[i].counter == highestCounter) { //only add coordinates add the 'newest' coordinates

				//obtain new coordinate to the right of current coordinate
				if ((pathList[i].x + 1) <= boundary.xUpper) { //check iff new coordinate doesn't move outside the map
					coordinate.x = pathList[i].x + 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					//now check if there is no obstacle at the new coordinate on the map
					if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						coordinateAdded = true;
						//stop looping when the right location is found
						if ((coordinate.x == endCoordinate.x) && (coordinate.y == endCoordinate.y)) {
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
					if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						coordinateAdded = true;
						//stop looping when the right location is found
						if ((coordinate.x == endCoordinate.x) && (coordinate.y == endCoordinate.y)) {
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
					if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						coordinateAdded = true;
						//stop looping when the right location is found
						if ((coordinate.x == endCoordinate.x) && (coordinate.y == endCoordinate.y)) {
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
					if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false) {
						pathList.push_back(coordinate);
						coordinateAdded = true;
						//stop looping when the right location is found
						if ((coordinate.x == endCoordinate.x) && (coordinate.y == endCoordinate.y)) {
							startPointReached = true;
						}
					}
				}
			}
		}
		highestCounter++;
	//	if (coordinateAdded == false) {
//			noPathPossible = true;
	//		throw std::runtime_error("No path found");
	//	}
	}
	return pathList;
}