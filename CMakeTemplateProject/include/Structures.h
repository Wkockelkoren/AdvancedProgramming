#pragma once
/**
These are the structures used in the program
*/
struct Position {
	/***
	A position contains a value for both the x- and y direction.
	*/
	size_t x = 0;
	size_t y = 0;
};

struct Task {
	/**
	A Task is an object that can be passed to an vehicle.
	*/
	Position goalPosition;
};
