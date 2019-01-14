#pragma once
/**
	A position contains a value for both the x- and y direction.
*/
struct Position {
	size_t x;
	size_t y;

};

/**
	A Task is an object that can be passed to an vehicle.
*/
struct Task {
	Position startPosition;
	Position goalPosition;
};

enum AlgorithmChoice {
	enumSampleAlgorithm = 0,
	enumAstar
};