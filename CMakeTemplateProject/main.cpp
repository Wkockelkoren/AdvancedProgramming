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

		void printCoords() {
			std::cout << "(" << x << "," << y << ")\n";
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
		PointOfInterest *map;
		//std::vector<PointOfInterest> poiList;

	public:
		const int width;
		const int height;

		Map(int width, int height) : width(width), height(height){
			map = new PointOfInterest[width*height];
			
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
					map[y * width + x].x = x;
					map[y * width + x].y = y;
				}
			}
		
			width;
			height;
		}

		~Map() {
			delete[] map;
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

			PointOfInterest& pointOfInterest = map[y * width + x];
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