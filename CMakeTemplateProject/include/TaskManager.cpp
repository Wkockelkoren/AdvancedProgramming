#include "TaskManager.h"
#include <iostream>


TaskManager::TaskManager() {

}

TaskManager::~TaskManager() {
	
}

void TaskManager::createTask(Position goalPosition) {
	Task task;
	task.startPosition = { SIZE_MAX,SIZE_MAX };
	task.goalPosition = goalPosition;
	taskList.push_back(task);
}


void TaskManager::createTask(Position startPosition,Position goalPosition) {
	Task task;
	task.startPosition = startPosition;
	task.goalPosition = goalPosition;
	taskList.push_back(task);
}

 std::vector<Task>&  TaskManager::getTaskList()  {
	return taskList;
}

void TaskManager::deleteTask(size_t iterator) {
	taskList.erase(taskList.begin() + iterator);
}


void TaskManager::printTasks() {
	std::cout << "List of Tasks:\n";
	for (Task task: taskList) {
		if (task.startPosition.x == SIZE_MAX && task.startPosition.y == SIZE_MAX) {
			std::cout << "Task to (" << task.goalPosition.x << ", " << task.goalPosition.y << ")\n";
		}
		else {
			std::cout << "Task from (" << task.startPosition.x << ", " << task.startPosition.y << ") to (" << task.goalPosition.x << ", " << task.goalPosition.y << ")\n";
		}
	}
	std::cout << "\n";
}
