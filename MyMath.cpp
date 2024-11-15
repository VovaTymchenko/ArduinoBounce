#include <iostream>
#include "MyMath.h"

vector2d::vector2d()
{
	x = 0;
	y = 0;
}

vector2d::vector2d(float x, float y)
{
	this->x = x;
	this->y = y;
}

vector2d Normalize(vector2d vector) //returns a new vector which is this normalized
{
	vector = MultScalar(vector, pow(FindLength(vector), -1));
	return vector;
}

vector2d MultScalar(vector2d vector, float scalar) //returns a new vector which is this multiplied by scalar
{
	vector.x *= scalar;
	vector.y *= scalar;
	return vector;
}

vector2d AddVector(vector2d vector, vector2d vector2) //returns a sum of two vectors
{
	vector.x += vector2.x;
	vector.y += vector2.y;
	return vector;
}

float DotProduct(vector2d vector1, vector2d vector2) //return dot product of this and another vector
{
	return (vector1.x * vector2.x + vector1.y * vector2.y);
}

float FindLength(float x1, float y1, float x2, float y2) //find distance between two coordinates
{
	return abs(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

float FindLength(vector2d vector) //find length of a vector
{
	return abs(sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
}