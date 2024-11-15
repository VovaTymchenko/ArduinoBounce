#include "Circle.h"

Circle::Circle()
{
	cx = 0;
	cy = 0;
	r = 50;
	thickness = 4;
};

Circle::Circle(float cx, float cy, float r, float thickness)
{
	this->cx = cx;
	this->cy = cy;
	this->r = r;
	this->thickness = thickness;
};