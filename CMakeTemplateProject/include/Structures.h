#pragma once
/**
These are the structures used in the program
*/
struct Position {
	/***
	A position contains a value for both the x- and y direction.
	*/
	size_t x;
	size_t y;

};

struct Task {
	/**
	A Task is an object that can be passed to an vehicle.
	*/
	Position startPosition;
	Position goalPosition;
};

enum AlgorithmChoice {
	enumSampleAlgorithm = 0,
	enumAstar
};