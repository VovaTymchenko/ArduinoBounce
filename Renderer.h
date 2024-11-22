#pragma once
#include <Adafruit_SSD1306.h>
#include "Circle.h"
//#include "Ball.h"

//void DrawFrame(Adafruit_SSD1306 display); //clear prev frame, draw new
void MakeFrame(Adafruit_SSD1306 display); //make a new frame
void AddCircle(Circle* pCircle); //add object to the array
//void AddBall(Ball* pBall); //add object to the array
void RemoveCircle(int index); //remove object from the array
void RemoveBall(int index); //remove object from the array