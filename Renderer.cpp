/*#include <Streaming.h>
#include <vector>
#include "Renderer.h"
#include "MyMath.h"

using namespace std;

//const char symb[6] = { ' ', '.', ':' , ';' , '+' , '#' }; //console gradient for overlapping objects

const float symbH = 1, symbW = 1; //console symbol pixel size
const float symbMod = symbH / symbW;
const int frameH = 90, frameW = 180; //draw surface dimensions - 1
int frame[frameH + 1][frameW + 1]; //frame "pixel" data

std::vector<Circle*> circles; //array of the objects to be displayed
std::vector<Ball*> balls; //array of the objects to be displayed

void DrawFrame() //uses the int frame array to pick characters from the symb gradient depending on the number of overlapping objects, then prints the character in console
{
	char curline[(frameW + 2) * (frameH + 1)];
	for (int i = 0; i < frameH; i++)
	{
		for (int j = 0; j < frameW; j++)
		{
			//if (i > 0 && j < 1) j = 1;
			curline[i * (frameW + 2) + j] = symb[min(frame[i][j], 5)];
			//cout << symb[min(frame[i][j], 5)];
		}
		curline[i * (frameW + 2) + frameW] = '|';
		curline[i * (frameW + 2) + frameW + 1] = '\n';
	}
	
	for (int j = 0; j < frameW; j++)
	{
		curline[(frameW + 2) * frameH + j] = '-';
	}
	curline[(frameW + 2) * frameH + frameW] = '+';
	curline[(frameW + 2) * frameH + frameW + 1] = 0;
	//system("cls");
	//cout << curline;
}

void MakeFrame() //runs through the matrix of y rows and x cols, checking if any of the objects should be displayed at the given coordinates. Uses an increment to determine how many objects overlap at a single coordinate
{
	for (int i = 0; i < frameH; i++)
	{
		for (int j = 0; j < frameW; j++)
		{
			frame[i][j] = 0;
			for (int k = 0; k < circles.size(); k++) //circles
			{
				float distance = FindLength(circles[k]->cx, circles[k]->cy, j, i * symbMod);
				if (abs(distance - circles[k]->r) <= circles[k]->thickness) frame[i][j] = frame[i][j] + 1;
			}

			for (int k = 0; k < balls.size(); k++) //balls
			{
				float distance = FindLength(balls[k]->cx, balls[k]->cy, j, i * symbMod);
				if (abs(distance - balls[k]->r) <= balls[k]->thickness) frame[i][j] = frame[i][j] + 1; //radius is supposed to always be 0, but ill leave it in the formula just in case
			}
		}
	}
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->Move();
		balls[i]->Bounce(circles, balls, i, symbMod, frameH, frameW);
	}
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
}*/