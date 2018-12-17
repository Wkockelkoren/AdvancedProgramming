
#include <iostream>
#include <vector>
#include "Window.h"
#include "PointOfInterest.h"
#include "Map.h"

bool loadWindow(SDL_Window** window, int width, int height, SDL_Surface** surface, SDL_Renderer** renderer) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init fail : %s\n", SDL_GetError());
		return false;
	}

	*window = SDL_CreateWindow(
		"Path Planner",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		0
	);
	if (!*window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window creation fail : %s\n", SDL_GetError());
		return false;
	}

	*surface = SDL_GetWindowSurface(*window);
	*renderer = SDL_CreateSoftwareRenderer(*surface);
	if (!renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Render creation for surface fail : %s\n", SDL_GetError());
		return false;
	}

	/* Clear the rendering surface with the specified color */
	SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(*renderer);
	return true;
}

void createMainButtons( nanogui::Screen* screen, nanogui::Window* mainWindow, int &menuMode) {
	nanogui::Button *mainButStart = new nanogui::Button(mainWindow, "Start/Stop");
	nanogui::Button *mainButMapEditor = new nanogui::Button(mainWindow, "Map Editor");
	nanogui::Button *mainButVehicleEditor = new nanogui::Button(mainWindow, "Add Vehicle");
	nanogui::Button *mainButTaskManager = new nanogui::Button(mainWindow, "Add Tasks");

	mainButStart->setCallback([] {
		std::cout << "Start/Stop" << std::endl;
	});

	mainButMapEditor->setCallback([&] {
		menuMode = 2;

		//(mainWindow)->setVisible(false);
		//(mapEditorWindow)->setVisible(true);
	});

	mainButVehicleEditor->setCallback([&] {
		menuMode = 3;
	});
	
	mainButTaskManager->setCallback([&] {
		menuMode = 4;
	});

}

void createMapEditButtons(nanogui::Screen* screen, nanogui::Window* mapEditorWindow, int &menuMode, int &buttonMode, int &xField, int &yField) {
	nanogui::IntBox<int> *mapEditorXfield = new nanogui::IntBox<int>(mapEditorWindow);
	mapEditorXfield->setUnits("X");
	mapEditorXfield->setValue(10);
	mapEditorXfield->setEditable(true);
	mapEditorXfield->setMinValue(1);
	mapEditorXfield->setSpinnable(true);
	mapEditorXfield->setValueIncrement(1);

	nanogui::IntBox<int> *mapEditorYfield = new nanogui::IntBox<int>(mapEditorWindow);
	mapEditorYfield->setUnits("Y");
	mapEditorYfield->setValue(10);
	mapEditorYfield->setEditable(true);
	mapEditorYfield->setMinValue(1);
	mapEditorYfield->setSpinnable(true);
	mapEditorYfield->setValueIncrement(1);

	nanogui::Button *mapEditorButNewMap = new nanogui::Button(mapEditorWindow, "New Map");

	nanogui::IntBox<int> *mapEditorPoIXfield = new nanogui::IntBox<int>(mapEditorWindow);
	mapEditorPoIXfield->setUnits("X");
	mapEditorPoIXfield->setValue(10);
	mapEditorPoIXfield->setEditable(true);
	mapEditorPoIXfield->setMinValue(1);
	mapEditorPoIXfield->setSpinnable(true);
	mapEditorPoIXfield->setValueIncrement(1);

	nanogui::IntBox<int> *mapEditorPoIYfield = new nanogui::IntBox<int>(mapEditorWindow);
	mapEditorPoIYfield->setUnits("Y");
	mapEditorPoIYfield->setValue(10);
	mapEditorPoIYfield->setEditable(true);
	mapEditorPoIYfield->setMinValue(1);
	mapEditorPoIYfield->setSpinnable(true);
	mapEditorPoIYfield->setValueIncrement(1);

	nanogui::Button *mapEditorButNewFloor = new nanogui::Button(mapEditorWindow, "Place Floor");
	nanogui::Button *mapEditorButNewWall = new nanogui::Button(mapEditorWindow, "Place Wall");
	nanogui::Button *mapEditorButNewDropOff = new nanogui::Button(mapEditorWindow, "Place Drop-Off");
	nanogui::Button *mapEditorButBack = new nanogui::Button(mapEditorWindow, "Back");

	mapEditorButNewFloor->setCallback([&, mapEditorPoIXfield, mapEditorPoIYfield](){
		xField = mapEditorPoIXfield->value();
		yField = mapEditorPoIYfield->value();
		buttonMode = 1;
		//std::cout << xField;
		//factory.getPointOfInterest(mapEditorPoIXfield->value(), mapEditorPoIYfield->value()).setPointOfInterestType(pointOfInterestType::Wall);
	});

	mapEditorButNewWall->setCallback([&, mapEditorPoIXfield, mapEditorPoIYfield]() {
		xField = mapEditorPoIXfield->value();
		yField = mapEditorPoIYfield->value();
		buttonMode = 2;
	});

	mapEditorButNewDropOff->setCallback([&, mapEditorPoIXfield, mapEditorPoIYfield]() {
		xField = mapEditorPoIXfield->value();
		yField = mapEditorPoIYfield->value();
		buttonMode = 3;
	});

	mapEditorButBack->setCallback([&] {
		menuMode = 1;

		//(*mapEditorWindow).setVisible(false);
		//(*mainWindow).setVisible(true);
	});

}

