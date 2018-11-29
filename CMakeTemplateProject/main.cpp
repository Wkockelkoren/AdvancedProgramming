#include <iostream>
#include <vector>
#include "Map.h"
#include "Vehicle.h"

int main()
{
	printf("Hello World!\n");
	printf("\n");

	Map factory(10, 10);
	
	
	std::vector<Vehicle> vehicles;
	/*Vehicle car(2,2);
	Vehicle bike(6, 6);
	vehicles.push_back(car);
	vehicles.push_back(bike);*/

	try {
		factory.getPointOfInterest(0, 5).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(9, 6).setPointOfInterestType(pointOfInterestType::DropOff);
		factory.getPointOfInterest(4, 2).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 3).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 4).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 5).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 6).setPointOfInterestType(pointOfInterestType::Wall);
		factory.getPointOfInterest(4, 7).setPointOfInterestType(pointOfInterestType::Wall);
	}
	catch (std::exception const& e) {// will be removed later is just for testing exeptions
		std::cout << e.what();
	}
	factory.printMap(vehicles);

	system("pause");

}