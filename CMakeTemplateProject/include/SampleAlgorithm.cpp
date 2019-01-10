#include "SampleAlgorithm.h"

void SampleAlgorithm::addNewCoordinate(Map &map, const Coordinate newCoordinate, const Position endPosition, const size_t &iterator,
	std::vector<Coordinate> &pathList) {
	/**this function checks if the requested coordinate is the start coordinate or if there is an obstacle at the requested position.
	If both is not the case the coordinate gets added to the argument pathlist
	*/
	for (size_t it = 0; it < pathList.size(); it++) {
		if ((newCoordinate.x == pathList[iterator].x) && (newCoordinate.y == pathList[iterator].y)) {
			existsAlready = true;
		}
	}
	//now check if there is no obstacle at the new coordinate on the map
	for (size_t it = 0; it < pathList.size(); it++) {
		if ((newCoordinate.x == pathList[it].x) && (newCoordinate.y == pathList[it].y)) {
			existsAlready = true;
		}
	}

	bool obstacle = false;
	try {
		obstacle = map.getPointOfInterest(newCoordinate.x, newCoordinate.y).getIsObstacle();
	}
	catch (std::exception const& e) {// will be removed later is just for testing exeptions
		std::cout << e.what();
	}
	if (obstacle == false && SampleAlgorithm::existsAlready == false) {
		pathList.push_back(newCoordinate);
		SampleAlgorithm::coordinateAdded = true;
		//stop looping when the right location is found
		if ((newCoordinate.x == endPosition.x) && (newCoordinate.y == endPosition.y)) {
			SampleAlgorithm::startPointReached = true;
		}
	}
	SampleAlgorithm::existsAlready = false;
}



std::vector<Coordinate> SampleAlgorithm::calculateListOfPaths(Map &map, Position startPosition, Position endPosition) {
	/**This function generates a vector of coordinates. It starts with the start coordinate and
	then it checks every coordinate adjacent to the start coordinate. If the coordinate is no
	obstacle and within boundaries it adds the coordinate to a list. Next, this action also happens
	with every new coordinate in the list untill the end position is found.
	*/
	std::vector<Coordinate> pathList;
	Coordinate coordinate;

	//reset highest counter
	highestCounter = 0;

	//Place startCoordinate in list
	coordinate.x = startPosition.x;
	coordinate.y = startPosition.y;
	coordinate.counter = 0;
	pathList.push_back(coordinate);

	std::cout << "generating path\n";

	while (startPointReached == false) { //loop as long a the start point is nog reached
		size_t listSize = pathList.size(); // get the list size in order to loop through every index
		coordinateAdded = false;

		for (size_t i = 0; i < listSize; i++) { //loop through every index in the pathlist
			if (pathList[i].counter == highestCounter) { //only add coordinates add the 'newest' coordinates

				//obtain new coordinate to the right of current coordinate
				if (pathList[i].x < (map.width - 1)) { //check if coordinate is not higher than the upper boundary (upper boundary x= map width - 1)
					coordinate.x = pathList[i].x + 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					addNewCoordinate(map, coordinate, endPosition, i, pathList);
				}
				//obtain new coordinate beneath current coordinate
				if (pathList[i].y < (map.height - 1)) { //check if coordinate is not higher than the upper boundary (upper boundary y= map height - 1)
					coordinate.x = pathList[i].x;
					coordinate.y = pathList[i].y + 1;
					coordinate.counter = highestCounter + 1;
					addNewCoordinate(map, coordinate, endPosition, i, pathList);
				}
				//obtain new coordinate left to current coordinate
				if (pathList[i].x > 0) { //check if coordinate is not higher than the upper boundary (lower boundary = 0)
					coordinate.x = pathList[i].x - 1;
					coordinate.y = pathList[i].y;
					coordinate.counter = highestCounter + 1;
					addNewCoordinate(map, coordinate, endPosition, i, pathList);
				}
				//obtain new coordinae above the current coordinate
				if (pathList[i].y > 0) { //check if coordinate is not higher than the upper boundary (lower boundary = 0)
					coordinate.x = pathList[i].x;
					coordinate.y = pathList[i].y - 1;
					coordinate.counter = highestCounter + 1;
					addNewCoordinate(map, coordinate, endPosition, i, pathList);
				}
			}
		}
		highestCounter++; //this counter is being used to add the neighbours next to the last added coordinates
	}
	return pathList;
}


std::vector<Position> SampleAlgorithm::getSinglePath(std::vector<Coordinate> &pathList, Position start) {
	//Reduce the pathList to list with steps to take

	/** This function returns a generated path from the output of the calculateListOfPahts function.
	The output of the calcaluteListOfPaths is a vector that contains the actual path and
	a set of unfinished path that don't lead to the right direction. This function searches
	for the actual path and returns that.
	*/

	size_t currentCounter = 0;

	bool added = false;
	Position currentPosition = { NULL , NULL };
	std::vector<Position> generatedPath;

	//Find startposition and counter by looping through pathList and comparing to startposition
	for (size_t i = 0; i < pathList.size(); i++) {
		if (pathList[i].x == start.x) {
			if (pathList[i].y == start.y) {
				currentCounter = pathList[i].counter;
				currentPosition.x = pathList[i].x;
				currentPosition.y = pathList[i].y;

				generatedPath.push_back(currentPosition);
			}
		}
	}

	while (currentCounter != 0) {
		for (size_t i = 0; i < pathList.size(); i++) {
			added = false;
			if (pathList[i].counter < currentCounter) {
				if ((pathList[i].x == (currentPosition.x + 1)) && (pathList[i].y == currentPosition.y) && added == false) {
					currentPosition.x = pathList[i].x;
					currentPosition.y = pathList[i].y;
					currentCounter = pathList[i].counter;
					generatedPath.push_back(currentPosition);
					added = true;
				}
				if ((pathList[i].x == (currentPosition.x - 1)) && (pathList[i].y == currentPosition.y) && added == false) {
					currentPosition.x = pathList[i].x;
					currentPosition.y = pathList[i].y;
					currentCounter = pathList[i].counter;
					generatedPath.push_back(currentPosition);
					added = true;
				}
				if ((pathList[i].y == (currentPosition.y + 1)) && (pathList[i].x == currentPosition.x) && added == false) {
					currentPosition.x = pathList[i].x;
					currentPosition.y = pathList[i].y;
					currentCounter = pathList[i].counter;
					generatedPath.push_back(currentPosition);
					added = true;
				}
				if ((pathList[i].y == (currentPosition.y - 1)) && (pathList[i].x == currentPosition.x) && added == false) {
					currentPosition.x = pathList[i].x;
					currentPosition.y = pathList[i].y;
					currentCounter = pathList[i].counter;
					generatedPath.push_back(currentPosition);
					added = true;
				}
			}
		}
	}
	return generatedPath;
}


std::vector<Position> SampleAlgorithm::createPath(const Position startPosition, const Position dropOff, Map &map) {
	/**
		this public function can be called in order to generate a path.
	*/
	/*
	this public function can be called in order to generate a path. it uses the private function
	"ListOfPaths" to generate a vector with 1 path from start to end, and with paths that dont lead
	to the right location. The function generatePath uses this list and returns only the correct path
	*/
	std::vector<Coordinate>	listOfPaths = calculateListOfPaths(map, dropOff, startPosition);
	std::vector<Position> generatedPath = getSinglePath(listOfPaths, startPosition);
	return generatedPath;
}