void createVehicleEditButtons(nanogui::Screen* screen, nanogui::Window* vehicleEditorWindow, int &menuMode, bool &vehicleAdded, int &vehicleXField, int &vehicleYField) {
	
	nanogui::IntBox<int> *placeVehicleXfield = new nanogui::IntBox<int>(vehicleEditorWindow);
	placeVehicleXfield->setUnits("Y");
	placeVehicleXfield->setValue(5);
	placeVehicleXfield->setEditable(true);
	placeVehicleXfield->setMinValue(1);
	placeVehicleXfield->setSpinnable(true);
	placeVehicleXfield->setValueIncrement(1);

	nanogui::IntBox<int> *placeVehicleYfield = new nanogui::IntBox<int>(vehicleEditorWindow);
	placeVehicleYfield->setUnits("Y");
	placeVehicleYfield->setValue(5);
	placeVehicleYfield->setEditable(true);
	placeVehicleYfield->setMinValue(1);
	placeVehicleYfield->setSpinnable(true);
	placeVehicleYfield->setValueIncrement(1);
	
	nanogui::Button *vehicleEditorButPlaceVehicle = new nanogui::Button(vehicleEditorWindow, "New Vehicle");
	nanogui::Button *vehicleEditorButBack = new nanogui::Button(vehicleEditorWindow, "Back");

	vehicleEditorButPlaceVehicle->setCallback([&, placeVehicleXfield, placeVehicleYfield]() {
		vehicleXField = placeVehicleXfield->value();
		vehicleYField = placeVehicleYfield->value();
		vehicleAdded = true;
	});

	vehicleEditorButBack->setCallback([&] {
		menuMode = 1;
	});
}

void createTaskManagerButtons(nanogui::Screen* screen, nanogui::Window* taskManagerWindow, int &menuMode, bool &taskAdded, int &newTaskXField, int &newTaskYField) {
	
	nanogui::IntBox<int> *newTaskXfield = new nanogui::IntBox<int>(taskManagerWindow);
	newTaskXfield->setUnits("Y");
	newTaskXfield->setValue(5);
	newTaskXfield->setEditable(true);
	newTaskXfield->setMinValue(1);
	newTaskXfield->setSpinnable(true);
	newTaskXfield->setValueIncrement(1);

	nanogui::IntBox<int> *newTaskYfield = new nanogui::IntBox<int>(taskManagerWindow);
	newTaskYfield->setUnits("Y");
	newTaskYfield->setValue(5);
	newTaskYfield->setEditable(true);
	newTaskYfield->setMinValue(1);
	newTaskYfield->setSpinnable(true);
	newTaskYfield->setValueIncrement(1);

	nanogui::Button *taskManagerButNewTask = new nanogui::Button(taskManagerWindow, "New Task");
	nanogui::Button *taskManagerButBack = new nanogui::Button(taskManagerWindow, "Back");

	taskManagerButNewTask->setCallback([&, newTaskXfield, newTaskYfield]() {
		newTaskXField = newTaskXfield->value();
		newTaskYField = newTaskYfield->value();
		taskAdded = true;
	});

	taskManagerButBack->setCallback([&] {
		menuMode = 1;
	});
}