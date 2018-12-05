#include "PathManager.h"


PathManager::PathManager(){
}


PathManager::~PathManager(){
}

void PathManager::addNewCoordinate(Map *map, const Coordinate newCoordinate,const Position endPosition, const int &iterator,
	std::vector<Coordinate> &pathList, bool &startPointReached,bool &coordinateAdded, bool &existsAlready) {
	//this function checks if the requested coordinate is the start coordinate of if there is an obstacle at the requested position
	for (int it = 0; it < pathList.size(); it++) {
		if ((newCoordinate.x == pathList[iterator].x) && (newCoordinate.y == pathList[iterator].y)) {
			existsAlready = true;
		}
	}
	//now check if there is no obstacle at the new coordinate on the map
	for (int it = 0; it < pathList.size(); it++) {
		if ((newCoordinate.x == pathList[it].x) && (newCoordinate.y == pathList[it].y)) {
			existsAlready = true;
		}
	}
	if (map->getPointOfInterest(newCoordinate.x, newCoordinate.y).getIsObstacle() == false && existsAlready == false) {
		pathList.push_back(newCoordinate);
		coordinateAdded = true;
		//stop looping when the right location is found
		if ((newCoordinate.x == endPosition.x) && (newCoordinate.y == endPosition.y)) {
			startPointReached = true;
		}
	}
	existsAlready = false;
}


