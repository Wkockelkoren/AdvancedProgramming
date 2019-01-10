#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include "Map.h"
#include "TaskManager.h"
#include "VehicleManager.h"

void MenuMain(size_t* menuMode);

void MenuTaskManager(size_t* menuMode, Map& factory, TaskManager& taskManager);

void MenuVehicleManager(size_t* menuMode, Map& factory, VehicleManager& vehicleManager);

void MenuSettings(size_t* menuMode, VehicleManager& vehicleManager);

void MenuMapEditor(size_t* menuMode, Map& factory);

size_t MenuUserInput(std::string text, size_t min, size_t max);

#endif