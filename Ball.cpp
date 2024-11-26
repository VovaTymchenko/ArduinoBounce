#include "Ball.h"

Ball::Ball()
{
	cx = 4;
	cy = 4;
	r = 0;
	thickness = 4;
	spdX = 1;
	spdY = 1;
}

Ball::Ball(float cx, float cy, float thickness, float spdX, float spdY)
{
	this->cx = cx;
	this->cy = cy;
	r = 0;
	this->thickness = thickness;
	this->spdX = spdX;
	this->spdY = spdY;
}

void Ball::Move() //change coordinates based on the ball speed
{
	cx += spdX;
	cy += spdY;
}

void Ball::Bounce(const std::vector<Circle*>& circles, const std::vector<Ball*>& balls, int i, const int frameH, const int frameW) //handling collisions
{
	//WALL BOUNCE

	//left & right bounce
	if (balls[i]->cx - balls[i]->r - balls[i]->thickness <= 0) //left
	{
		balls[i]->cx += 2 * ((balls[i]->r + balls[i]->thickness) - balls[i]->cx); //turns overshoot into position after precise bounce
		balls[i]->spdX = -spdX;
	}
	if (balls[i]->cx + balls[i]->r + balls[i]->thickness >= frameW) //right
	{
		balls[i]->cx -= 2 * ((balls[i]->r + balls[i]->thickness) - frameW + balls[i]->cx); //turns overshoot into position after precise bounce
		balls[i]->spdX = -spdX;
	}

	//top & bottom bounce
	if (balls[i]->cy - balls[i]->r - balls[i]->thickness <= 0) //bottom
	{
		balls[i]->cy += 2 * ((balls[i]->r + balls[i]->thickness) - balls[i]->cy); //turns overshoot into position after precise bounce
		balls[i]->spdY = -spdY;
	}
	if (balls[i]->cy + balls[i]->r + balls[i]->thickness >= frameH) //top
	{
		balls[i]->cy -= 2 * ((balls[i]->r + balls[i]->thickness) - frameH + balls[i]->cy); //turns overshoot into position after precise bounce
		balls[i]->spdY = -spdY;
	}

	//OBJECT BOUNCE

	for (int k = 0; k < circles.size(); k++) //checking collision with circles
	{
		float distance = FindLength(circles[k]->cx, circles[k]->cy, balls[i]->cx, balls[i]->cy);
		if (abs(distance - circles[k]->r - balls[i]->r) <= circles[k]->thickness + balls[i]->thickness) //radius is supposed to always be 0, but ill leave it in the formula just in case
		{
			vector2d normal(balls[i]->cx - circles[k]->cx, balls[i]->cy - circles[k]->cy);
			normal = Normalize(normal);

			vector2d velocity(spdX, spdY);
			vector2d newVelocity = AddVector(velocity, MultScalar(normal, (-2 * DotProduct(velocity, normal))));
			//v new = v - 2(v . n) * n
			//^^^velocity - 2 * projection of velocity on normal^^^

			spdX = newVelocity.x;
			spdY = newVelocity.y;
		}
	}

	for (int k = i + 1; k < balls.size(); k++) //checking collision with balls
	{
		float distance = FindLength(balls[k]->cx, balls[k]->cy, balls[i]->cx, balls[i]->cy);
		if (abs(distance - balls[k]->r - balls[i]->r) <= balls[k]->thickness + balls[i]->thickness) //radius is supposed to always be 0, but ill leave it in the formula just in case
		{
			//return both balls to pre-collision state
			balls[i]->cx -= balls[i]->spdX;
			balls[i]->cy -= balls[i]->spdY;
			balls[k]->cx -= balls[k]->spdX;
			balls[k]->cy -= balls[k]->spdY;

			//this might look rather complicated, but all this is a result of figuring out a location where the colliding objects should have met between the "pre-collision" -> "collision" frames
			//to work out the "time" multiplier for the speeds of the objects, this formula was used:
			// 
			//||(c1,0 + t * v1) - (c2,0 + t * v2)|| = r1 + r2
			// 
			//where c1,0 and c2,0 are objects' "pre-collision" frame location vectors, v1 and v2 are their speed vectors, r1 and r2 are radiuses, and the "time" t is the speed multiplier we are trying to find
			//after doing some maths to find the formula for the "time" t, we get a quadratic equation:
			float t, t1, t2, A, B, C; //quadratic equation parameters
			vector2d deltaC0 = AddVector(vector2d(balls[i]->cx, balls[i]->cy), vector2d(-balls[k]->cx, -balls[k]->cy));
			vector2d deltaV = AddVector(vector2d(balls[i]->spdX, balls[i]->spdY), vector2d(-balls[k]->spdX, -balls[k]->spdY));
			A = pow(FindLength(deltaV), 2); //square the length of delta v
			B = 2 * DotProduct(deltaC0, deltaV); //2 * (delta c0 dot delta v)
			C = pow(FindLength(deltaC0), 2) - pow((balls[i]->r + balls[i]->thickness + balls[k]->r + balls[k]->thickness), 2); //square the length of delta c0 - square the sum of r
			t1 = (-B + sqrt(pow(B, 2) - 4 * A * C)) / (2 * A); //the quadratic equation
			t2 = (-B - sqrt(pow(B, 2) - 4 * A * C)) / (2 * A); //the quadratic equation
			if (t1 < t2) t = t1;
			else t = t2;
			//t has a 0 to 1 value, which lets us move the balls by a range of distances from (0, 0) to (spdX, spdY). It's pretty much a mask value

			vector2d velocity(balls[i]->spdX, balls[i]->spdY); //pre-collision velocity of balls[i]
			vector2d velocityK(balls[k]->spdX, balls[k]->spdY); //pre-collision velocity of balls[k]

			vector2d normal((balls[i]->cx + balls[i]->spdX * t) - (balls[k]->cx + balls[k]->spdX * t), (balls[i]->cy + balls[i]->spdY * t) - (balls[k]->cy + balls[k]->spdY * t));
			vector2d normalK((balls[k]->cx + balls[k]->spdX * t) - (balls[i]->cx + balls[i]->spdX * t), (balls[k]->cy + balls[k]->spdY * t) - (balls[i]->cy + balls[i]->spdY * t));

			normal = Normalize(normal); //normal for balls[i]
			normalK = Normalize(normalK); //normal for balls[k]
			vector2d normalKK;// = normalK;
			//vector2d normalK = MultScalar(normal, -1); //normal for balls[k]

			vector2d relDir = MultScalar(normal, DotProduct(velocity, normal)); //normalized projection of balls[i] velocity on normal
			vector2d relDirK = MultScalar(normal, DotProduct(velocityK, normal)); //normalized projection of balls[k] velocity on normal

			bool fasterK = (abs(FindLength(MultScalar(normal, (DotProduct(velocity, normal))))) < abs(FindLength(MultScalar(normal, (DotProduct(velocityK, normal))))));
			
			if (DotProduct(relDir, relDirK) < 0) //if dot product is < 0 the vector are pointing in opposite directions
			{
				//if projections of both balls' velocity on normal are not co-directed, flip the faster ball's normal vector
				if (fasterK) normal = MultScalar(normal, -1);
				else normalKK = MultScalar(normalK, -1);
			}

			vector2d newVelocity = AddVector(velocity, MultScalar(normal, (-2 * DotProduct(velocity, normal)))); //velocity for balls[i]
			vector2d newVelocityK = AddVector(velocityK, MultScalar(normalK, (-2 * DotProduct(velocityK, normalK)))); //velocity for balls[k]
			//v new = v - 2(v . n) * n
			//^^^velocity - 2 * projection of velocity on normal^^^

			//move both balls to the point of collision
			balls[i]->cx += balls[i]->spdX * t;
			balls[i]->cy += balls[i]->spdY * t;
			balls[k]->cx += balls[k]->spdX * t;
			balls[k]->cy += balls[k]->spdY * t;

			//set new speed
			balls[i]->spdX = newVelocity.x;
			balls[i]->spdY = newVelocity.y;
			balls[k]->spdX = newVelocityK.x;
			balls[k]->spdY = newVelocityK.y;

			//move both balls after the collision
			balls[i]->cx += balls[i]->spdX * (1 - t);
			balls[i]->cy += balls[i]->spdY * (1 - t);
			balls[k]->cx += balls[k]->spdX * (1 - t);
			balls[k]->cy += balls[k]->spdY * (1 - t);
		}
	}
}

void Ball::Split() //TBD
{
	//sounds fun, but i gotta do the main batch first
}