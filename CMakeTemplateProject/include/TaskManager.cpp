#include "TaskManager.h"

Task TaskManager::getTask() {
	/**
	This function returns the front task in list.
	*/
	return taskList.front();
}

TaskManager::TaskManager() {

}

TaskManager::~TaskManager() {
	
}

void TaskManager::createTask(Position goalPosition, Position startPosition = {NULL,NULL}) {
	/**
	This function adds a task to the taskList. 
	*/
	Task task;
	task.startPosition = startPosition;
	task.goalPosition = goalPosition;
	taskList.push_back(task);
}

const std::vector<Task>* const TaskManager::getTaskList() const {
	/**
	This function returns ann reference to the taskList
	*/
	return &taskList;
}

void TaskManager::deleteTask(size_t iterator) {
	/**
	This function deletes a task by iterator
	*/
	taskList.erase(taskList.begin() + iterator);
}