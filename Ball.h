#pragma once
#include <vector>
#include "MyMath.h"
#include "Circle.h"

class Ball : public Circle
{
public:
	float spdX, spdY; //move speed
	Ball();
	Ball(float cx, float cy, float thickness, float spdX, float spdY);
	void Move(); //change coordinates based on the ball speed
	void Bounce(std::vector<Circle*> circles, std::vector<Ball*> balls, int i, float symbMod, const int frameH, const int frameW); //handling collisions
	void Split(); //TBD
};