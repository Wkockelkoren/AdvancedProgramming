#ifndef TaskManager_H
#define TaskManager_H

#include <vector>
#include "Structures.h"
/**
Class for the TaskManager
*/
class TaskManager {
private:
	std::vector<Task> taskList;

public:
	TaskManager();

	~TaskManager();

	/**
	This function adds a task without a start position to the taskList.
	*/
	void createTask(Position goalPosition);

	/**
	This function adds a task with both a start and goal position to the taskList.
	*/
	void createTask(Position startPosition, Position goalPosition);

	/**
	This function returns a reference to the taskList
	*/
	std::vector<Task>&  getTaskList() ;

	/**
	This function deletes a task by iterator
	*/
	void deleteTask(size_t iterator);

	/**
	This function prints a list of all tasks
	*/
	void printTasks();
};
#endif