std::vector<Coordinate> PathManager::generateListOfPaths(Map *map, Position startPosition, Position endPosition) {
		/*This function generates a vector of coordinates. It starts with the start coordinate and
		then it checks every coordinate adjacent to the start coordinate. If the coordinate is no
		obstacle and within boundaries it adds the coordinate to a list. Next, this action also happens
		with every new coordinate in the list untill the end position is found.
		*/
		std::vector<Coordinate> pathList;
		Coordinate coordinate;
		Boundary boundary;

		//define boundary
		boundary.xUpper = map->width - 1; //upper bound is biggest permissable x coordinate
		boundary.xLower = 0;
		boundary.yUpper = map->height - 1;
		boundary.yLower = 0;

		//control variables
		bool startPointReached = false;
		int highestCounter = 0;
		bool coordinateAdded = false;
		bool noPathPossible = false;
		bool existsAlready = false;

		//Place startCoordinate in list
		coordinate.x = startPosition.x;
		coordinate.y = startPosition.y;
		coordinate.counter = 0;
		pathList.push_back(coordinate);

		std::cout << "generating path\n";

		while ((startPointReached == false) && (noPathPossible == false)) { //loop as long a the start point is nog reached
			int listSize = pathList.size(); // get the list size in order to loop through every index
			coordinateAdded = false;

			for (int i = 0; i < listSize; i++) { //loop through every index in the pathlist
				if (pathList[i].counter == highestCounter) { //only add coordinates add the 'newest' coordinates

					//obtain new coordinate to the right of current coordinate
					if ((pathList[i].x + 1) <= boundary.xUpper) { //check iff new coordinate doesn't move outside the map
						coordinate.x = pathList[i].x + 1;
						coordinate.y = pathList[i].y;
						addNewCoordinate(map, coordinate, endPosition, i, pathList, startPointReached, coordinateAdded, existsAlready);
						}
						/*
						//checkNewCoordinate(map, coordinate, startPosition
						coordinate.counter = highestCounter + 1;
						for (int it = 0; it < pathList.size(); it++) {
							if ((coordinate.x == pathList[i].x) && (coordinate.y == pathList[i].y)) {
								existsAlready = true;
							}
						}
						//now check if there is no obstacle at the new coordinate on the map
						for (int it = 0; it < pathList.size(); it++) {
							if ((coordinate.x == pathList[it].x) && (coordinate.y == pathList[it].y)) {
								existsAlready = true;
							}
						}
						if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false && existsAlready == false) {
							pathList.push_back(coordinate);
							coordinateAdded = true;
							//stop looping when the right location is found
							if ((coordinate.x == endPosition.x) && (coordinate.y == endPosition.y)) {
								startPointReached = true;
							}
						}
						existsAlready = false;
					}
					*/
					//obtain new coordinate above current coordinate
					if ((pathList[i].y + 1) <= boundary.yUpper) { //check iff new coordinate doesn't move outside the map
						coordinate.x = pathList[i].x;
						coordinate.y = pathList[i].y + 1;
						coordinate.counter = highestCounter + 1;
						//now check if there is no obstacle at the new coordinate on the map
						for (int it = 0; it < pathList.size(); it++) {
							if ((coordinate.x == pathList[it].x) && (coordinate.y == pathList[it].y)) {
								existsAlready = true;
							}
						}
						if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false && existsAlready == false) {
							pathList.push_back(coordinate);
							coordinateAdded = true;
							//stop looping when the right location is found
							if ((coordinate.x == endPosition.x) && (coordinate.y == endPosition.y)) {
								startPointReached = true;
							}
						}
						existsAlready = false;
					}
					//obtain new coordinate left to current coordinate
					if ((pathList[i].x - 1) >= boundary.xLower) { //check iff new coordinate doesn't move outside the map
						coordinate.x = pathList[i].x - 1;
						coordinate.y = pathList[i].y;
						coordinate.counter = highestCounter + 1;
						//now check if there is no obstacle at the new coordinate on the map
						for (int it = 0; it < pathList.size(); it++) {
							if ((coordinate.x == pathList[it].x) && (coordinate.y == pathList[it].y)) {
								existsAlready = true;
							}
						}
						if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false && existsAlready == false) {
							pathList.push_back(coordinate);
							coordinateAdded = true;
							//stop looping when the right location is found
							if ((coordinate.x == endPosition.x) && (coordinate.y == endPosition.y)) {
								startPointReached = true;
							}
						}
						existsAlready = false;
					}
					//obtain new coordinae beneath the current coordinate
					if ((pathList[i].y - 1) >= boundary.yLower) { //check iff new coordinate doesn't move outside the map
						coordinate.x = pathList[i].x;
						coordinate.y = pathList[i].y - 1;
						coordinate.counter = highestCounter + 1;
						//now check if there is no obstacle at the new coordinate on the map
						for (int it = 0; it < pathList.size(); it++) {
							if ((coordinate.x == pathList[it].x) && (coordinate.y == pathList[it].y)) {
								existsAlready = true;
							}
						}
						if (map->getPointOfInterest(coordinate.x, coordinate.y).getIsObstacle() == false && existsAlready == false) {
							pathList.push_back(coordinate);
							coordinateAdded = true;
							//stop looping when the right location is found
							if ((coordinate.x == endPosition.x) && (coordinate.y == endPosition.y)) {
								startPointReached = true;
							}
						}
						existsAlready = false;
					}
					//clean map
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


std::vector<Coordinate> PathManager::generatePath(std::vector<Coordinate> &pathList, Position &start) {
		//Reduce the pathList to list with steps to take
		int currentCounter;
		bool added = false;
		Coordinate currentCoordinate;
		std::vector<Coordinate> generatedPath;

		//Find startposition and counter by looping through pathList and comparing to startposition
		for (int i = 0; i < pathList.size(); i++) {
			if (pathList[i].x == start.x) {
				if (pathList[i].y == start.y) {
					currentCounter = pathList[i].counter;
					currentCoordinate = pathList[i];
					generatedPath.push_back(currentCoordinate);
				}
			}
		}

		while (currentCounter != 0) {
			for (int i = 0; i < pathList.size(); i++) {
				added = false;
				if (pathList[i].counter < currentCounter) {
					if ((pathList[i].x == (currentCoordinate.x + 1)) && (pathList[i].y == currentCoordinate.y) && added == false) {
						currentCoordinate.x = pathList[i].x;
						currentCoordinate.y = pathList[i].y;
						currentCoordinate.counter = pathList[i].counter;
						currentCounter = pathList[i].counter;
						generatedPath.push_back(currentCoordinate);
						added = true;
					}
					if ((pathList[i].x == (currentCoordinate.x - 1)) && (pathList[i].y == currentCoordinate.y) && added == false) {
						currentCoordinate.x = pathList[i].x;
						currentCoordinate.y = pathList[i].y;
						currentCoordinate.counter = pathList[i].counter;
						currentCounter = pathList[i].counter;
						generatedPath.push_back(currentCoordinate);
						added = true;
					}
					if ((pathList[i].y == (currentCoordinate.y + 1)) && (pathList[i].x == currentCoordinate.x) && added == false) {
						currentCoordinate.x = pathList[i].x;
						currentCoordinate.y = pathList[i].y;
						currentCoordinate.counter = pathList[i].counter;
						currentCounter = pathList[i].counter;
						generatedPath.push_back(currentCoordinate);
						added = true;
					}
					if ((pathList[i].y == (currentCoordinate.y - 1)) && (pathList[i].x == currentCoordinate.x) && added == false) {
						currentCoordinate.x = pathList[i].x;
						currentCoordinate.y = pathList[i].y;
						currentCoordinate.counter = pathList[i].counter;
						currentCounter = pathList[i].counter;
						generatedPath.push_back(currentCoordinate);
						added = true;
					}
				}
			}
		}
		return generatedPath;
	}


std::vector<Coordinate> PathManager::createPath(Position startPosition, Position dropOff, Map &map) {
	/* 
	this public function can be called in order to generate a path. it uses the private function 
	"ListOfPaths" to generate a vector with 1 path from start to end, and with paths that dont lead
	to the right location. The function generatePath uses this list and returns only the correct path
	*/
	std::vector<Coordinate>	listOfPaths = generateListOfPaths(&map, dropOff, startPosition);
	std::vector<Coordinate> generatedPath = generatePath(listOfPaths, startPosition);
	return generatedPath;
}