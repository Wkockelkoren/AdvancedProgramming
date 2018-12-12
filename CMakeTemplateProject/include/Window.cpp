
#include <iostream>
#include <vector>
#include "Window.h"

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

void createButtons( nanogui::Screen* screen, nanogui::Window* mainWindow, nanogui::Window* mapEditorWindow, bool &mapEditMode) {
	nanogui::Button *mainButStart = new nanogui::Button(mainWindow, "Start");
	nanogui::Button *mainButStop = new nanogui::Button(mainWindow, "Stop");
	nanogui::Button *mainButMapEditor = new nanogui::Button(mainWindow, "Map Editor");

	
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
	



	mainButStart->setCallback([] {
		std::cout << "Start" << std::endl;
	});

	mainButStop->setCallback([] {
		std::cout << "Stop" << std::endl;
	});
	
	mainButMapEditor->setCallback([&] {
		mapEditMode = true;
		
		//(mainWindow)->setVisible(false);
		//(mapEditorWindow)->setVisible(true);
	});
	
	mapEditorButBack->setCallback([&] {
		mapEditMode = false;
		
		//(*mapEditorWindow).setVisible(false);
		//(*mainWindow).setVisible(true);
	});
	
}
