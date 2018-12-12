#include "VehicleManager.h"


VehicleManager::VehicleManager(){
	
}


VehicleManager::~VehicleManager(){
}

void VehicleManager::addVehicle(const int xPosition, const int yPosition,const double vehicleSpeed) {
	/** This function can be used to add a vehicle.
	*/
	Vehicle vehicle(xPosition, yPosition, vehicleSpeed);
	listOfVehicles.push_back(vehicle);
}


void VehicleManager::addNewCoordinate(Map &map, const Coordinate newCoordinate,const Position endPosition, const int &iterator,
	std::vector<Coordinate> &pathList, bool &startPointReached,bool &coordinateAdded, bool &existsAlready) {
	/**this function checks if the requested coordinate is the start coordinate or if there is an obstacle at the requested position. 
	If both is not the case the coordinate gets added to the argument pathlist
	*/
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
	if (map.getPointOfInterest(newCoordinate.x, newCoordinate.y).getIsObstacle() == false && existsAlready == false) {
		pathList.push_back(newCoordinate);
		coordinateAdded = true;
		//stop looping when the right location is found
		if ((newCoordinate.x == endPosition.x) && (newCoordinate.y == endPosition.y)) {
			startPointReached = true;
		}
	}
	existsAlready = false;
}


std::vector<Coordinate> VehicleManager::calculateListOfPaths(Map &map, Position startPosition, Position endPosition) {
		/**This function generates a vector of coordinates. It starts with the start coordinate and
		then it checks every coordinate adjacent to the start coordinate. If the coordinate is no
		obstacle and within boundaries it adds the coordinate to a list. Next, this action also happens
		with every new coordinate in the list untill the end position is found.
		*/
		std::vector<Coordinate> pathList;
		Coordinate coordinate;

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
	
			for (int i = 0; i < listSize ; i++) { //loop through every index in the pathlist
				if (pathList[i].counter == highestCounter) { //only add coordinates add the 'newest' coordinates

					//obtain new coordinate to the right of current coordinate
					if ((pathList[i].x + 1) <= map.width - 1) { //check if coordinate is not higher than the upper boundary (upper boundary x= map width - 1)
						coordinate.x = pathList[i].x + 1;
						coordinate.y = pathList[i].y;
						coordinate.counter = highestCounter + 1;
						addNewCoordinate(map, coordinate, endPosition, i, pathList, startPointReached, coordinateAdded, existsAlready);
					}
					//obtain new coordinate above current coordinate
					if ((pathList[i].y + 1) <= map.height - 1) { //check if coordinate is not higher than the upper boundary (upper boundary y= map height - 1)
						coordinate.x = pathList[i].x;
						coordinate.y = pathList[i].y + 1;
						coordinate.counter = highestCounter + 1;
						addNewCoordinate(map, coordinate, endPosition, i, pathList, startPointReached, coordinateAdded, existsAlready);
					}
					//obtain new coordinate left to current coordinate
					if ((pathList[i].x - 1) >= 0) { //check if coordinate is not higher than the upper boundary (lower boundary = 0)
						coordinate.x = pathList[i].x - 1;
						coordinate.y = pathList[i].y;
						coordinate.counter = highestCounter + 1;
						addNewCoordinate(map, coordinate, endPosition, i, pathList, startPointReached, coordinateAdded, existsAlready);
					}
					//obtain new coordinae beneath the current coordinate
					if ((pathList[i].y - 1) >= 0) { //check if coordinate is not higher than the upper boundary (lower boundary = 0)
						coordinate.x = pathList[i].x;
						coordinate.y = pathList[i].y - 1;
						coordinate.counter = highestCounter + 1;
						addNewCoordinate(map, coordinate, endPosition, i, pathList, startPointReached, coordinateAdded, existsAlready);
					}
				}
			}
			highestCounter++; //this counter is being used to add the neighbours next to the last added coordinates
		}
		return pathList;
	}


std::vector<Position> VehicleManager::getSinglePath(std::vector<Coordinate> &pathList, Position start) {
		/** This function returns a generated path from the output of the calculateListOfPahts function. 
		The output of the calcaluteListOfPaths is a vector that contains the actual path and 
		a set of unfinished path that don't lead to the right direction. This function searches
		for the actual path and returns that.
		*/
		int currentCounter;
		bool added = false;
		Position currentPosition;
		std::vector<Position> generatedPath;

		//Find startposition and counter by looping through pathList and comparing to startposition
		for (int i = 0; i < pathList.size(); i++) {
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
			for (int i = 0; i < pathList.size(); i++) {
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

Vehicle VehicleManager::getAvailableVehicle() {
	/** This function searches for a vehicle that is not working and returns it
	*/
	std::vector<Vehicle> availableVehicles;
	std::vector<Position> generatedPath;
	int numberOfVehicles = listOfVehicles.size();
	//check how many vehicles are available
	for (int currentVehicle = 0; currentVehicle < numberOfVehicles; currentVehicle++) {
		if (listOfVehicles[currentVehicle].checkIfWorking() == false) {
			return listOfVehicles[currentVehicle];
		}
	}
	return 0;
}

void VehicleManager::countAvailableVehicles() {
	/** This function returns the number of vehicles that are not working
	*/
	int numberOfVehicles = listOfVehicles.size();
	numberOfAvailableVehicles = 0;
	for (int currentVehicle = 0; currentVehicle < listOfVehicles.size(); currentVehicle++) {
		if (listOfVehicles[currentVehicle].checkIfWorking() == false) {
			numberOfAvailableVehicles++;
		}
	}
}

void VehicleManager::assignPathToVehicle(const std::vector<Task> &currentTasks,const Position dropOff, Map &map) {
	/** 
	this public function can be called in order to generate a path for a specific vehicle. 
	*/
	countAvailableVehicles();

	if (currentTasks.size() >= numberOfAvailableVehicles && numberOfAvailableVehicles > 0) {
		Vehicle availableVehicle = getAvailableVehicle(); //first a vehicle that is not doing work is needed
		std::vector<Position> generatedPath = createPath(availableVehicle.getPosition(), currentTasks.front().goalPosition, map);
		availableVehicle.moveNextPathPosition();
	}
}

void VehicleManager::setTasks(Task newTask) {
	/** This setter can be used to assign a path to a vehicle
	*/
	listOfTasks.push_back(newTask);
	numberOfTasks++;
}


std::vector<Position> VehicleManager::createPath(const Position startPosition, const Position dropOff, Map &map) {
		/**
		this public function can be called in order to generate a path. 
		*/
		std::vector<Coordinate>	listOfPaths = calculateListOfPaths(map, dropOff, startPosition);
		std::vector<Position> generatedPath = getSinglePath(listOfPaths, startPosition);
		return generatedPath;
	}