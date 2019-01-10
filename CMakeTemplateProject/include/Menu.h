#ifndef MENU_H
#define MENU_H

#include "Map.h"
#include "TaskManager.h"
#include "VehicleManager.h"

void MenuMain(size_t* menuMode);

void MenuTaskManager(size_t* menuMode, Map& factory, TaskManager& taskManager);

void MenuVehicleManager(size_t* menuMode, Map& factory, VehicleManager& vehicleManager);

size_t MenuUserInput(std::string text, size_t min, size_t max);

#endif