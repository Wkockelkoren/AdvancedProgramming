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
	//init null

	void createTask(Position startPosition, Position goalPosition);
	
	Task getTask();
	//test push back
	const std::vector<Task>* const getTaskList() const;

	void deleteTask(size_t iterator);
};
#endif