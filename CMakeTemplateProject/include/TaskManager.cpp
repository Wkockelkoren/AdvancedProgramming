#include "TaskManager.h"
#include <iostream>


TaskManager::TaskManager() {

}

TaskManager::~TaskManager() {
	
}

void TaskManager::createTask(Position goalPosition) {
	/**
	This function adds a task without a start position to the taskList.
	*/
	Task task;
	task.startPosition = { SIZE_MAX,SIZE_MAX };
	task.goalPosition = goalPosition;
	taskList.push_back(task);
}


void TaskManager::createTask(Position startPosition,Position goalPosition) {
	/**
	This function adds a task with both a start and goal position to the taskList. 
	*/
	Task task;
	task.startPosition = startPosition;
	task.goalPosition = goalPosition;
	taskList.push_back(task);
}

 std::vector<Task>&  TaskManager::getTaskList()  {
	/**
	This function returns ann reference to the taskList
	*/
	return taskList;
}

void TaskManager::deleteTask(size_t iterator) {
	/**
	This function deletes a task by iterator
	*/
	
	if (iterator < taskList.size()) {
		taskList.erase(taskList.begin() + iterator);
	}
}


void TaskManager::printTasks() {
	std::cout << "List of Tasks:\n";
	size_t counter = 0;
	for (Task task: taskList) {
		std::cout << "Task " << counter;
		if (task.startPosition.x == SIZE_MAX && task.startPosition.y == SIZE_MAX) {
			std::cout << " to (" << task.goalPosition.x << ", " << task.goalPosition.y << ")\n";
		}
		else {
			std::cout << " from (" << task.startPosition.x << ", " << task.startPosition.y << ") to (" << task.goalPosition.x << ", " << task.goalPosition.y << ")\n";
		}
		counter++;
	}
	std::cout << "\n";
}
