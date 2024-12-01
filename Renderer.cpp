#include <Streaming.h>
#include "Renderer.h"
#include "MyMath.h"

const int frameH = 64, frameW = 128; //draw surface dimensions - 1
bool blink = false; //defines if the edited object should be displayed this frame

std::vector<Circle*> circles; //array of the objects to be displayed
std::vector<Ball*> balls; //array of the objects to be displayed

void MakeFrame(Adafruit_SSD1306 &display, int pause, int edit) //runs through the matrix of y rows and x cols, checking if any of the objects should be displayed at the given coordinates. Uses an increment to determine how many objects overlap at a single coordinate
{
	for (int i = 1; i < frameH; i++)
	{
		for (int j = 1; j < frameW; j++)
		{
			for (int k = 0; k < circles.size(); k++) //circles
			{
        if (k == edit && blink) continue;
				float distance = FindLength(circles[k]->cx, circles[k]->cy, j, i);
				if (abs(distance - circles[k]->r) <= circles[k]->thickness) display.drawPixel(j, i, SSD1306_WHITE);
			}

			for (int k = 0; k < balls.size(); k++) //balls
			{
        if (k == (edit - circles.size()) && blink) continue;
				float distance = FindLength(balls[k]->cx, balls[k]->cy, j, i);
				if (abs(distance - balls[k]->r) <= balls[k]->thickness) display.drawPixel(j, i, SSD1306_WHITE); //radius is supposed to always be 0, but ill leave it in the formula just in case
			}
		}
	}
  if (pause == 1)
  {
    for (int i = 0; i < balls.size(); i++)
	  {
	  	balls[i]->Move();
  		balls[i]->Bounce(circles, balls, i, frameH, frameW);
  	}
  }
  blink = !blink;
}

void AddCircle(Circle* pCircle) //adds pointer to a new Circle() object to the array of of circles on the scene
{
	circles.push_back(pCircle);
}

void AddBall(Ball* pBall) //adds pointer to a new Ball() object to the array of balls on the scene
{
	balls.push_back(pBall);
}

void RemoveCircle(int index) //removes a Circle pointer from the array of circles on the scene and reallocates memory
{ 
	Circle* circle = circles[index];
	circles.erase(circles.begin() + index);
	delete circle;
}

void RemoveBall(int index) //removes a Ball pointer from the array of balls on the scene and reallocates memory
{ 
	Ball* ball = balls[index];
	balls.erase(balls.begin() + index);
	delete ball;
}