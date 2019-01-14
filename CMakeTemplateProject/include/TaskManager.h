#ifndef TaskManager_H
#define TaskManager_H

#include <vector>
#include "Structures.h"

class TaskManager {
private:
	std::vector<Task> taskList;

public:
	TaskManager();

	~TaskManager();

	void createTask(Position goalPosition);

	void createTask(Position startPosition, Position goalPosition);

	std::vector<Task>&  getTaskList() ;

	void deleteTask(size_t iterator);

	void printTasks();
};
#endif