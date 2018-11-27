#include <iostream>
#include <vector>
#include <string>

//enum used to choice state
enum State {
	error = -1,
	default = 0,
	MapEditor = 1,
	TaskManager = 2, 
	AddVehicle = 3, 
	ExistingVehicle = 4, 
	Go = 5,
	Stop = 6
} ;

//variables
std::string userInput;

//prototypes
bool checkUserInput(std::string userInput, const std::vector<std::string> *possibleInput);
State choiceTab(std::string desiredEnum);

int main()
{
	//ask user to select state
	printf("Possible states are: Map Editor, Task Manager, Add Vehicle, and go \n");
	printf("Please select the desired state: ");

	getline(std::cin, userInput); // get user input
	
	//switch statement which executes functions corresponding to states
	switch (choiceTab(userInput)) {
		case MapEditor:
			std::cout << "Map editor\n";
			break;

		case TaskManager:
			std::cout << "Task Manager\n";
			break;

		case AddVehicle:
			std::cout << "Add Vehicle\n";
			break;

		case ExistingVehicle:
			std::cout << "Existing Vehicle\n";
			break;

		case Go:
			std::cout << "Go\n";
			break;
			
		case Stop:
			std::cout << "Stopping\n";
			return 0;
			break;

		case error:
			std::cout << "Error\n";

		default:
			std::cout << "Bye\n";
			break;

	}

}

bool checkUserInput(std::string userInput, const std::vector<std::string> *possibleInput) {
	bool validityInput = false; //variable for returning whether an input is valid (false) or invalid (true)
	//obtain size of vector "possible inputs"
	int size = (*possibleInput).size();
	
	//loop through possibilites to check wether to input is valid or not
	for (int i = 0; size > i; i++) {
		if (userInput == (*possibleInput).at(i)) {
			return true;
			
		}
		else {
			validityInput = false;
		}
	}
	return false;
}
State choiceTab(std::string desiredEnum) {
	if (desiredEnum == "default") {
		return default;
	}
	else if ((desiredEnum == "map editor") ||
		(desiredEnum == "Map Editor") ||
		(desiredEnum == "MapEditor")) {
		return MapEditor;
	}
	else if ((desiredEnum == "task manager") ||
		(desiredEnum == "Task Manager") ||
		(desiredEnum == "TaskManager")) {
		return TaskManager;
	}
	else if ((desiredEnum == "add vehicle") ||
		(desiredEnum == "Add Vehicle") ||
		(desiredEnum == "AddVehicle")){
		return AddVehicle;
	}
	else if ((desiredEnum == "existing vehicle") ||
		(desiredEnum == "Existing Vehicle") ||
		(desiredEnum == "ExistingVehicle")) {
		return ExistingVehicle;
	}
	else if ((desiredEnum == "Go") ||
		(desiredEnum == "go")) {
		return Go;
	}
	else if ((desiredEnum == "stop") ||
		(desiredEnum == "Stop")) {
		return Stop;
	}
	else {
		return error;
	}
}

