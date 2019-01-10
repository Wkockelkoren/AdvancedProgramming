#include "Menu.h"

void MenuMain(size_t* menuMode) {
	std::cout << "--- Main ---\n";
	std::cout << "Select Menu Mode:\n";
	std::cout << "1. Task Manager\n";
	std::cout << "2. Vehicle Manager\n";
	std::cout << "3. Map Editor\n";
	std::cout << "4. Go\n";
	std::cout << "5. Exit\n\n";
	*menuMode = MenuUserInput("Input", 1, 5);
}

void MenuTaskManager(size_t* menuMode, Map& factory, TaskManager& taskManager){
	size_t userInputX = 0;
	size_t userInputY = 0;

	std::cout << "--- Task Manager ---\n";
	std::cout << "Options:\n";
	std::cout << "1. Add Task\n";
	std::cout << "2. Back\n\n";
	size_t subMenuMode = MenuUserInput("Input", 1, 2);

	switch (subMenuMode) {
	case 1: /* Add Task */
		std::cout << "Add Task:\n";

		userInputX = MenuUserInput("Give an X-position", 0, factory.width - 1);
		userInputY = MenuUserInput("Give an Y-position", 0, factory.height - 1);

		taskManager.createTask({ userInputX, userInputY });

		break;

	case 2: /* Go back to main menu */
		*menuMode = 0;
		break;

	default:
		*menuMode = 1;
		break;
	}
}

void MenuVehicleManager(size_t* menuMode, Map& factory, VehicleManager& vehicleManager) {
	size_t userInputX = 0;
	size_t userInputY = 0;

	std::cout << "--- Vehicle Manager ---\n";
	std::cout << "1. Add Vehicle \n";
	std::cout << "2. Back \n\n";
	size_t subMenuMode = MenuUserInput("Input", 1, 2);

	switch (subMenuMode) {
	case 1: /* Add vehicle */
		std::cout << "Add Vehicle:\n";
		userInputX = MenuUserInput("Give an X-position", 0, factory.width - 1);
		userInputY = MenuUserInput("Give an Y-position", 0, factory.height - 1);

		vehicleManager.addVehicle({ userInputX, userInputY }, 1);

	case 2: /* Go back to main menu */
		*menuMode = 0;
		break;

	default:
		*menuMode = 1;
		break;
	}
}

void MenuMapEditor(size_t* menuMode, Map& factory) {
	size_t userInputX = 0;
	size_t userInputY = 0;

	std::cout << "--- Map Editor ---\n";
	std::cout << "1. Place Wall \n";
	std::cout << "2. Place DropOff \n";
	std::cout << "3. Place Floor(Delete Wall/DropOff) \n";
	std::cout << "4. Back \n";
	size_t subMenuMode = MenuUserInput("Input", 1, 4);
	switch (subMenuMode) {
	case 1: /*Place Wall*/
		std::cout << "Add Wall:\n";
		userInputX = MenuUserInput("Give an X-position", 0, factory.width - 1);
		userInputY = MenuUserInput("Give an Y-position", 0, factory.height - 1);
		
		factory.getPointOfInterest(userInputX, userInputY).setPointOfInterestType(pointOfInterestType::Wall);
		break;
	case 2:/*Place DropOff*/
		std::cout << "Add DropOff:\n";
		userInputX = MenuUserInput("Give an X-position", 0, factory.width - 1);
		userInputY = MenuUserInput("Give an Y-position", 0, factory.height - 1);
		
		factory.getPointOfInterest(userInputX, userInputY).setPointOfInterestType(pointOfInterestType::DropOff);
		break;
	case 3:/*Place Floor*/
		std::cout << "Add Floor:\n";
		userInputX = MenuUserInput("Give an X-position", 0, factory.width - 1);
		userInputY = MenuUserInput("Give an Y-position", 0, factory.height - 1);

		factory.getPointOfInterest(userInputX, userInputY).setPointOfInterestType(pointOfInterestType::Floor);
		break;
	case 4:/*Back*/
		*menuMode = 0;
		break;
	default:
		std::cout << "Invalid input \n";
		break;
	}
}

size_t MenuUserInput(std::string text, size_t min, size_t max) {
	bool error = true;
	size_t input = 0;
	while (error) {
		std::cout << text.c_str() << " (" << min << " to " << max << "): ";
		std::cin >> input;
		if (input < min || input > max) {
			std::cout << "Input is out of range \n";
			error = true;
			continue;
		}
		error = false;
	}
	std::cout << "\n";
	return input;
}

