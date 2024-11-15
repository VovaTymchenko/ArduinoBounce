#pragma once

struct vector2d
{
	float x, y;
	vector2d();
	vector2d(float x, float y);
};
vector2d Normalize(vector2d vector); //returns a normalized vector
vector2d MultScalar(vector2d vector, float scalar); //returns a vector multiplied by a scalar
vector2d AddVector(vector2d vector, vector2d vector2); //returns a sum of two vectors
float DotProduct(vector2d vector1, vector2d vector2); //returns dot product of two vectors
float FindLength(float x1, float y1, float x2, float y2); //finds distance between two coordinates
float FindLength(vector2d vector); //finds length of a vector