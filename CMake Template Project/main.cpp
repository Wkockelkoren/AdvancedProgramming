#include <iostream>
#include <vector>

class Vehicle {

};

class PointOfInterest {

};

class Map {
	private:
		std::vector<Vehicle> vehicleList;
		std::vector<PointOfInterest> poiList;

	public:
		const int width;
		const int height;
	
	Map::Map(int width, int height) : width(width), height(height) {
		width;
		height;
	}
};



int main()
{
	printf("Hello World!\n");
	printf("\n");

	Map factory = Map(10, 10);
	std::cout << factory.height;

	system("pause");
}