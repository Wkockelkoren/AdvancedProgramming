#include <iostream>
#include <vector>


class Vehicle {

};


enum pointOfInterestType { Path, Wall, DropOff };

class PointOfInterest {
	private:
		bool isObstacle;
		pointOfInterestType type;

	public:
		int x;
		int y;
		PointOfInterest::PointOfInterest( int x1 = 0, int y1 = 0, pointOfInterestType pointType = pointOfInterestType::Path, bool obstacle = false ) {
			x = x1;
			y = y1;
			type = pointType;
			isObstacle = obstacle;
		}

		bool getIsObstacle() {
			return isObstacle;
		}

		void setIsObstacle(bool obstacle ) {
			isObstacle = obstacle;
		}

		pointOfInterestType getPointOfInterestType() {
			return type;
		}

		void setPointOfInterestType(pointOfInterestType pointType) {
			type = pointType;
		}
};


class Map {
	private:
		std::vector<Vehicle> vehicleList;
		//PointOfInterest *map;
		//std::vector<PointOfInterest> poiList;
		int * testarray;

	public:
		const int width;
		const int height;
		PointOfInterest *map;
		Map(int width, int height) : width(width), height(height){
			map = new PointOfInterest[width*height];
			
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					map[y * width + x].x = x;
					map[y * width + x].y = y;
				}
			}

			testarray = new int[width*height];
			//map = new PointOfInterest[width][height];
			//PointOfInterest map[width][height];
		
			//map = calloc(sizeof(PointOfInterest), width*height);
			//assert(map);
			width;
			height;
		}

		~Map() {
			delete[] map;
			delete[] testarray;
		}

		int& at(int i1, int i2) {
			return testarray[i1 * width + height];
		}

		PointOfInterest& getPointOfInterest(int x, int y) {
			//Check wether the requested point is within the map
			if (!(x < width) || !(x >= 0)) {
				std::cout << "\nRequested point of interest is not within the map\n\n";
				throw "Requested point of interest is not within the map - class Map getPointOfInterest()";
			}
			if (!(y < height) || !(y >= 0)) {
				std::cout << "\nRequested point of interest is not within the map\n\n";
				throw "Requested point of interest is not within the map - class Map getPointOfInterest()";
			}

			PointOfInterest pointOfInterest = map[y * width + x];
			return pointOfInterest;
		}

		void printMap() {
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					pointOfInterestType type = map[y * width + x].getPointOfInterestType();

					if (type == pointOfInterestType::Path) {
						std::cout << "_ ";
					}
					else if (type == pointOfInterestType::Wall) {
						std::cout << "X ";
					}
					else if (type == pointOfInterestType::DropOff) {
						std::cout << "D ";
					}
					else {
						throw "Requested type can't be printed - class Map PrintMap()";
					}

					if (x == width - 1) {
						std::cout << "\n";
					}
				}
			}
		}
};


int main()
{
	printf("Hello World!\n");
	printf("\n");

	Map factory(4,5);

	PointOfInterest point1 = factory.getPointOfInterest(3,4);
	std::cout <<"("<< point1.x << "," << point1.y << ")\n";



	//PointOfInterest testie(pointOfInterestType::Wall);
	//factory.getPointOfInterest(5, 5) = testie;
	//PointOfInterest aa = factory.getPointOfInterest(5, 5);
	//std::cout << aa.getPointOfInterestType();
	//
	//std::cout << "aa";
	//
	//Map test(10, 10);
	//test.at(2, 2) = 42;
	//std::cout << test.at(2, 2);
	//
	////factory.getPointOfInterest(1, 1).setPointOfInterestType(pointOfInterestType::Wall);
	////factory.getPointOfInterest(2, 2).setPointOfInterestType(pointOfInterestType::Wall);
	////factory.getPointOfInterest(4, 4).setPointOfInterestType(pointOfInterestType::Wall);
	////factory.getPointOfInterest(5, 5).setPointOfInterestType(pointOfInterestType::Wall);
	////factory.getPointOfInterest(7, 7).setPointOfInterestType(pointOfInterestType::Wall);
	////factory.getPointOfInterest(8, 8).setPointOfInterestType(pointOfInterestType::Wall);
	//
	//PointOfInterest point0 = factory.getPointOfInterest(1, 1);
	//point0.setPointOfInterestType(pointOfInterestType::Wall);
	//
	//
	//PointOfInterest point1 = factory.getPointOfInterest(2, 2);
	//point1.setPointOfInterestType(pointOfInterestType::Wall);
	//PointOfInterest point2 = factory.getPointOfInterest(4, 4);
	//point2.setPointOfInterestType(pointOfInterestType::Wall);
	//PointOfInterest point3 = factory.getPointOfInterest(5, 5);
	//point3.setPointOfInterestType(pointOfInterestType::Wall);
	//PointOfInterest point4 = factory.getPointOfInterest(7, 7);
	//point4.setPointOfInterestType(pointOfInterestType::Wall);
	//PointOfInterest point5 = factory.getPointOfInterest(8, 8);
	//point5.setPointOfInterestType(pointOfInterestType::Wall);

	//for (int i = 0; i < 10; i++) {
	//
	//	for (int j = 0; j < 10; j++) {
	//		PointOfInterest point = factory.getPointOfInterest(i,j);
	//		point.setPointOfInterestType(pointOfInterestType::Wall);
	//	}
	//}
	//std::cout << "print all:";
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 10; j++) {
	//		PointOfInterest point = factory.getPointOfInterest(i, j);
	//		//point.setPointOfInterestType(pointOfInterestType::Wall);
	//		std::cout <<point.getPointOfInterestType();
	//	}
	//}
	//std::cout << "End\n";

	factory.printMap();

	//PointOfInterest point1 = factory.getPointOfInterest(1, 1);
	//std::cout << "Point1 of interest type: " << point1.getPointOfInterestType() << "\n";

	//PointOfInterest point = factory.getPointOfInterest(3, 3);
	//point.setPointOfInterestType(pointOfInterestType::Wall);
	//std::cout << "\nPoint of interest type: " << point.getPointOfInterestType() << "\n";


	//std::cout << factory.map[13].getPointOfInterestType();

	//PointOfInterest point = factory.getPointOfInterest(2, 1);
	//std::cout << "Point of interest type: " << point.getPointOfInterestType() << "\n";
	//std::cout << "Point of interest obstacle: " << point.getIsObstacle() << "\n";

	//std::cout << "Point of interest type: " << factory.getPointOfInterest(1, 1).getPointOfInterestType()<< "\n\n";

	system("pause");
}