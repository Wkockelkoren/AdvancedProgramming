#include <iostream>
#include <vector>
#include "Map.h"
#include "Vehicle.h"

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

	system("pause");

}