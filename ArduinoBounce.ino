#include <Streaming.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TM1638plus.h>
#include "MyMath.h"
#include "Circle.h"
#include "Ball.h"
#include "Renderer.h"

//HARDWARE

Servo servo; //servo

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64); //display

TM1638plus tm(D5, D6 , D7, false);//expansion board
byte tmButtons;

int pauseButton = 0; //button



Ball* ball2 = new Ball(5, 5, 6, 2.1, 5.3);
Ball* ball3 = new Ball(15, 5, 14, 2.1, 6.3);

void setup()
{
  //serial
  Serial.begin(115200);

  //display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  //expansion board
  tm.displayBegin(); 
  tm.displayText("00000000");

  //servo
  servo.attach(D3, 500, 2400);

  //pause button
  pinMode(D4, INPUT_PULLUP);


  Serial << endl << "Hello World!" << endl;
  AddBall(ball2);
  AddBall(ball3);
}

void loop()
{
  if (digitalRead(D4) == 0)
  {
    tone(D8, 466.16, 100);
    pauseButton = abs(pauseButton - 1);
    if (pauseButton) ServoSpin(180, 0, -1, 3);
    else ServoSpin(0, 180, 1, 3);
    tone(D8, 466.16, 100);
  }

  tmButtons = tm.readButtons(); // read which buttons are pressed
  tm.displayIntNum(tmButtons);
  tm.setLED(0, 1);
  
  MakeFrame(display, pauseButton, tmButtons - 1);
  display.display();
  display.clearDisplay();
}

void ServoSpin(int startAngle, int endAngle, int direction, int speed) //spinDirection should be 1 or -1
{
  servo.write(startAngle); 
  delay(500);
  for (int i = startAngle; i * direction <= endAngle; i += direction * speed) servo.write(i);
  delay(500);
}






















/*
  Circle* circle1 = new Circle();

  Serial << "x " << circle1->cx << endl;
  Serial << "y " << circle1->cy << endl;
  Serial << "r " << circle1->r << endl;
  Serial << "thick " << circle1->thickness << endl;

  Circle* circle2 = new Circle(90, 90, 0, 30);

  vector2d normal(circle1->cx - circle2->cx, circle1->cy - circle2->cy);
  Serial << "bare " << normal.x << normal.y << endl;
  Serial << "bare length " << FindLength(normal) << endl;
  normal = MultScalar(normal, 4);
  Serial << "multiplied " << normal.x << normal.y << endl;
  Serial << "multiplied length " << FindLength(normal) << endl;
  normal = Normalize(normal);
  Serial << "normalized " << normal.x << normal.y << endl;
  Serial << "normalized length " << FindLength(normal) << endl;

  vector2d paranormal(12 - circle2->cy, - 31 - circle2->cx);
  Serial << "dot product " << DotProduct(normal, paranormal) << endl;
  */