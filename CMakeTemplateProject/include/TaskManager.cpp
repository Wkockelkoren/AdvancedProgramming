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
	taskList.erase(taskList.begin() + iterator);
}