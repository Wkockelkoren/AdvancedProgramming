#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "Map.h"
#include "TaskManager.h"
#include "VehicleManager.h"

/**
Main menu options
*/
void MenuMain(size_t* menuMode);

/**
Task manager menu
*/
void MenuTaskManager(size_t* menuMode, Map& factory, TaskManager& taskManager);

/**
Vehicle manager menu
*/
void MenuVehicleManager(size_t* menuMode, Map& factory, VehicleManager& vehicleManager);


/**
Settings menu
*/
void MenuSettings(size_t* menuMode, VehicleManager& vehicleManager);

/**
Map editor menu
*/
void MenuMapEditor(size_t* menuMode, Map& factory);

/**
Function that gets user input within a given range
*/
size_t MenuUserInput(std::string text, size_t min, size_t max);

#endif